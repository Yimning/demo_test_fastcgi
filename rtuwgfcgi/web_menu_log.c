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
#include "api.h"

#define RIGHT_HTML_BUFFER (right_html_str+strlen(right_html_str))


int display_menu_log_detail(char *right_html_str)
{
	char tempBuffer[MAX_BUFFER_SIZE] = {0};
	char *pstr = tempBuffer;
	fread_file(DEBUG_PATH,&pstr);
	//X-LIGHTTPD-send-file  
	//printf("X-Sendfile: %s 0-\r\n\r\n", DEBUG_PATH);
	if(!right_html_str) return -1;
	sprintf(RIGHT_HTML_BUFFER,"\
	     <div class=\"content\">\
		    <div>\
				<font size=\"3\" color=\"#cc0000\">\
						<pre style=\"text-align: left\">%s</pre>\
				</font>\
			</div>\
          </div>\
		",pstr);
	free(pstr);
	return 0;
}
