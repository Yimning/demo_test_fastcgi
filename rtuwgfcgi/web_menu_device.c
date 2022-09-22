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
#include "getparameter.h"
#include "api.h"


#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"

#define RIGHT_HTML_BUFFER (right_html_str+strlen(right_html_str))


int display_menu_device_detail(char *right_html_str)
{
	if(!right_html_str) return -1;
	char databuf[256];
	
	Device led;
	Device beep;

	int led_status = display_menu_device_readStatus("/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/rtuwgfcgi/debug/led",databuf);
	if(!strncmp(databuf,"0",1))
	{
			led.statusCode = 0;
			led.status="LED灯已关";
			led.img="led_off.png";
			led.key="LED";
	}else
	{
			led.statusCode = 1;
			led.status="LED灯已开";
			led.img="led_on.png";
			led.key="LED";
	};
	
	int beep_status = display_menu_device_readStatus("/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/rtuwgfcgi/debug/beep",databuf);
	if(!strncmp(databuf,"0",1))
	{
			beep.statusCode = 0;
			beep.status="蜂鸣器已关";
			beep.img="beep_off.png";
			beep.key="BEEP";
	}else
	{
			beep.statusCode = 1;
			beep.status="蜂鸣器已开";
			beep.img="beep_on.png";
			beep.key="BEEP";
	};

	sprintf(RIGHT_HTML_BUFFER,"\
		    <div>\
				<font size=\"3\" color=\"#cc0000\">\
					<marquee class=\"marquee\" scrollamount=\"6\" direction=\"up\" Align=\"Middle\" >\
						<p style=\"text-align: center\">温馨提示:点击图片可实现控制设备开关噢!</p>\
					</marquee>\
				</font>\
			</div>\
	        <div class=\"content2\">\
				<form action=\"/demo_test_fastcgi/fcgitest.fcgi?CMD=MENU&SELECT=1\" method=\"POST\" enctype=\"application/x-www-form-urlencoded;charset=UTF-8\" name=\"form1\" id=\"form1\">\
					<div class=\"content_item\">\
					    <input type=\"hidden\" name=\"LED\" value=\"%d\">\
						<input type=\"hidden\" name=\"BEEP\" value=\"%d\">\
						<img width=\"200\" height=\"200\" border=\"0\" id=ledimg src=\"/demo_test_fastcgi/cgi-bin/images/%s\" onclick=\"document.form1.submit()\">\
						<p class=\"title\" style=\"text-align:center\">\
								%s\
						</p>\
					</div>\
				</form>\      
			</div>\
			",led.statusCode==0?1:0,beep.statusCode,led.img,led.status);
		sprintf(RIGHT_HTML_BUFFER,"\
	        <div class=\"content2\">\
				<form action=\"/demo_test_fastcgi/fcgitest.fcgi?CMD=MENU&SELECT=1\" method=\"POST\" enctype=\"application/x-www-form-urlencoded;charset=UTF-8\" name=\"form2\" id=\"form2\">\
					<div class=\"content_item\">\
						<input type=\"hidden\" name=\"LED\" value=\"%d\">\
					    <input type=\"hidden\" name=\"BEEP\" value=\"%d\">\
						<img width=\"200\" height=\"200\" border=\"0\" id=ledimg src=\"/demo_test_fastcgi/cgi-bin/images/%s\" onclick=\"document.form2.submit()\">\
						<p class=\"title\" style=\"text-align:center\">\
								%s\
						</p>\
					</div>\
				</form>\      
			</div>\
			",led.statusCode,beep.statusCode==0?1:0,beep.img,beep.status);
	return 0;
}
