#ifdef ENABLE_FASTCGI
#include <fcgi_stdio.h>
#include <fcgi_config.h>
#else
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>   
#include <time.h>         
#include <sys/stat.h>
#include <sys/wait.h> 

#include "getparameter.h"
#include "common.h"
#include "api.h"

#include "webcmd.h"

#include "web_config_ui.h"
#include "web_config_menu.h"
#include "web_config_menu_detail.h"
#include "web_menu_device.h"
#include "web_menu_data.h"
#include "web_menu_log.h"
#include "web_menu_updatepsw.h"
#include "web_flush_data.h"
#include "qdecoder/qdecoder.h"  
#include "qdecoder/internal.h"

#include "dbgout.h"
#include "rest_common.h"
#include "raphters.h"
#include <json.h>
#include <pthread.h>
#include <sqlite3.h>

#define RIGHT_HTML_BUFFER (right_html_str+strlen(right_html_str))

struct WebServerCtrl_T  
{
    pthread_mutex_t mutex;     
};

static struct WebServerCtrl_T webServerCtrl;

   


int init_dashboard_page(char *top_html_str, char *left_html_str, char *right_html_str)
{
    printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
    printf("<!DOCTYPE HTML>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <meta http-equiv=\"Pragma\" content=\"no-cache\">\
    <meta http-equiv=\"Cache-Control\" content=\"no-cache\">\
    <meta http-equiv=\"Expires\" content=\"0\">\
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
                    <a href=\"/demo_test_fastcgi/fcgitest.fcgi?CMD=MENU\">控制系统</a>\
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
    <link rel=\"stylesheet\" href=\"/demo_test_fastcgi/cgi-bin/css/index_style.css\">\
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
                    <a href=\"/demo_test_fastcgi/fcgitest.fcgi?CMD=HOME\">控制系统</a>\
                </div>\
            </div>\
            ");
printf("%s",right_html_str);
printf("\
        </div>\
    </div>\
    <script src=\"/demo_test_fastcgi/cgi-bin/js/dashboard.js\"></script>\
    <script src=\"/demo_test_fastcgi/cgi-bin/js/pushHistory.js\"></script>\
    ");
printf("\
</body>\
</html>\
");
    return 0;
}

static int login_ok_already(int webcmd, char* accountNumber, char* passWord)
{
    static int login_ok = -1;
    static struct timeval t_start, t_end;

    char tempBuffer[MAX_BUFFER_SIZE]={0};

    char *pstr = NULL;
    pstr = tempBuffer;
    fread_file(LOGIN_PATH,&pstr);

    if (webcmd == WEB_CMD_LOGIN)
    {
        if((pstr != NULL) &&(!strcmp(accountNumber, cJSON_GetStrValue(pstr,"accountNumber"))) &&(!strcmp(passWord, cJSON_GetStrValue(pstr,"passWord"))))
        {
            login_ok = 1; //  login ok
			gettimeofday(&t_start, NULL);
			gettimeofday(&t_end, NULL);
            FPRINTF_LOG(DEBUG_PATH,"%s登录操作---%s\r\n", web_cmd2str(webcmd), getenv("REQUEST_URI"));         
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
    free(pstr);
	return login_ok;
}

static int get_request_method_type(char* request_method)
{
    if (request_method != NULL)
    {
        if(!strcmp(request_method, "GET"))
        {
            return 4;
        }else if(!strcmp(request_method, "POST"))
        {
            return 2;
        }else if(!strcmp(request_method, "COOKIE"))
        {
            return 1;
        }else{
            return 0;
        }
           
    }else
        return -1;
}

struct response *res;
START_HANDLER (simple, POST, "/login", res,0, matches) {
    char tempBuffer[256] = {0}; 
    char *pt = tempBuffer; 
    char *accountNumber = NULL;
    char *passWord = NULL;
    char msg[256]={0};
    int ret = -1;
    int webcmd = 1;
    
    // char *get_query_string1 = qcgireq_getquery(Q_CGI_POST);

    // DEBUG_LOG(DEBUG_PATH,DEBUG,"qcgireq_getquery(Q_CGI_POST)=%s\n",get_query_string1);

    // if(get_query_string1 != NULL) {
    //     free(get_query_string1);
    // }
    //cjson_cgi_getPostStr(&pt);

    
    // json_object *req_json = json_object_new_object();

    qentry_t *req = qcgireq_parse(NULL, 0);
    MODEL_INIT(POST);
    REQUEST_REQUIRED_VAR_STRING(accountNumber, "accountNumber");
    REQUEST_REQUIRED_VAR_STRING(passWord, "passWord");
    DEBUG_LOG(DEBUG_PATH,DEBUG,"get_query_string====%s---%s\n",accountNumber,passWord);
    GO_END_HANDLER;

    ret = login_ok_already(webcmd, accountNumber, passWord);

    switch (ret)
    {
        case 0:
            // printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
            // printf("<p style=\"text-align:center; font-size:18px\">需要重新登录!!!</p>");
            strcpy(msg,"Need to log in again!");
            break;
        case 1:
            strcpy(msg,"Login succeeded!");
            break;
        case -1:
            // printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
            // printf("<p style=\"text-align:center; font-size:18px\">登录用户名密码错误!!!</p>");
            strcpy(msg,"Login accountnumber or password error!");
            break;
    }
    MODEL_ADD_STRING("accountNumber", accountNumber);
    MODEL_ADD_STRING("msg", msg);
	MODEL_ADD_INTEGER("data", ret);
    MODEL_OUTPUT();
    //read_stdin(NULL);                 
    //req->print(req, stdout, true);

    // Get values
    // char *value = (char *)req->getstr(req, "accountNumber", false);

    // if (value == NULL) value = "(nothing)";

    //char *query_string = NULL;

    //DEBUG_LOG(DEBUG_PATH,DEBUG,"%s---%s---%s---%s---%s\n",tempBuffer,getenv("CONTENT_TYPE"),getenv("CONTENT_LENGTH"),get_query_string,query_string);

    //cjson_cgi_getPostStr(&pt);
    

    //DEBUG_LOG(DEBUG_PATH,DEBUG,"Total %d entries.    pt=%s----strlen(pt)=%d\n", req->size(req),pt,strlen(pt));

    // Print out
    // qcgires_setcontenttype(req, "application/json");


    //REQUEST_PARSER_INIT(POST);
    //response_add_header(res, "content-type", "application/json");
    //response_write(res, "{\"add\":\"0\"}");
    // response_write(res, host_name);
}
END_HANDLER

START_HANDLER(default_handler, GET, "/login", res, 0, matches)
{
    char tempBuffer[256] = {0}; 
    char *pt = tempBuffer; 
                        
    cjson_cgi_getPostStr(&pt);

    //qentry_t *req = qcgireq_parse(NULL, 0);

    //DEBUG_LOG(DEBUG_PATH,DEBUG,"Total %d entries.    pt=%s\n", req->size(req),pt);
    //req->print(req, stdout, true);


    // Get values
    //char *value = (char *)req->getstr(req, "accountNumber", false);
    char *value = NULL;
    if (value == NULL) value = "(nothing)";

    char *query_string = get_query_string();

    char *get_query_string1 = qcgireq_getquery(Q_CGI_POST);

    DEBUG_LOG(DEBUG_PATH,DEBUG,"qcgireq_getquery(Q_CGI_POST)=%s\n",get_query_string1);

    if(get_query_string1 != NULL) {
        free(get_query_string1);
    }

    DEBUG_LOG(DEBUG_PATH,DEBUG,"%s---%s-----%s\n",value,getenv("CONTENT_TYPE"),query_string);

    response_add_header(res, "content-type", "text/html");
    response_write(res, "default page");
} END_HANDLER

// START_AUTHORIZED_MODEL(getNetworkSideBand, POST, "/api/login", 2, matches, true) 
// {
//     // if(0){
//     //     matches = matches;
//     // }
//     // MODEL_ADD_INTEGER("sideband_devices_id", 0);
//     // MODEL_OUTPUT();

// }END_AUTHORIZED_MODEL

int server_fcgi_main()
{
    system("mode con cp select=65001");
    static char top_html_str[1024 * 1024];   // 1024kB
    static char left_html_str[1024 * 1024];  // 1024kB
    static char right_html_str[1024 * 1024]; // 1024kB
    static char javascript_html_str[1024 * 1024]; // 1024kB
    static char tempBuffer[1024*1024]= {0};
    int ret = 0;
    char *username;
    char *password; 
    const char *pstr =  NULL;


    // while (FCGI_Accept() >= 0)
    // {
        //rude::CGI cgi; //必须放在这里定义，否则只执行一次
        int webcmd = 0;

        // pthread_t tid;
        // pthread_create(&tid, NULL, read_stdin, NULL);
            
        //     // 主线程继续执行其他业务逻辑
        //     char *query = qcgireq_getquery(Q_CGI_POST);

        //     pthread_join(tid, NULL);

        // pthread_mutex_lock(&webServerCtrl.mutex);

        bzero(top_html_str, sizeof(top_html_str));
        bzero(left_html_str, sizeof(left_html_str));
        bzero(right_html_str, sizeof(right_html_str));
        //pstr = cjson_cgi_GET_getStrValue("CMD");
        char *cmd = tempBuffer; 
        char *req_method = getenv("REQUEST_METHOD");

        char *pt = tempBuffer; 
                        
        //cjson_cgi_getPostStr(&pt);

        //char *query = qcgireq_getquery(Q_CGI_POST);
        
        FPRINTF_LOG(DEBUG_PATH,"qcgireq_getquery = %s----req_method = %s----pt = %s-----%s----%s----%s---=%d\r\n","query",req_method, pt, getenv("REQUEST_URI"), getenv("PATH_INFO"),getenv("QUERY_STRING"),get_request_method_type(req_method));

        //qentry_t *req =  qcgireq_parse(NULL, (Q_CGI_T)0);  
        //DEBUG_LOG(DEBUG_PATH,DEBUG,"Error in allocating memory \n");
        // printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
        // printf("<p style=\"text-align:center; font-size:18px\">1111!!!</p>");

        sqlite3 *db;
        char *err_msg = 0;

        int rc = sqlite3_open("mydatabase.db", &db);

        FPRINTF_LOG(DEBUG_PATH,"sqlite3_open = %d\r\n",rc);

        add_handler(default_handler);
        add_handler(simple);
        //add_handler(getNetworkSideBand);
        //int getNetworkSideBand();
        
        //handle_restservice();

        // printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
        // printf("<p style=\"text-align:center; font-size:18px\">需要重新登录!!!</p>");
        /*
        switch (get_request_method_type(query))
        {
            case 0:
                //handle_post_task();
                break;
            case 1:
                //handle_post_task();
                break;
            case 2:
                //handle_post_task();
                break;
            case 4:
                //handle_post_task();
                break;
            default:
                break;
        }
        */

        // // qcgires_download(req, "/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/src/debug/debug.txt", "application/octet-stream;charset=utf-8");
        // // req->free(req);
        // // display_menu_log_detail(RIGHT_HTML_BUFFER);






        // pstr = cjson_cgi_GET_getStrValue("CMD");


        // webcmd = (int)web_str2cmd(pstr);
        
        // //GET request method
        // if((req_method != NULL)&&(!strcmp("GET",req_method)))
        // {
        //     username = cjson_cgi_GET_getStrValue("USERNAME");
        //     password = cjson_cgi_GET_getStrValue("PASSWORD");
        // }

        // //POS request method
        // // cjson_cgi_getPostStr(&cmd);
        // // if((req_method != NULL)&&(!strcmp("POST",req_method))&&(cmd!=NULL))
        // // {
        // //     webcmd = (int)web_str2cmd(cjson_cgi_POST_getStrValue(cmd,"CMD"));
        // //     username = cjson_cgi_POST_getStrValue(cmd,"USERNAME");
        // //     password = cjson_cgi_POST_getStrValue(cmd,"PASSWORD");
        // // }


        // if ((webcmd != WEB_CMD_HEARTBEAT) &&
        //     ((ret = login_ok_already(webcmd, username, password)) != 1))
        // { // not login ok
        //     if (ret == 0)
        //     {
        //         printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
        //         printf("<p style=\"text-align:center; font-size:18px\">需要重新登录!!!</p>");
        //     }
        //     if (ret == -1)
        //     {
        //         printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
        //         printf("<p style=\"text-align:center; font-size:18px\">登录用户名密码错误!!!</p>");
        //     }

        //     goto CGI_FINISH;
        // }

        // switch (webcmd)
        // {
        //     case WEB_CMD_HEARTBEAT:
        //     {
        //         printf("%s\n\n","Content-Type:text/html;charset=utf-8");
        //         printf("heartbeat %s",cjson_cgi_GET_getStrValue("SELECT"));
        //         goto CGI_FINISH;
        //     }

        //     case WEB_CMD_HOME_PAGE:
        //     case WEB_CMD_LOGIN:
        //     {
        //         display_config_ui(left_html_str, cjson_cgi_GET_getStrValue("SELECT"));
        //         web_html_ui_select(top_html_str,left_html_str,right_html_str);
        //         goto CGI_FINISH;
        //     }
        //     break;
        //     case WEB_CMD_MENU:
        //     {
        //         display_config_menu(left_html_str, cjson_cgi_GET_getStrValue("SELECT"));
                
        //         menu_select select;

        //         if(!right_html_str) return -1;

        //         if(!cjson_cgi_GET_getStrValue("SELECT")) select=MENU_DEVICE;
        //         else select=(menu_select)atoi(cjson_cgi_GET_getStrValue("SELECT"));

        //         switch(select)
        //         {
        //             case MENU_DEVICE:
        //             {
        //                 char *pt = tempBuffer; 
                        
        //                 cjson_cgi_getPostStr(&pt);
        //                 if((!strcmp("POST", getenv("REQUEST_METHOD"))&&(pt!=NULL)))
        //                 {
        //                     /* 请求的目的地址 */
        //                     FPRINTF_LOG(DEBUG_PATH,"%s---%s---%s\r\n", web_cmd2str((web_cmd_t)WEB_CMD_MENU), menulist[MENU_DEVICE].name, getenv("REQUEST_URI"));
                            
        //                     display_menu_device_writeStatus("/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/src/debug/led", cjson_cgi_POST_getStrValue(pt,"LED"));

        //                     display_menu_device_writeStatus("/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/src/debug/beep", cjson_cgi_POST_getStrValue(pt,"BEEP"));
        //                 }
        //                 display_menu_device_detail(RIGHT_HTML_BUFFER);
        //             }
        //             break;
        //             case MENU_DATA:
        //             {
        //                 display_menu_data_detail(RIGHT_HTML_BUFFER);
        //             }
        //             break;
        //             case MENU_LOG:
        //             {
        //                 display_menu_log_detail(RIGHT_HTML_BUFFER);
        //             }
        //             break;
        //             case MENU_USER:   
        //             {
        //             }
        //             break;	
        //             case MENU_UPDATEPSD:
        //             {
        //                 char *pt = tempBuffer; 
        //                 int status_code = 404;

        //                 cjson_cgi_getPostStr(&pt);
        //                 if((!strcmp("POST", getenv("REQUEST_METHOD"))&&(pt!=NULL)))
        //                 {
        //                     char buffer[MAX_BUFFER_SIZE]={0};
        //                     char *pstr = NULL;
        //                     pstr = buffer;
        //                     fread_file(LOGIN_PATH,&pstr);

        //                     FPRINTF_LOG(DEBUG_PATH,"%s---%s---%s\r\n", web_cmd2str((web_cmd_t)WEB_CMD_MENU), menulist[MENU_UPDATEPSD].name, getenv("REQUEST_URI"));
                            
        //                     cJSON *json = cJSON_Parse(pstr);
                            
        //                     // cJSON_GetObjectItem(json,"int")->valueint = 2;
        //                     // cJSON_GetObjectItem(json,"float")->valuedouble = 2.0;
        //                     strcpy(cJSON_GetObjectItem(json,"password")->valuestring,cjson_cgi_POST_getStrValue(pt,"NPSD1"));

        //                     //修改对象的值
        //                     //cJSON_ReplaceItemInObject(json,"word",cJSON_CreateString("password"));
        //                     FPRINTF_LOG(DEBUG_PATH,"%s\r\n",cJSON_Print(json));

        //                     int ret = write_file(LOGIN_PATH,"w+",cJSON_Print(json));

        //                     if(ret > 0){
        //                       status_code = 200;
        //                       FPRINTF_LOG(DEBUG_PATH,"write %d bytes succeed.\r\n",ret);
        //                     }

        //                     /* 设置Cookie时，需在 printf("Content-type:text/html\n\n"); 前设置： */
        //                     printf("Set-Cookie: username=%s;\nSet-Cookie: password=%s;\n","username","password");
        //                     //printf("<div><input type=\"hidden\" id=\"rid\" value=\"%s\"></input></div>","1");
        //                     /* 设置状态码 */
        //                     //printf("Status:404\n\n");

        //                     /* 跳转html */
        //                     //printf("Location:/test.html\n\n");   

        //                     FPRINTF_LOG(DEBUG_PATH,"%s---\r\n",getenv("HTTP_COOKIE"));
    
        //                     cJSON_Delete(json);
        //                 }

        //                 free((void*)pstr);                                                          
        //                 free(pt);
        //                 display_menu_updatepsd_detail(RIGHT_HTML_BUFFER);
        //                 if(status_code == 200){
        //                     sprintf(RIGHT_HTML_BUFFER,"<script src=\"/demo_test_fastcgi/cgi-bin/js/dashboard.js\"></script><script language=\"javascript\">alert(\"修改成功!\");clearAllCookie()</script>");
        //                 }   
        //             }
        //             break;  
        //             case MENU_EXIT:
        //             {
        //                 sprintf(RIGHT_HTML_BUFFER,"<script src=\"/demo_test_fastcgi/cgi-bin/js/dashboard.js\"></script><script language=\"javascript\">window.location.href = \"index.html\";clearAllCookie()</script>");
        //                 //display_menu_acqclient_detail(RIGHT_HTML_BUFFER);   
        //                 //<a href="#" target="_top">退出</a>
        //             }     
        //             break;
        //             case MENU_USER1:
        //             {
        //                 sprintf(RIGHT_HTML_BUFFER,"<script src=\"/demo_test_fastcgi/cgi-bin/js/dashboard.js\"></script><script language=\"javascript\">alert(\"还没完成噢!\");</script></script>");    
        //             }
        //             break;	
        //             case MENU_USER2:
        //             {
        //                 sprintf(RIGHT_HTML_BUFFER,"<script src=\"/demo_test_fastcgi/cgi-bin/js/dashboard.js\"></script><script language=\"javascript\">alert(\"还没完成噢!\");</script></script>");    
        //             }
        //             break;	
        //             case MENU_DOWNLOAD_LOG:
        //             {    
        //                 //printf("%s\n\n", "application/octet-stream;charset=utf-8");                  
        //                 qentry_t *req =  qcgireq_parse(NULL, (Q_CGI_T)0);  
        //                 qcgires_download(req, "/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/src/debug/debug.txt", "application/octet-stream;charset=utf-8");
        //                 req->free(req);
        //                 display_menu_log_detail(RIGHT_HTML_BUFFER);
                        
        //                 sprintf(RIGHT_HTML_BUFFER,"<script src=\"/demo_test_fastcgi/cgi-bin/js/dashboard.js\"></script><script language=\"javascript\">alert(\"=====\");</script></script>");    
        //             }
        //             break;	
        //             case MENU_UPLOAD_FILE:
        //             {    
        //                 // Parse queries.
        //                 qentry_t *req = qcgireq_parse(NULL, (Q_CGI_T)0);

        //                 // get queries
        //                 const char *text = req->getstr(req, "text", false);
        //                 const char *filedata   = req->getstr(req, "binary", false);
        //                 int filelength = req->getint(req, "binary.length");
        //                 const char *filename   = req->getstr(req, "binary.filename", false);
        //                 const char *contenttype = req->getstr(req, "binary.contenttype", false);

        //                 // check queries
        //                 if (text == NULL) qcgires_error(req, "Invalid usages.");
        //                 if (filename == NULL || filelength == 0) {
        //                     qcgires_error(req, "Select file, please.");
        //                 }

        //                 char  filepath[1024];
        //                 sprintf(filepath, "%s/%s", BASEPATH, filename);

        //                 if (savefile(filepath, filedata, filelength) < 0) {
        //                     qcgires_error(req, "File(%s) open fail. Please make sure CGI or directory has right permission.",
        //                                 filepath);
        //                 }

        //                 // result out
        //                 qcgires_setcontenttype(req, "text/html");
        //                 printf("You entered: <b>%s</b>\n", text);
        //                 printf("<br><a href=\"%s\">%s</a> (%d bytes, %s) saved.",
        //                     filepath, filename, filelength, contenttype);

        //                 // dump
        //                 printf("\n<p><hr>--[ DUMP INTERNAL DATA STRUCTURE ]--\n<pre>");
        //                 req->print(req, stdout, false);
        //                 printf("\n</pre>\n");

        //                 // de-allocate
        //                 req->free(req);

        //             }
        //             break;	
                    	 
        //             default:;  
        //         }
                  
        //         web_html_ui_select2(top_html_str,left_html_str,right_html_str);
        //     }
        //     break;
		// 	case WEB_CMD_FLUSH_DATA:
		// 	{  
        //         char *pack_buffer=left_html_str;
        //         //printf("%s\n\n","Content-Type:text/html;charset=gb2312");
        //         printf("%s\n\n","Content-Type:text/html;charset=utf-8");
        //         //printf("login success");  
        //         //package formate
        //         printf("{\"polcodes\":[{\"UserName\":\"123\",\"Sex\":\"456\"},{\"UserName\":\"789\",\"Sex\":\"0\"}]}");
        //         //rtdata_flush_package(pack_buffer);
        //         //printf("%s",pack_buffer);  
        //         goto CGI_FINISH;
		// 	}
		// 	break;		
        //     case WEB_CMD_FLUSH_STATUS:  
        //     {
        //         static int count = 0;  
        //         char *pack_buffer = right_html_str;  
        //         // printf("%s\n\n","Content-Type:text/html;charset=gb2312");
        //         printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
        //         // printf("login success %d",count++);  
        //         // package formate
        //         // printf("{\"polcodes\":[{\"UserName\":\"123\",\"Sex\":\"456\"},{\"UserName\":\"789\",\"Sex\":\"0\"}]}");
        //         status_flush_package(pack_buffer);   
        //         printf("%s", pack_buffer);        
        //         // NOTE :: continue below    
        //         goto CGI_FINISH;           
        //     }
        //     default: 
        //         printf("%s\n\n", "Content-Type:text/html;charset=utf-8");
        //         printf("NO such cmd %s !!!", cgi["CMD"]);
        //         goto CGI_FINISH;  
        //     }
                 serve_forever();
        CGI_FINISH:
            //cgi.finish();  
            pthread_mutex_unlock(&webServerCtrl.mutex);  
    // }
    return 0;
}