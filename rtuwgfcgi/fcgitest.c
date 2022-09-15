#include <rude/cgi.h>
#include <fcgi_stdio.h>
#include <fcgi_config.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//#include <rude/cgiparser.h> //Version 5.0.0 Renamed Component from CGIParser to CGI
#include <iostream>
#include <sys/time.h>
#include <time.h>
#include <sys/stat.h>

#include "getparameter.h"
#include "common.h"
#include "fprintf.h"
#include "api.h"

#include "webcmd.h"

#include "web_config_ui.h"
#include "web_config_menu.h"
#include "web_config_menu_detail.h"
#include "web_menu_device.h"
#include "web_menu_data.h"
#include "web_menu_log.h"

#define RIGHT_HTML_BUFFER (right_html_str+strlen(right_html_str))

using namespace rude;

struct webserver_ctrl
{
    pthread_mutex_t mutex;
};

static struct webserver_ctrl wsctrl;




int init_dashboard_page(char *top_html_str, char *left_html_str, char *right_html_str)
{
    printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
    printf("<!DOCTYPE HTML>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <title>Document</title>\
    <link rel='stylesheet' href='/demo_test_fastcgi/cgi-bin/css/all.css'>\
    <link rel=\"stylesheet\" href=\"/demo_test_fastcgi/cgi-bin/css/dashboard_style.css\">\
    <script src=\"./cgi-bin/js/jquery-3.4.1.min.js\"></script>\
 \
</head>\
<body>\
    <div class=\"wrapper\">\
        <div class=\"sidebar\">\
            <div class=\"bg_shadow\"></div>\
            <div class=\"sidebar_inner\">\
                <div class=\"close\">\
                    <i class=\"fas fa-times\"></i>\
                </div>\
                <div class=\"profile_info\">\
                    <div class=\"profile_img\">\
                        <img src=\"/demo_test_fastcgi/cgi-bin/images/Profile_id.jpg\" alt=\"\">\
                    </div>\
                    <div class=\"profile_data\">\
                        <p class=\"name\">Yimning</p>\
                        <span>\
                            <i class=\"fas fa-map-marker-alt\"></i>\
                            中国,深圳\
                        </span>\
                    </div>\
                </div>\
\
\
                <ul class=\"siderbar_menu\">\
                    <li class=\"active\">\
                        <a href=\"#\">\
                            <div class=\"icon\">\
                                <i class=\"fas fa-heart\"></i>\
                            </div>\
                            <div class=\"title\">设备控制</div>\
                        </a>\
                    </li>\
                    <li class=\"\">\
                        <a href=\"#\">\
                            <div class=\"icon\">\
                                <i class=\"fas fa-chart-bar\"></i>\
                            </div>\
                            <div class=\"title\">数据分析</div>\
                        </a>\
                    </li>\
                    <li class=\"\">\
                        <a href=\"#\">\
                            <div class=\"icon\">\
                                <i class=\"fas fa-file-alt\"></i>\
                            </div>\
                            <div class=\"title\">日志记录</div>\
                        </a>\
                    </li>\
                    <li class=\"\">\
                        <a href=\"#\">\
                            <div class=\"icon\">\
                                <i class=\"fas fa-user\"></i>\
                            </div>\
                            <div class=\"title\">用户详细信息</div>\
                            <div class=\"arrow\">\
                                <i class=\"fas fa-chevron-down\"></i>\
                            </div>\
                        </a>\
                        <ul class=\"accordion\">\
                            <li><a href=\"#\" class=\"active\">用户信息</a></li>\
                        </ul>\
                    </li>\
                    <li class=\"\">\
                        <a href=\"#\">\
                            <div class=\"icon\">\
                                <i class=\"fas fa-unlock\"></i>\
                            </div>\
                            <div class=\"title\">修改密码</div>\
                        </a>\
                    </li>\
                     <li class=\"\">\
                        <a href=\"#\">\
                            <div class=\"icon\">\
                                <i class=\"fa fa-outdent\"></i>\
                            </div>\
                            <div class=\"title\">退出登陆</div>\
                        </a>\
                    </li>\
                </ul>\
            </div>\
        </div>\
        <div class=\"main_container\">\
            <div class=\"navbar\">\
                <div class=\"hamburger\">\
                    <i class=\"fas fa-bars\"></i>\
                </div>\
                <div class=\"logo\">\
                    <a href=\"#\">控制系统</a>\
                </div>\
            </div>\
            <div class=\"content\">\
                <div class=\"item\">\
                     <img src=\"/demo_test_fastcgi/cgi-bin/images/led_off.png\" alt=\"\">\
                </div>\
                <div class=\"item\">\
                     <img src=\"/demo_test_fastcgi/cgi-bin/images/beep_off.png\" alt=\"\">\
                </div>\
            </div>\
        </div>\
    </div>\
    <script src=\"/demo_test_fastcgi/cgi-bin/js/dashboard.js\"></script>\
</body>\
</html>\
");
    return 0;
}


int web_html_ui_select2(char *top_html_str, char *left_html_str, char *right_html_str)
{
    printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
    printf("<!DOCTYPE HTML>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <title>Document</title>\
    <link rel='stylesheet' href='/demo_test_fastcgi/cgi-bin/css/all.css'>\
    <link rel=\"stylesheet\" href=\"/demo_test_fastcgi/cgi-bin/css/dashboard_style.css\">\
    <script src=\"./cgi-bin/js/jquery-3.4.1.min.js\"></script>\
 \
</head>\
<body>\
    <div class=\"wrapper\">\
        <div class=\"sidebar\">\
            <div class=\"bg_shadow\"></div>\
            <div class=\"sidebar_inner\">\
                <div class=\"close\">\
                    <i class=\"fas fa-times\"></i>\
                </div>\
                <div class=\"profile_info\">\
                    <div class=\"profile_img\">\
                        <img src=\"/demo_test_fastcgi/cgi-bin/images/Profile_id.jpg\" alt=\"\">\
                    </div>\
                    <div class=\"profile_data\">\
                        <p class=\"name\">Yimning</p>\
                        <span>\
                            <i class=\"fas fa-map-marker-alt\"></i>\
                            中国,深圳\
                        </span>\
                    </div>\
                </div>\
\
\
");
printf("%s\n\n", left_html_str);
printf("\
    </div>\
        </div>\
        <div class=\"main_container\">\
            <div class=\"navbar\">\
                <div class=\"hamburger\">\
                    <i class=\"fas fa-bars\"></i>\
                </div>\
                <div class=\"logo\">\
                    <a href=\"#\">控制系统</a>\
                </div>\
            </div>\
            ");
printf("%s",right_html_str);
printf("\
        </div>\
    </div>\
    <script src=\"/demo_test_fastcgi/cgi-bin/js/dashboard.js\"></script>\
    ");
printf("\
</body>\
</html>\
");
    return 0;
}

int rtuwg_html_ui2(char *top_html_str, char *left_html_str, char *right_html_str)
{

    if (!top_html_str || !left_html_str || !right_html_str)
        return -1;

    printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
    printf("<html> \
    <head>  \
    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />  \
    <script src=\"/cgi-bin/javascripts/jquery-3.1.1.min.js\" type=\"text/javascript\"></script>\
    <script src=\"/cgi-bin/javascripts/json2.js\" type=\"text/javascript\"></script>\ 
    <title></title>  \
    </head>  \
    <style>  \
    div{margin:0;padding:0;border:0}  \
    </style>  \
    <body style=\"margin:0; padding:0; overflow:hidden\">");
    printf("<div style=\" height:100px; background-color:#009ad6\" id=\"top\">%s</div>", top_html_str);
    printf("<div style=\" background-color:#039\" >");
    printf("<div style=\"float:left;width:500px;height:500px; background-color:#f6f5ec\" id=\"left\">%s</div>", left_html_str);
    // printf("<div style=\"float:left; width:10px; height:500px; background-color:#ffffff;overflow:scroll;\" id=\"right\">%s</div>",right_html_str);
    printf("</div>");
#if 0 // conflict with serial popping box
printf("<link rel=\"stylesheet\" type=\"text/css\" href=\"/cgi-bin/javascripts/jquery.datetimepicker.css\"/>");
printf("<script src=\"/cgi-bin/javascripts/jquery.js\"></script>");
printf("<script src=\"/cgi-bin/javascripts/jquery.datetimepicker.js\"></script>");
printf("<script language=\"javascript\">  \
$('#datetimepicker').datetimepicker();\
$('#datetimepicker').datetimepicker({\
      lang:\"ch\",           \
      format:\"Y-m-d H:i:s\",      \
      timepicker:true,    \
      yearStart:2000, \
      yearEnd:2099, \
      todayButton:true\
});</script>");
#endif
#if 1
    printf("<script language=\"javascript\">  \
    function g(id){  \
        return document.getElementById(id);  \
    }  \
    var left_width = 550;\
    var page_min_height = 500;\
      \
    function resetFrame()  \
    {  \
        try{  \
            var xy = [window.innerWidth,window.innerHeight];  \
            var width = xy[0];  \
            var height = xy[1];  \
            if(width<left_width) width=left_width;  \
            if(height<page_min_height) height=page_min_height;  \
            var left_obj = g('left');  \
            var top_obj = g('top');  \
\
            left_obj.style.height = height-100+\"px\";  \
            left_obj.style.width = width+\"px\";  \
                     \
        }catch(e){  \
            alert();  \
        }  \
    }  \
    resetFrame();  \
    window.onresize = resetFrame;  \
    </script>");
#endif

    printf("</body>  \
    </html>");

    return 0;
}

int web_html_ui_select(char *top_html_str, char *left_html_str, char *right_html_str)
{

    if (!top_html_str || !left_html_str || !right_html_str)
        return -1;

    printf("%s \n\n", "Content-Type:text/html;charset=utf-8");

printf("<!DOCTYPE HTML>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <title>Document</title>\
    <link rel='stylesheet' href='/demo_test_fastcgi/cgi-bin/css/all.css'>\
    <link rel=\"stylesheet\" href=\"/demo_test_fastcgi/cgi-bin/css/dashboard_style.css\">\
    <script src=\"./cgi-bin/js/jquery-3.4.1.min.js\"></script>\
 \
</head>\
<body>\
    <div class=\"wrapper\">\
        <div class=\"main_container1\">\
            <div class=\"navbar\">\
                <div class=\"hamburger\">\
                    <i class=\"fas fa-bars\"></i>\
                </div>\
                <div class=\"logo\">\
                    <a href=\"/demo_test_fastcgi/fcgitest.fcgi?CMD=HOME_PAGE\">控制系统</a>\
                </div>\
            </div>\
            <div class=\"content1\">");
printf("%s\n\n", left_html_str);
printf("\
            </div>\
        </div>\
    </div>\
    <script>\
        console.log(\"left_html_str\");\
    </script>\
</body>\
</html>\
");    

    return 0;
}


int cjson_cgi_getPostStr(char **postDataBuffer)
{
#if 1
    char *content_len = NULL;
    char *tempBuffer = NULL;
    int  data_len, read_len;
 	/* 说明返回内容类型为html文本 */
	//printf("Content-Type:text/html\n\n");

	/* 请求方式 */
	char *req_method = getenv("REQUEST_METHOD");

    /* 获取数据类型  */
    char *content_type = getenv("CONTENT_TYPE");//application/x-www-form-urlencoded、multipart/form-data、text/plain 其中：multipart/form-data是文件传输
    
    /* 处理POST请求 */
	if(0 == strcmp("POST", req_method))    
    { 
        content_len = getenv("CONTENT_LENGTH");//获取数据长度

        if (NULL == content_len) {
            content_len = "";
        }
        
        data_len = atoi(content_len);
        if (data_len < 0) {
        return -1;
        }
        tempBuffer = (char *)malloc(data_len);
        memset(tempBuffer, 0, data_len);
        if (NULL == tempBuffer) {
            return -1;
        }

        read_len = fread(tempBuffer, 1, data_len, stdin);

        if (read_len != data_len) {
            return -1;
        }
        *postDataBuffer = tempBuffer;
    }
    else{
        *postDataBuffer = NULL;
    }
    
    return read_len;
#endif
#if 0
 	/* 说明返回内容类型为html文本 */
	// printf("Content-Type:text/html\n\n");
 
	/* 请求方式 */
	char *req_method = getenv("REQUEST_METHOD");
 
	if (0 == strcmp("POST", req_method)) { /* 处理POST请求 */
		char *content_len = getenv("CONTENT_LENGTH");//获取数据长度
		char *content_type = getenv("CONTENT_TYPE");//获取数据类型 application/x-www-form-urlencoded、multipart/form-data、text/plain 其中：multipart/form-data是文件传输
 
		int len = 0;
		if (NULL != content_len) {
			len = atoi(content_len);
		}		
 
		if (len > 0) { //获取post数据	
			//if (NULL != content_type && NULL == strstr(content_type, "multipart/form-data")) {//普通文本参数
				char dat_buf[50] = {0};
				if (len > 50) {
					len = 50;
				}
				len = fread(dat_buf, 1, len, stdin);
				printf("post type:%s. len:%d, data:%s.", content_type, len, dat_buf);
                FPRINTF_LOG(DEBUG_PATH,".......post type:%s. len:%d, data:%s.", content_type, len, dat_buf);
                
				//使用字符串分割函数获取各个参数：strtok_r
			
        }
    }
#endif
    return 0;
}



static int login_ok_already(int webcmd, rude::CGI &cgi )
{
    static int login_ok = 1;
    static struct timeval t_start, t_end;
    char user[] = {0};
    char password[] = {0}; 

    if (webcmd == WEB_CMD_LOGIN)
    {
        if (!strcmp(cjson_cgi_GET_getStrValue("USERNAME"), "admin") &&
            !strcmp(cjson_cgi_GET_getStrValue("PASSWORD"), "123"))
        {
            login_ok = 1; //  login ok
			gettimeofday(&t_start, NULL);
			gettimeofday(&t_end, NULL);
            // printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
            // printf("<script>alert(\"login ok%d--%d\")</script>",t_start.tv_sec,t_end.tv_sec);
		}
        else
        {
            login_ok = -1;
        }
	}
	else
	{
		gettimeofday(&t_end, NULL);
		if((t_end.tv_sec-t_start.tv_sec)>600)    //Login again after 600 seconds
        {
            login_ok=0;
        }
		gettimeofday(&t_start, NULL);

	}

	return login_ok;
}

int rtuwg_fcgi_main()
{
    system("mode con cp select=65001");
    static char top_html_str[1024 * 1024];   // 1024kB
    static char left_html_str[1024 * 1024];  // 1024kB
    static char right_html_str[1024 * 1024]; // 1024kB
    static char javascript_html_str[1024 * 1024]; // 1024kB
    static char tempBuffer[1024*1024]= {0};
    int ret = 0;
    const char *pstr =  NULL;

    while (FCGI_Accept() >= 0)
    {
        rude::CGI cgi; //必须放在这里定义，否则只执行一次
        int webcmd = 0;
        
        pthread_mutex_lock(&wsctrl.mutex);

        bzero(top_html_str, sizeof(top_html_str));
        bzero(left_html_str, sizeof(left_html_str));
        bzero(right_html_str, sizeof(right_html_str));
        pstr = cjson_cgi_GET_getStrValue("CMD");
        //printf("cjson_cgi_getStrValue:%s\r\n", pstr);
  
        webcmd = (int)web_str2cmd(pstr);
        // printf("%s\n\n", "Content-Type:text/html;charset=UTF-8");
        // printf("cgi[CMD] = %s\n\n <br/> webcmd = %d\n\n", cgi["CMD"], webcmd);
        // init_dashboard_page("top_html_str",top_html_str,"left_html_str");

        if (webcmd != WEB_CMD_HEARTBEAT &&
            ((ret = login_ok_already(webcmd, cgi)) != 1))
        { // not login ok
            if (ret == 0)
            {
                printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
                printf("<p style=\"text-align:center; font-size:18px\">需要重新登录!!!</p>");
            }
            if (ret == -1)
            {
                printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
                printf("<p style=\"text-align:center; font-size:18px\">登录用户名密码错误!!!</p>");
            }

            goto CGI_FINISH;
        }

        if (!cgi.exists("CMD"))
        {
            if (!strcmp("POST", getenv("REQUEST_METHOD")))
            { // upload file
                char save_file_name[50] = {0};
                int file_size;
            }
            goto CGI_FINISH;
        }

        switch (webcmd)
        {
        case WEB_CMD_HEARTBEAT:
            printf("%s\n\n","Content-Type:text/html;charset=utf-8");
            printf("heartbeat %s",cjson_cgi_GET_getStrValue("SELECT"));
            goto CGI_FINISH;
            
        case WEB_CMD_HOME_PAGE:
        case WEB_CMD_LOGIN:
        {
            display_config_ui(left_html_str, cjson_cgi_GET_getStrValue("SELECT"));
            web_html_ui_select(top_html_str,left_html_str,right_html_str);
            //printf("<script>alert(\"这是弹出框提示文本 %d--%d\")</script>",webcmd,login_ok_already(webcmd, cgi));
            goto CGI_FINISH;
        }
        break;
        case WEB_CMD_MENU:
        {
            display_config_menu(left_html_str, cjson_cgi_GET_getStrValue("SELECT"));
            
            menu_select select;

            if(!right_html_str) return -1;

            if(!cjson_cgi_GET_getStrValue("SELECT")) select=MENU_DEVICE;
            else select=(menu_select)atoi(cjson_cgi_GET_getStrValue("SELECT"));

            switch(select)
            {
                case MENU_DEVICE:
                {
                    char *pt = tempBuffer; 
                    
                    cjson_cgi_getPostStr(&pt);
                    if((!strcmp("POST", getenv("REQUEST_METHOD"))&&(pt!=NULL))){
                        
                        display_menu_device_writeStatus("/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/rtuwgfcgi/debug/led", cjson_cgi_POST_getStrValue(pt,"LED"));

                        display_menu_device_writeStatus("/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/rtuwgfcgi/debug/beep", cjson_cgi_POST_getStrValue(pt,"BEEP"));
                    }
                    display_menu_device_detail(RIGHT_HTML_BUFFER);
                }
                break;
                case MENU_DATA:
                {
                    display_menu_data_detail(RIGHT_HTML_BUFFER);
                }
                break;
                case MENU_LOG:
                {
                    display_menu_log_detail(RIGHT_HTML_BUFFER);
                }
                break;
                case MENU_USER:
                {
                    //sprintf(RIGHT_HTML_BUFFER,"serial");
                    //display_menu_serial_detail(RIGHT_HTML_BUFFER);
                }
                break;		
                case MENU_UPDATEPSD:
                {
                    //sprintf(RIGHT_HTML_BUFFER,"ai");
                    //display_menu_ai_detail(RIGHT_HTML_BUFFER);
                }
                break;
                case MENU_EXIT:
                {
                    //sprintf(RIGHT_HTML_BUFFER,"acqclient");
                    //display_menu_acqclient_detail(RIGHT_HTML_BUFFER);
                }
                break;
                case MENU_USER1:
                {
                    //sprintf(RIGHT_HTML_BUFFER,"network");
                    //display_menu_netowrk_detail(RIGHT_HTML_BUFFER);
                }
                break;		
                case MENU_USER2:
                {
                    //sprintf(RIGHT_HTML_BUFFER,"camera1");
                    //display_menu_camera_detail(RIGHT_HTML_BUFFER);
                }
                break;
                default:;
            }
            
            web_html_ui_select2(top_html_str,left_html_str,right_html_str);
        }
        break;
        case WEB_CMD_FLUSH_STATUS:
        {
            static int count = 0;
            char *pack_buffer = top_html_str;
            // printf("%s\n\n","Content-Type:text/html;charset=gb2312");
            printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
            // printf("login success %d",count++);
            // package formate
            // printf("{\"polcodes\":[{\"UserName\":\"123\",\"Sex\":\"456\"},{\"UserName\":\"789\",\"Sex\":\"0\"}]}");
            // status_flush_package(pack_buffer);
            printf("%s", pack_buffer);
            // NOTE :: continue below
            goto CGI_FINISH;
        }
        default:
            printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
            printf("NO such cmd %s !!!", cgi["CMD"]);
            goto CGI_FINISH;
        }
        //web_html_ui_select(top_html_str,left_html_str,right_html_str);
        // rtuwg_html_ui2("top_html_str", "left_html_str", "right_html_str");
    CGI_FINISH:
        //cgi.finish();
        pthread_mutex_unlock(&wsctrl.mutex);
    }
    return 0;
}