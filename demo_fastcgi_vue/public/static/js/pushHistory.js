/*
 * @Author: Yimning 1148967988@qq.com
 * @Date: 2022-09-20 16:13:38
*/

//浏览器返回键事件
pushHistory();
window.addEventListener(
    "popstate", function (e) {
        //判断移动端
        var userAgentInfo = navigator.userAgent;
        var Agents = new Array("Android", "iPhone", "SymbianOS", "Windows Phone", "iPad", "iPod");
        var equipmentType = false;

        for (var v = 0; v < Agents.length; v++) {
            if (userAgentInfo.indexOf(Agents[v]) != -1) {
                equipmentType = true;
                break;
            }
        }
        if (equipmentType) {
            $("#mask-back").show();
            $("#mask-back .back-close").on(
                "click", function () {
                    $("#mask-back").hide();
                })
        }
        pushHistory(); //注，此处调用，可以让用户一直停留着这个页面
    },
    false);

function pushHistory() {
    var state = {
        title: "title",
        url: "#"
    };
    window.history.pushState(state, "title", "#");
}
