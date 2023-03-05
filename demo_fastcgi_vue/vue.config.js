/*
 * @Author: Yimning
 * @Date: 2021-02-05 13:37:28
 * @Description: 
 * @FilePath: \demo_fastcgi_vue\vue.config.js
 */
var path = require('path')

module.exports = {
    outputDir: 'demo_fastcgi_vue', //打包好的包名 默认时为dist
    publicPath: './',  //公共路径  
    assetsDir: 'static',//打包好的静态资源路径
    productionSourceMap: false,
    //如果不需要定位问题，并且不想被看到源码，就把productionSourceMap 置为false，既可以减少包大小，也可以加密源码。
    // All options for webpack-dev-server are supported
    // https://webpack.js.org/configuration/dev-server/


    devServer: {
        // https://github.com/chimurai/http-proxy-middleware#proxycontext-config
        // axios跨域代理配置表，在这里可以配置特定的请求代理到对应的API接口
        host: "localhost", //本机主机名
        port: 8080, //本机启动端口
        https: false, //协议
        open: true, //启动服务器时自动打开浏览器访问
        proxy: {
            // 代理所有的以'/api'开头的浏览器请求
            '/api': {
                // 服务端域名和端口
                //target: 'http://localhost:8082/', 
                target: 'https://www.yimning.cn:8082/', //未上线可用
                // 如果设置成true：请求头中host会设置成target
                changeOrigin: true,   //开启代理，需要跨域
                // 用'/'替换浏览器请求url中的'/api'，例如浏览器请求为http://localhost:8082/api/xxx,
                // 则对应的服务端接口为http://localhost:8082/xxx
                secure: true,  // 安全证书校验
                ws:true,
                headers: {
                    Referer: 'https://www.yimning.cn:8082' //表示请求的来源（必填）
                },
                pathRewrite: {//
                    '^/api': '/'  //如果需要，可以用'^/api': '/'来代替，但是后台的接口需要注意改变 
                },
                //before: app => { }
            }
        }
    }

    // devServer: {
    //     proxy: {
    //         '/api':{
    //             target:'http://jsonplaceholder.typicode.com',
    //             changeOrigin:true,
    //             pathRewrite:{
    //                 '/api':''
    //             }
    //         }
    //     }
    // }
}

