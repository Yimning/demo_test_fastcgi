#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "webcmd.h"
#include "web_config_menu.h"
#include "web_config_ui.h"

#define LEFT_HTML_BUFFER (left_html_str+strlen(left_html_str))

#if 0
static struct menu_list menulist[]=
{
	{
		.selstr="DEVICE",
		.image_path="fas fa-heart",
		.color="rgb(255, 71, 38)",
		.name="设备控制",
		.select=MENU_DEVICE,
	},		
	{
		.selstr="DATA",
		.image_path="fas fa-chart-bar",
		.color="rgb(0, 128, 0)",
		.name="数据分析",
		.select=MENU_DATA,
	},
	{
		.selstr="LOG",
		.image_path="fas fa-file-alt",
		.color="rgb(98, 101, 114)",
		.name="日志记录",
		.select=MENU_LOG,
	},
	{
		.selstr="USER",
		.image_path="fas fa-user",
		.color="rgb(0, 183, 255)",
		.name="用户详细信息",
		.select=MENU_USER,
	},
	{
		.selstr="UPDATEPSD",
		.image_path="fas fa-unlock",
		.color="rgb(0, 183, 214)",
		.name="修改密码",
		.select=MENU_UPDATEPSD,
	},
	{
		.selstr="EXIT",
		.image_path="fas fa-outdent",
		.color="rgb(136, 93, 192)",
		.name="退出登录",
		.select=MENU_EXIT,
	},	
};
#endif

int display_config_ui(char *left_html_str,const char *select)
{
	int i=0,j=0;
	if(!left_html_str) return -1;	

	sprintf(LEFT_HTML_BUFFER,"<table width=\"100%\" border=\"0\" cellspacing=\"0\">");
	sprintf(LEFT_HTML_BUFFER,"<style type=\"text/css\">");
	sprintf(LEFT_HTML_BUFFER,".color{color:#000000; text-decoration:none;}");
	sprintf(LEFT_HTML_BUFFER,".color:visited{color:#000000; text-decoration:none;}");
	sprintf(LEFT_HTML_BUFFER,".color:hover{color:#000000; text-decoration:underline;}");
	sprintf(LEFT_HTML_BUFFER,"</style>");
		
	for(i=0;i<(ARRAY_SIZE(menulist)/3+1);i++)
	{
		sprintf(LEFT_HTML_BUFFER,"<tr  bgcolor=\"%s\">",(i%2==0) ? "#adddff" : "#d7e4ed");

		for(j=0;j<3 && ((i*3+j)<ARRAY_SIZE(menulist));j++)
		{
			sprintf(LEFT_HTML_BUFFER,"<td><a href=\"/demo_test_fastcgi/fcgitest.fcgi?CMD=MENU&SELECT=%d\" style=\"text-decoration:none;font-size :20px;\" class=\"color\">",menulist[i*3+j].select);
			sprintf(LEFT_HTML_BUFFER,"<table><tr>");
			sprintf(LEFT_HTML_BUFFER,"<td>\
							<div class=\"icon\">\
							          <span style=\"font-size: 3em; color: %s;\">\
          									<i class=\"%s\"></i>\
          								</span>\
                            </div>\
							</td>",menulist[i*3+j].color,menulist[i*3+j].image_path);
			sprintf(LEFT_HTML_BUFFER,"<td style=\"vertical-align:middle;\">%s</td>",menulist[i*3+j].name);
			sprintf(LEFT_HTML_BUFFER,"</tr></table>");
			sprintf(LEFT_HTML_BUFFER,"</a></td>");
		}
		
    	sprintf(LEFT_HTML_BUFFER,"</tr>");
	}
	sprintf(LEFT_HTML_BUFFER,"</table>");
	return 0;
	
}


int display_config_header(char *top_html_str,const char *select)
{
fprintf(stdout,"<!DOCTYPE HTML>\
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
                    <a href=\"#\">控制系统</a>\
                </div>\
            </div>\
        </div>\
    </div>\
</body>\
</html>\
");
	return 0;
}


