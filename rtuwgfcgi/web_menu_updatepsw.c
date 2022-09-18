/*
 * @Author: Yimning
 * @Date: 2022-08-09 13:40:55
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "webcmd.h"
#include "web_config_menu.h"
#include "web_config_menu_detail.h"
#include "web_menu_updatepsw.h"
#include "api.h"

#define RIGHT_HTML_BUFFER (right_html_str+strlen(right_html_str))


int display_menu_updatepsd_detail(char *right_html_str)
{
	char tempBuffer[MAX_BUFFER_SIZE] = {0};
	char *pstr = tempBuffer;
	fread_file(DEBUG_PATH,&pstr);

	if(!right_html_str) return -1;
	sprintf(RIGHT_HTML_BUFFER,"\
	     <div class=\"content\">\
		 	<div/>\
                <form class=\"col-12\" name=\"click_submit\" method=\"POST\" action=\"\">\
                    <div class=\"form-group\">\
						<i class=\"form-unlock\"></i>\
                        <input type=\"password\" class=\"form-control\" placeholder=\"输入新密码\" name=\"NPSD\" id=\"npid\"\
                            required=\"required\">\
                    </div>\
                    <div class=\"form-group\">\
                        <i class=\"form-unlock\"></i>\
                        <input type=\"password\" class=\"form-control\" placeholder=\"再次输入新密码\" name=\"NPSD1\" id=\"npsdid\"\
                            required=\"required\" onkeydown=\"ok_keyup_submit(event);\">\
                    </div>\
                </form>\
			<div/>\
			<div>\
				<button class=\"btn btn-primary btn1\" onclick=\"pwdIn()\">\
                        <i class=\"fas fa-user-lock\"></i>\
                        确定</button>\
                <button class=\"btn btn-success btn2\" onclick=\"cancel()\">\
                        <i class=\"fas fa-undo\"></i>\
                        取消</button>\
			<div/>\
          </div>\
		");
	free(pstr);
	return 0;
}
