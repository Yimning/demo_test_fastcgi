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
