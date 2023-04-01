/*
 * @Author: your name
 * @Date: 2020-08-30 21:29:12
 * @LastEditTime: 2021-07-08 19:45:20
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \vue-manage-system\src\axios.js
 */
import axios from 'axios'
import Element from 'element-ui'
import router from './router'
import store from './store'

/* 当发起axios请求时 会自动作为前置 */
//axios.defaults.baseURL = "http://localhost:8082"
axios.defaults.baseURL = 'http://localhost'
// 前置拦截
axios.interceptors.request.use(config => {
  return config
})

axios.interceptors.response.use(response => {
    let res = response.data;

    console.log("=================")
    console.log(res)
    console.log("=================")

    if (res.code === 200) {
      return response
    } else {

      Element.Message.error('错了哦，这是一条错误消息', {duration: 3 * 1000})
      return Promise.reject(response.data.msg)
    }
  },
  error => {
    console.log(error)
    if(error.response.data) {
      error.message = error.response.data.msg
    }

    if(error.response.status === 401) {
      store.commit("REMOVE_INFO") //store的提交，把全局的参数清空 ,index.js
      router.push("/login")
    }

    Element.Message.error(error.message, {duration: 3 * 1000})
    return Promise.reject(error)  //阻止返回
  }
)