/*
 * @Author: Yimning
 * @Date: 2022-08-05 12:40:55
 */
#ifndef WEB_MENU_DEVICE
#define WEB_MENU_DEVICE

extern int display_menu_device_detail(char *right_html_str);
extern int display_menu_device_readStatus(char *filename,char *databuf);
extern int display_menu_device_writeStatus(char *filename,char *status);

typedef struct Device {
	int statusCode;
    char *status;
    char *img;
    char *key;
}Device;

#endif

