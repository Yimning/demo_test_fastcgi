/*
 * @Author: Yimning
 * @Date: 2022-08-08 13:40:55
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "webcmd.h"
#include "web_config_menu.h"
#include "web_config_menu_detail.h"
#include "web_menu_device.h"
#include "web_menu_data.h"
#include "fprintf.h"
#include "getparameter.h"

#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"


#define RIGHT_HTML_BUFFER (right_html_str+strlen(right_html_str))


int display_menu_config_detail(char *right_html_str,const char *selstr)
{
	menu_select select;

	if(!right_html_str) return -1;

	if(!selstr) select=MENU_DEVICE;
	else select=(menu_select)atoi(selstr);

	switch(select)
	{
		case MENU_DEVICE:
		{
			if (!strcmp("POST", getenv("REQUEST_METHOD")))
            { 
				CONSOLELOG(DEBUG_PATH,"getenv(REQUEST_METHOD)",getenv("REQUEST_METHOD"));
				
				//CONSOLELOG(DEBUG_PATH,"---cjson_cgi_POST_getStrValue---",cjson_cgi_POST_getStrValue("LED"));
				 	/* 说明返回内容类型为html文本 */
	printf("Content-Type:text/html\n\n");
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

				FPRINTF_LOG(DEBUG_PATH,"post type:%s,len:%d, data:%s\r\n", content_type, len, dat_buf);
        }
    }

	
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
			//sprintf(RIGHT_HTML_BUFFER,"base");
			//display_menu_base_detail(RIGHT_HTML_BUFFER);
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

	return 0;
}
