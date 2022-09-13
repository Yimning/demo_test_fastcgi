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

#define RIGHT_HTML_BUFFER (right_html_str+strlen(right_html_str))
#define JAVASCRIPT_HTML_BUFFER (javascript_html_str+strlen(javascript_html_str))

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
				
            }
			//display_menu_device_detail(RIGHT_HTML_BUFFER);
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
