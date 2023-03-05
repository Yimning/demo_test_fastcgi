<template>
    <div class="wrap">
      <iframe 
        ref="iframe" 
        :src="htmlSrc" 
        width="100%" 
        height="100%" 
        frameborder="0">
      </iframe>
      <!-- <button @click="vueSendMsg">vue向iframe传递信息</button>
      <button @click="iframeMethods">触发iframe中的方法</button> -->
    </div>
  </template>
  
  <script>
  export default {
    data() {
      return {
        htmlSrc:'static/index.html',
      };
    },
    methods: {
      // vue获取iframe传递过来的信息
    //   getiframeMsg(event){
    //     const res = event.data;
    //     console.log(event)
    //     if(res.cmd == 'myIframe'){
    //       console.log(res)
    //     }
    //   },
    //   // vue向iframe传递信息
    //   vueSendMsg(){
    //     const iframeWindow = this.$refs.iframe.contentWindow;
    //     iframeWindow.postMessage({ 
    //       cmd:'myVue',
    //       params : {
    //         info: 'Vue向iframe传递的消息',
    //       } 
    //     },'*')
    //   },
    //   // 触发iframe中的方法
    //   iframeMethods(){
    //     this.$refs.iframe.contentWindow.triggerByVue('通过Vue触发iframe中的方法');
    //   },
    },
    mounted() {
      //window.addEventListener('message',this.getiframeMsg)
    },
  };
  </script>
  
  
  <style lang="scss" scoped>
  .wrap{
    width: 100%;
    height: 100%;
  }
  </style>
  