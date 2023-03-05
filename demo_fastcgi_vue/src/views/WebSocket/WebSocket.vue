<!--
 * @Author: your name
 * @Date: 2020-11-24 15:35:44
 * @LastEditTime: 2020-12-07 12:52:44
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \vue-manage-system\src\views\WebSocket\WebSocket.vue
-->
<template>
    <div>
        <button @click="requstWs">点击发起websocket请求</button>
        <button @click="closeWebSocket">关闭</button>
    </div>
</template>
<script>
import { sendWebSocket, closeWebSocket } from '@/utils/websocket.js';

export default {
    beforeDestroy() {
        // 页面销毁时关闭ws。因为有可能ws连接接收数据尚未完成，用户就跳转了页面
        // 在需要主动关闭ws的地方都可以调用该方法
        closeWebSocket();
    },
    methods: {
        // ws连接成功，后台返回的ws数据，组件要拿数据渲染页面等操作
        wsMessage(data) {
            const dataJson = data;
            console.log(dataJson);
            // 这里写拿到数据后的业务代码
        },
        // ws连接失败，组件要执行的代码
        wsError() {
            // 比如取消页面的loading
        },
        requstWs() {
            // 防止用户多次连续点击发起请求，所以要先关闭上次的ws请求。
            //closeWebSocket();
            // 跟后端协商，需要什么参数数据给后台
            const obj = {
                monitorUrl: '',
                userName: ''
            };
            // 发起ws请求
            sendWebSocket('ws://localhost:8082/websocket/DPS007', '', this.wsMessage, this.wsError);
            let url = 'http://localhost:8082/xdx/text?shopId=DPS007';
            // 这里只是一个基于axios的ajax请求，你可以换成你的请求格式
            // this.$ajax.get(url)

            // 不想安装axios了，这里使用最原始的 js去请求
            // var xhr = new XMLHttpRequest () ;
            // xhr.open('get',url,true);
            // xhr.send("fff");
        },
        closeWebSocket() {
            closeWebSocket();
        }
    }
};
</script>


