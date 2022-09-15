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
#include "web_menu_log.h"

#define RIGHT_HTML_BUFFER (right_html_str+strlen(right_html_str))


int display_menu_log_detail(char *right_html_str)
{

	if(!right_html_str) return -1;
	sprintf(RIGHT_HTML_BUFFER,"\
	     <div class=\"content\">\
		    <div>\
				<font size=\"3\" color=\"#cc0000\">\
						<p style=\"text-align: center\">%s</p>\
				</font>\
			</div>\
          </div>\
		",logstr);
	return 0;
}
