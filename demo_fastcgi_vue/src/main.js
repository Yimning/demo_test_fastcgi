import Vue from 'vue';
import App from './App.vue';
import router from './router';
import ElementUI from 'element-ui';
import VueI18n from 'vue-i18n';
import store from './store';
import { messages } from './components/common/i18n';
import 'element-ui/lib/theme-chalk/index.css'; // 默认主题
// import './assets/css/theme-green/index.css'; // 浅绿色主题
import './assets/css/icon.css';
import './components/common/directives';
import 'babel-polyfill';
import "./permission";
import depot from './utils/requestDepot';


//引入axios模块(先下载`axios`--)
import axios from 'axios'
//将axios挂载在vue原型链上
Vue.prototype.$axios = axios;
// axios.defaults.timeout =  3000;
axios.defaults.headers.post['Content-Type'] = 'application/json;charset=UTF-8';

Vue.config.productionTip = false;
Vue.use(VueI18n);
Vue.use(ElementUI, {
    size: 'small'
});
const i18n = new VueI18n({
    locale: 'zh',
    messages
});

depot();

new Vue({
    router,
    i18n,
    store,  //注意导入store
    render: h => h(App)
}).$mount('#app');
