/*
 * @Author: Yimning 1148967988@qq.com
 * @Date: 2022-08-12 03:56:15
 * @Description: login
 */

function checkUser() {
    var result = document.getElementById("uid").value;
    var password = document.getElementById("pid").value;
    result = result.trim()
    if ((result == "")&&(result == null)&&(result == undefined)){
        alert("用户名不能为空");
        return false;
    }
     
    if (password=="") {
        alert("密码不能为空");
        return false;
    }
    return true;
}

function $(id) {
    return document.getElementById(id).value;
}


function signIn() {
   if(checkUser() == true) {
        document.click_submit.action = "/demo_test_fastcgi/fcgitest.fcgi";
        document.click_submit.submit();
   }
}
function signUp() {
    document.click_submit.action = "#######";
    document.click_submit.submit();
}



function keyup_submit(e){ 
    var evt = window.event || e; 
    if (evt.keyCode == 13){
        //回车事件
        signIn();
    }
}
