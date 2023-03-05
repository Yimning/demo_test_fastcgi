import axios from './request'

var depot = {}

depot.get = function ({ url, config = {}, cb }) {
    axios.get(url, config).then((res) => {
        if (res.status === 200) {
            let result = res.data;
            cb(result);
        }
    }).catch((error) => {
        console.log('请求错误：' + error);
    });
};

depot.post = function ({ url, data, cb }) {
    axios.post(url, data).then(
        (res) => {
            if (res.status === 200) {
                if (res.status === 200) {
                    let result = res.data;
                    cb(result);
                }
            }
        }).catch((error) => {
        console.log(error);
    });
};

export default () => {
    window.depot = depot;
};


//在Main中引入

// import store from './utils/requestDepot';
// depot();


//使用  注意解决跨域问题  

// depot.get({
//     url: 'demo/demo',
//     data: {},
//     cb: (res)=> {
//       console.log(res)
//     }
//   })