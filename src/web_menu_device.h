/*
 * @Author: Yimning
 * @Date: 2022-08-05 12:40:55
 */
#ifndef WEB_MENU_DEVICE_H
#define WEB_MENU_DEVICE_H

extern int display_menu_device_detail(char *right_html_str);

typedef struct Device {
	int statusCode;
    char *status;
    char *img;
    char *key;
}Device;

#endif

