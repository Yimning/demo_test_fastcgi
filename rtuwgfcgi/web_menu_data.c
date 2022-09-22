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
#include "web_menu_data.h"
#include "web_menu_device.h"
#include "getparameter.h"
#include "api.h"


#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"


#define RIGHT_HTML_BUFFER (right_html_str+strlen(right_html_str))

int display_menu_data_detail(char *right_html_str)
{
	if(!right_html_str) return -1;
	char databuf[256];

	Device temp;
	Device humid;

	int temp_status = display_menu_device_readStatus("/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/rtuwgfcgi/debug/beep",databuf);
	if(!strncmp(databuf,"0",1))
	{
			temp.statusCode = 0;
			temp.status="温度**";
			temp.img="temp_grep.png";
			temp.key="TEMP";
	}else
	{
			temp.statusCode = 1;
			temp.status="温度##";
			temp.img="temp_color.png";
			temp.key="TEMP";
	};

	int humid_status = display_menu_device_readStatus("/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/rtuwgfcgi/debug/beep",databuf);
	if(!strncmp(databuf,"0",1))
	{
			humid.statusCode = 0;
			humid.status="湿度**";
			humid.img="humid_grep.png";
			humid.key="HUMID";
	}else
	{
			humid.statusCode = 1;
			humid.status="湿度##";
			humid.img="humid_color.png";
			humid.key="HUMID";
	};

		sprintf(RIGHT_HTML_BUFFER,"\
	        <div class=\"content2\">\
				<form action=\"/demo_test_fastcgi/fcgitest.fcgi?CMD=MENU&SELECT=0\" method=\"POST\" enctype=\"application/x-www-form-urlencoded;charset=UTF-8\" name=\"form3\" id=\"form3\">\
					<div class=\"content_item\">\
						<input type=\"hidden\" name=\"LED\" value=\"%d\">\
					    <input type=\"hidden\" name=\"BEEP\" value=\"%d\">\
						<img width=\"200\" height=\"200\" border=\"0\" id=tempimg src=\"/demo_test_fastcgi/cgi-bin/images/%s\" onclick=\"\">\
						<p class=\"title\" style=\"text-align:center\">\
								%s\
						</p>\
					</div>\
				</form>\      
			</div>\
			",temp.statusCode,temp.statusCode==0?1:0,temp.img,temp.status);
		sprintf(RIGHT_HTML_BUFFER,"\
	        <div class=\"content2\">\
				<form action=\"/demo_test_fastcgi/fcgitest.fcgi?CMD=MENU&SELECT=0\" method=\"POST\" enctype=\"application/x-www-form-urlencoded;charset=UTF-8\" name=\"form4\" id=\"form4\">\
					<div class=\"content_item\">\
						<input type=\"hidden\" name=\"LED\" value=\"%d\">\
					    <input type=\"hidden\" name=\"BEEP\" value=\"%d\">\
						<img width=\"200\" height=\"200\" border=\"0\" id=humidimg src=\"/demo_test_fastcgi/cgi-bin/images/%s\" onclick=\"\">\
						<p class=\"title\" style=\"text-align:center\">\
								%s\
						</p>\
					</div>\
				</form>\      
			</div>\
			",temp.statusCode,temp.statusCode==0?1:0,humid.img,humid.status);
	return 0;
}
