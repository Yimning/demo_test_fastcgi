/*
 * @Author: Yimning
 * @Date: 2022-08-05 12:40:55
 */
#ifndef WEB_CONFIG_MENU
#define WEB_CONFIG_MENU

#define CHILD_NODE_MAXLEN 5

typedef enum menu_select_t{
		MENU_DEVICE,
		MENU_DATA,
		MENU_LOG,
		MENU_USER,
		MENU_UPDATEPSD,
		MENU_EXIT,
		MENU_USER1,  //6
		MENU_USER2,  //7
}menu_select;

struct S
{
    int a;
    char c;
    double d;
};
struct T
{
    struct S s; //结构体嵌套
    char name[20];
    int num;
};

typedef struct menu_list_child {
	const char *selstr;
	const char *name;
	const int select;
	const char *status;
}childNode;

typedef struct menu_list {
	const char *selstr;
	const char *image_path;
	const char * color;
	const char *name;
	const int select;
	const char *status;
	const int child_existence;
	childNode child[CHILD_NODE_MAXLEN];
}menu_list;



extern int init_config_menu();
extern int display_config_menu(char *left_html_str,const char *select);

extern int display_console_printf(char *javascript_html_str);

#endif

