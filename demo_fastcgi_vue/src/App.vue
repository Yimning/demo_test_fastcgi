<template>
    <div id="app">
        <router-view v-if="isRouterAlive"></router-view>
    </div>
</template>
<style>
@import './assets/css/main.css';
/* 深色主题  */
@import './assets/css/color-dark.css';
/*@import "./assets/css/theme-green/color-green.css";   浅绿色主题*/
</style> 
<script>
export default { 
    name: 'app',
    provide() {
        return {
            reload: this.reload
        };
    },
    data() {
        return {
            isRouterAlive: true
        };
    }, 
    methods: {
        reload() {
            this.isRouterAlive = false;
            this.$nextTick(function () {
                this.isRouterAlive = true;
            });
        }
    }
};
</script>