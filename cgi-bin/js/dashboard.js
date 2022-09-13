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


function imgFunc() {
    document.click_submit.action = "/demo_test_fastcgi/fcgitest.fcgi?CMD=MENU&SELECT=0";
    document.click_submit.submit();
}