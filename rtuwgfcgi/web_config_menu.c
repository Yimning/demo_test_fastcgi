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