# demo_fastcgi_vue

## Project setup
```
npm install
```

### Compiles and hot-reloads for development
```
npm run serve
```

### Compiles and minifies for production
```
npm run build
```

### Lints and fixes files
```
npm run lint
```

### Customize configuration
See [Configuration Reference](https://cli.vuejs.org/config/).

### How to create demo first time
Create vue3 demo：
```
vue create XXX   # XXX is demo name.
```
Next
```
# 是否使用淘宝源
Your connection to the default yarn registry seems to be slow.
   Use https://registry.npm.taobao.org for faster installation? (Y/n)  Y


? Please pick a preset: (Use arrow keys)            
   Default ([Vue 2] babel, eslint)                   
>  Default (Vue 3 Preview) ([Vue 3] babel, eslint)   
   Manually select features  

Next press Enter.
```
And waitting for the first project initialization to complete.and the prompt is as follows
```
Vue CLI v5.0.8
? Please pick a preset: Default ([Vue 3] babel, eslint)


Vue CLI v5.0.8
✨  Creating project in /home/yimning/XXX/demo_fastcgi_vue.
⚙️  Installing CLI plugins. This might take a while...


added 857 packages in 55s
🚀  Invoking generators...
📦  Installing additional dependencies...


added 102 packages in 19s
⚓  Running completion hooks...

📄  Generating README.md...

🎉  Successfully created project demo_fastcgi_vue.
👉  Get started with the following commands:

 $ cd demo_fastcgi_vue
 $ npm run serve

```
And next,execute `npm run serve`
```
> demo_fastcgi_vue@0.1.0 serve
> vue-cli-service serve

 INFO  Starting development server...


 DONE  Compiled successfully in 25948ms                                                                                                                                            5:41:50 AM


  App running at:
  - Local:   http://localhost:8080/
  - Network: http://192.168.1.166:8080/

  Note that the development build is not optimized.
  To create a production build, run npm run build.

```
Finally, you Will be able to access the web page through the local website or network address.




### demo structure
├── README.md            项目介绍
├── index.html           入口页面
├── public              构建项目的公共部分
├── screenshots                效果截图
├── src                源码目录 
│  ├── main.js          入口js文件
│  ├── permission.js      路由权限设置
│  ├── axios.js         路由全局配置与拦截
│  ├── App.vue          根组件
│  ├── api                   项目接口
│  ├── components        公共组件目录
│  ├── assets           资源目录，这里的资源会被wabpack构建
│  ├── routes           前端路由
│  │  └── index.js
│  ├── store           应用级数据（state）状态管理
│  │  └── index.js
│  └── views           页面目录 
│    ├── AccountSettings        账户信息维护
│    ├── ClassTable             课程信息管理
│    ├── FaceManager            人脸库管理
│    └── SignIn                 考勤信息管理
│    ├── UsersManager           账户信息管理
│    └── WebSocket              WebSocket连接 
│    ├── 403.vue                无权限页面
│    └── 404.vue                页面不存在
│    └── Dashboard.vue          主页面
│    └── Login.vue              登录页面
│    └── Photograph.vue         即时拍照页面
│    └── Tabs.vue               消息中心
├── vue.config.js         项目配置、开发环境变量、生产环境变量
├── package.json    npm包配置文件，定义了项目的npm脚本，依赖包等

