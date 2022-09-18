/*
 * @Author: Yimning 
 * @Date: 2022-08-01 00:39:26
*/
#ifndef WEB_CONFIG_UI
#define WEB_CONFIG_UI

#include "web_config_menu.h"

extern int display_config_ui(char *left_html_str,const char *select);

extern int display_config_header(char *left_html_str,const char *select);



static struct menu_list menulist[]={
	{
		.selstr="DEVICE",
		.image_path="fas fa-heart",
		.color="rgb(255, 71, 38)",
		.name="设备控制",
		.select=MENU_DEVICE,
		.status="active",
		.child_existence=0,
	},		
	{
		.selstr="DATA",
		.image_path="fas fa-chart-bar",
		.color="rgb(0, 128, 0)",
		.name="数据分析",
		.select=MENU_DATA,
		.status="active",
		.child_existence=0,
	},
	{
		.selstr="LOG",
		.image_path="fas fa-file-alt",
		.color="rgb(98, 101, 114)",
		.name="日志记录",
		.select=MENU_LOG,
		.status="active",
		.child_existence=0,
	},
	{
		.selstr="USER",
		.image_path="fas fa-user",
		.color="rgb(0, 183, 255)",
		.name="用户详细信息",
		.select=MENU_USER,
		.status="active",
		.child_existence=1,
		.child={
			{
				.selstr="USER1",
				.name="用户信息",
				.select=MENU_USER1,
				.status="",
			},
			{
				.selstr="USER2",
				.name="手机号码",
				.select=MENU_USER2,
				.status="",
			},
		}
	},
	{
		.selstr="UPDATEPSD",
		.image_path="fas fa-unlock",
		.color="rgb(0, 183, 214)",
		.name="修改密码",
		.select=MENU_UPDATEPSD,
		.status="active",
		.child_existence=0,
	},
	{
		.selstr="EXIT",
		.image_path="fas fa-outdent",
		.color="rgb(136, 93, 192)",
		.name="退出登录",
		.select=MENU_EXIT,
		.status="active",
		.child_existence=0,
	},	
};


#endif
