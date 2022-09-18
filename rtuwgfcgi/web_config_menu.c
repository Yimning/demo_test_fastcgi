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
#include "web_config_ui.h"

#define LEFT_HTML_BUFFER (left_html_str+strlen(left_html_str))


// int display_config_menu(char *left_html_str,const char *select)
// {
// 	int i=0;
// 	if(!left_html_str) return -1;	

// 	sprintf(LEFT_HTML_BUFFER,"<table width=\"100%\" border=\"0\" cellspacing=\"0\">");

// 	for(i=0;i<ARRAY_SIZE(menulist);i++)
// 	{
// 		sprintf(LEFT_HTML_BUFFER,"<tr  bgcolor=\"%s\">",(i%2==0) ? "#d7e4ed" : "#f6f5ec");
// 		sprintf(LEFT_HTML_BUFFER,"<style type=\"text/css\">");
// 		sprintf(LEFT_HTML_BUFFER,".color{color:#000000; text-decoration:none;}");
// 		sprintf(LEFT_HTML_BUFFER,".color:visited{color:#000000; text-decoration:none;}");
// 		sprintf(LEFT_HTML_BUFFER,".color:hover{color:#000000; text-decoration:underline;}");
// 		sprintf(LEFT_HTML_BUFFER,"</style>");
		
// 		sprintf(LEFT_HTML_BUFFER,"<td><a href=\"/cgi-bin/usr/rtuwg.fcgi?CMD=MENU&SELECT=%d\" style=\"text-decoration:none;font-size :20px;\" class=\"color\">",menulist[i].select);
// 		sprintf(LEFT_HTML_BUFFER,"<table><tr>");
// 		sprintf(LEFT_HTML_BUFFER,"<td><img height=50 width=50/><i class=\"%s\"></i></td>",menulist[i].image_path);
// 		sprintf(LEFT_HTML_BUFFER,"<td style=\"vertical-align:middle;\">%s</td>",menulist[i].name);
// 		sprintf(LEFT_HTML_BUFFER,"</tr></table>");
// 		sprintf(LEFT_HTML_BUFFER,"</a></td>");
//     	sprintf(LEFT_HTML_BUFFER,"</tr>");
// 	}
// 	sprintf(LEFT_HTML_BUFFER,"</table>");
// 	return 0;
// }

int display_config_menu(char *left_html_str,const char *select)
{
	int i=0,j=0;
	if(!left_html_str) return -1;	

	sprintf(LEFT_HTML_BUFFER,"<ul class=\"siderbar_menu\">");

	for(i=0;i<ARRAY_SIZE(menulist);i++)
	{
		sprintf(LEFT_HTML_BUFFER,"<li class=%s>", atoi(select)==menulist[i].select?menulist[i].status:"");
		
		sprintf(LEFT_HTML_BUFFER,"<a href=\"/demo_test_fastcgi/fcgitest.fcgi?CMD=MENU&SELECT=%d\">",menulist[i].select);

		sprintf(LEFT_HTML_BUFFER,"<div class=\"icon\">\
							          <span style=\"font-size: 1.5em; color: %s;\">\
          									<i class=\"%s\"></i>\
          								</span>\
                                 </div>",menulist[i].color,menulist[i].image_path);
		sprintf(LEFT_HTML_BUFFER,"<div class=\"title\">%s</div>",menulist[i].name);
		if(menulist[i].child_existence == 1){
		                 sprintf(LEFT_HTML_BUFFER,"<div class=\"arrow\">\
						 		<span style=\"font-size: 1.5em;\">\
                               		<i class=\"fas fa-chevron-down\"></i>\
								</span>\
                            </div>");
		}
		sprintf(LEFT_HTML_BUFFER,"</a>");

		if(menulist[i].child_existence == 1){
			menulist[i].status="active";
		    sprintf(LEFT_HTML_BUFFER,"<ul class=\"accordion\">");
			for(j=0;j<2;j++){
				sprintf(LEFT_HTML_BUFFER,"<li><a href=\"/demo_test_fastcgi/fcgitest.fcgi?CMD=MENU&SELECT=%d\" class=\"%s\">%s</a>",menulist[i].child[j].select,menulist[i].child[j].status,menulist[i].child[j].name);
			}
			sprintf(LEFT_HTML_BUFFER,"</ul>");
		}

		sprintf(LEFT_HTML_BUFFER,"</li>");

	}
	sprintf(LEFT_HTML_BUFFER,"</ul>");
	return 0;
}

int init_config_menu()
{/*left page*/



}




int display_console_printf(char *javascript_html_str)
{
printf("\
    <script>\
        console.log(\"%s\")\
    </script>\
",javascript_html_str);
	return 0;
}
//alert(\"hello world\")  //弹窗