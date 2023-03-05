import router from "./router";

/* 路由前置拦截 */
// 路由判断登录 根据路由配置文件的参数

//使用钩子函数对路由进行权限跳转
// router.beforeEach((to, from, next) => {
//   document.title = `${to.meta.title} | vue-manage-system`;
//   const role = this.$store.getters.getUser.roseID;
//   console.log(role);
//   if (!role && to.path !== '/login') {
//       next('/login');
//   } else if (to.meta.permission) {
//       // 如果是管理员权限则可进入，这里只是简单的模拟管理员权限而已
//       role === 'admin' ? next() : next('/403');
//   } else {
//       // 简单的判断IE10及以下不进入富文本编辑器，该组件不兼容
//       if (navigator.userAgent.indexOf('MSIE') > -1 && to.path === '/editor') {
//           Vue.prototype.$alert('vue-quill-editor组件不兼容IE10及以下浏览器，请使用更高版本的浏览器查看', '浏览器不兼容通知', {
//               confirmButtonText: '确定'
//           });
//       } else {
//           next();
//       }
//   }
// });

// to: Route: 即将要进入的目标 路由对象
// from: Route: 当前导航正要离开的路由
// next: Function: 一定要调用该方法来 resolve 这个钩子。执行效果依赖 next 方法的调用参数。

router.beforeEach((to, from, next) => {
  document.title = `${to.meta.title} | vue-manage-system`;

  if (to.matched.some(record => record.meta.requireAuth)) { // 判断该路由是否需要登录权限
     const token = localStorage.getItem("token")
    console.log("------token------" + token)
    if (token) { // 判断当前的token是否存在 ； 登录存入的token
      if (to.path === '/login') {
      } else {
        next()
      }
    } else {
      next({
        path: '/login'   //token不存在 则无法进入
      })
    }
  } else {
    next()
  }
});




// router.beforeEach((to, from, next) => {


//   const route = ['dashboard'];
//   let isLogin = localStorage.getItem("token"); // 是否登录
//   console.log(isLogin);
//   // 未登录状态；当路由到route指定页时，跳转至login
//   if (route.indexOf(to.path) >= 0) {
//     if (isLogin == null) {
//       router.push({
//         path: '/login',
//       });
//     }
//   }
//   // 已登录状态；当路由到login时，跳转至home 
//   console.log("111111111111"+to.path)
//   //localStorage.setItem('routerName', to.name)
//   if (to.path === 'login') {
//     if (isLogin != null) {
//       router.push({
//         path: '/Dashboard',
//       });;
//     }
//   }
//   next();
// });