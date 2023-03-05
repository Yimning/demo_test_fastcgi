import axios from 'axios';

const service = axios.create({
    // process.env.NODE_ENV === 'development' 来判断是否开发环境
    // easy-mock服务挂了，暂时不使用了
    // baseURL: 'https://www.easy-mock.com/mock/592501a391470c0ac1fab128',
    headers: {
        'content-type': 'application/json;charset=UTF-8',
        'token': 'one'
    }, 
   // baseURL: 'http://localhost:8082',  
    timeout: 5000,
    withCredentials: true
});
// 添加请求拦截器
service.interceptors.request.use(
    config => {
        // 在发送请求之前做某事，比如说 设置token
        config.headers['token'] = 'token';
        return config;
    },
    error => {
        // 请求错误时做些事
        console.log(error);
        return Promise.reject();
    }
);

// 添加响应拦截器
service.interceptors.response.use(
    // 对响应数据做些事
    response => {
        if (response.status === 200) {
            return response.data;
        } else {
            Promise.reject();
        }
    },
    error => {
        console.log(error);
        return Promise.reject(); // 返回接口返回的错误信息
    }
);

export default service;