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

#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"


#define RIGHT_HTML_BUFFER (right_html_str+strlen(right_html_str))


int display_menu_device_readStatus(char *filename, char* databuf)
{
	int fd, retvalue=-1;
	char buf[20];
	/* 打开设备驱动 */
	fd = open(filename, O_RDWR);
	if(fd < 0){
		printf("file %s open failed!\r\n", filename);
		return -1;
	}

	/* 向文件读数据 */
	memset(buf, 0, sizeof(buf));
	retvalue = read(fd, buf, sizeof(buf));
	if(retvalue < 0){
		printf("Device Control Failed!\r\n");
		close(fd);
		return -1;
	}
	memcpy(databuf, buf, sizeof(buf));

	retvalue = close(fd); /* 关闭文件 */
	if(retvalue < 0){
		printf("file %s close failed!\r\n", filename);
		return -1;
	}
	return retvalue;
}



int display_menu_device_writeStatus(char *filename, char *status)
{
	int fd, retvalue;
	unsigned char databuf[1];

	/* 打开设备驱动 */
	fd = open(filename, O_RDWR);
	if(fd < 0){
		printf("file %s open failed!\r\n", filename);
		return -1;
	}

	databuf[0] = atoi(status);	/* 要执行的操作：打开或关闭 */

	/* 向文件写入数据 */
	retvalue = write(fd, databuf, sizeof(databuf));
	if(retvalue < 0){
		printf("Device Control Failed!\r\n");
		close(fd);
		return -1;
	}

	retvalue = close(fd); /* 关闭文件 */
	if(retvalue < 0){
		printf("file %s close failed!\r\n", filename);
		return -1;
	}
	return 0;
}



int display_menu_device_detail(char *right_html_str)
{
	if(!right_html_str) return -1;
	char databuf[256];
	
	Device led;
	Device beep;

	int led_status = display_menu_device_readStatus("/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/debug/led",databuf);
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
	
	int beep_status = display_menu_device_readStatus("/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/debug/beep",databuf);
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
				<form action=\"/demo_test_fastcgi/fcgitest.fcgi?CMD=MENU&SELECT=0\" method=\"POST\" enctype=\"application/x-www-form-urlencoded\" name=\"form1\" id=\"form1\">\
					<div class=\"content_item\">\
						<input type=\"hidden\" name=\"CMD\" value=\"MENU\">\
						<input type=\"hidden\" name=\"SELECT\" value=\"0\">\
					    <input type=\"hidden\" name=\"LED\" value=\"%d\">\
						<img width=\"200\" height=\"200\" border=\"0\" id=ledimg src=\"/demo_test_fastcgi/cgi-bin/images/%s\" onclick=\"document.form1.submit()\">\
						<p class=\"title\" style=\"text-align:center\">\
								%s\
						</p>\
					</div>\
				</form>\      
			</div>\
			",led.statusCode==0?1:0,led.img,led.status);
		sprintf(RIGHT_HTML_BUFFER,"\
	        <div class=\"content2\">\
				<form action=\"/demo_test_fastcgi/fcgitest.fcgi?CMD=MENU&SELECT=0\" method=\"POST\" enctype=\"application/x-www-form-urlencoded\" name=\"form2\" id=\"form2\">\
					<div class=\"content_item\">\
						<input type=\"hidden\" name=\"CMD\" value=\"MENU\">\
						<input type=\"hidden\" name=\"SELECT\" value=\"0\">\
					    <input type=\"hidden\" name=\"BEEP\" value=\"%d\">\
						<img width=\"200\" height=\"200\" border=\"0\" id=ledimg src=\"/demo_test_fastcgi/cgi-bin/images/%s\" onclick=\"document.form2.submit()\">\
						<p class=\"title\" style=\"text-align:center\">\
								%s\
						</p>\
					</div>\
				</form>\      
			</div>\
			",beep.statusCode==0?1:0,beep.img,beep.status);
	return 0;
}
