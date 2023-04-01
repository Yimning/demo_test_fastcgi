#ifndef RTUWG_MENU_SELFINFO_DETAIL
#define RTUWG_MENU_SELFINFO_DETAIL
#include "rtuwg_ui_parameter.h"

#define UPGRADE_FILE_MAX_COUNT 10

struct upgrade_mnger{
	char file_name[UPGRADE_FILE_MAX_COUNT][50];
	int file_size[UPGRADE_FILE_MAX_COUNT];

	int curr_file_count;
};

struct selfinfo_mnger{
	struct K37aInfoStr selfinfo,selfinfoBak; 
	struct K37aVersionAllStr softVerInfo;
	char *selfinfoParListBuffer;

	struct upgrade_mnger upgrademnger;

	int decimal_point;
};


extern int display_menu_selfinfo_detail(char *right_html_str);
extern int init_selfinfo_mnger();
extern int save_self_infor(char *right_html_str,struct K37aInfoStr *selfinfo,int decimal_point);
extern int init_selfinfo_str(struct K37aInfoStr *selfinfo);
extern int display_software_information(char *right_html_str);
extern int reboot_rtuwg(char *right_html_str);
extern int power_off_rtuwg(char *right_html_str);
extern int display_upgrade_detail(char *right_html_str);
extern int config_upgrade_detail(char *right_html_str,char *filename,int filesize);
extern int upgrade_rtuwg(char *right_html_str);
extern int reset_rtuwg(char *right_html_str);

extern int devinf_password_self_info();
extern char *devinfo_get_user_name();
extern char *devinfo_get_passwd();


#endif
