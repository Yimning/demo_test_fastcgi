/*
 * @Author: Yimning
 * @Date: 2022-09-16 11:04:57
 * @Time: $CURRENT_YEAR/$CURRENT_MONTH/$CURRENT_DATE $CURRENT_HOUR:$CURRENT_MINUTE:$CURRENT_SECOND
 * @LastEditTime: 2022-09-20 14:05:29
 * @Description: 
 */
$(document).ready(function(){
    $(".siderbar_menu li").click(function(){
        $(".siderbar_menu li").removeClass("active");
        $(this).addClass("active");
    })
    $(".hamburger").click(function(){
        $(".wrapper").addClass("active");
    })
    $(".bg_shadow,.close").click(function(){
        $(".wrapper").removeClass("active");
    })
})


//清空cookie
function clearCookie() {
    var keys = document.cookie.match(/[^ =;]+(?=\=)/g);
    if (keys) {
        for (var i = keys.length; i--;) {
            document.cookie = keys[i] + '=0;path=/;expires=' + new Date(0).toUTCString();//清除当前域名下的,例如：m.kevis.com
            document.cookie = keys[i] + '=0;path=/;domain=' + document.domain + ';expires=' + new Date(0).toUTCString();//清除当前域名下的，例如 .m.kevis.com
            document.cookie = keys[i] + '=0;path=/;domain=kevis.com;expires=' + new Date(0).toUTCString();//清除一级域名下的或指定的，例如 .kevis.com
        }
    }
    console.log('已清除');
}

function checkpsd() {
    var result = document.getElementById("npid").value;
    var password = document.getElementById("npsdid").value;
    result = result.trim()
    if ((result == "")){
        alert("密码不能为空");
        return false;
    }
     
    if (password == "") {
        alert("再次输入的密码");
        return false;
    }
    

    if(result == password)
    {
        return true;
    }
    else alert("两次输入的密码一致");

    return false;
}



function pwdIn() {
    if(checkpsd() == true) {
        document.click_submit.action = "/demo_test_fastcgi/fcgitest.fcgi?CMD=MENU&SELECT=4";
        document.click_submit.submit();
        console.log(document.getElementById("npid").value);
    }
}
function cancel() {
    //location.reload();    //刷新当前页面
    /* <meta http-equiv="refresh" content="5"> */   //页面自动刷新；5 指每隔 5 秒刷新一次页面
    document.getElementById("npid").value = '';
    document.getElementById("npsdid").value = '';
    console.log('已清除');
}

function ok_keyup_submit(e){ 
    var evt = window.event || e; 
    if (evt.keyCode == 13){
        //回车事件
        pwdIn();
    }
}