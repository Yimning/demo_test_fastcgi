#ifndef RTUWG_MENU_CAMERA_DETAIL
#define RTUWG_MENU_CAMERA_DETAIL

static char *camera_name[]={
	"camera0",
	"camera1",
	"camera2",
	"camera3",
};

#define MAX_CAMERA_NUM 4// 2

struct camera_mnger{
	struct PhotoCapStr phcap[MAX_CAMERA_NUM];
	struct PhotoCapStr phcapBak[MAX_CAMERA_NUM];
};
extern int display_menu_camera_detail(char *right_html_str);
extern int display_one_camera_detail(char *right_html_str,int camera_no);
extern int take_a_photo(char *right_html_str,int camera_no);
extern int search_photo(char *right_html_str,int page,char * sttmstr,char *endtmstr,int camera_no);
extern int config_camera(char *right_html_str,int camera_no);
extern int save_camera_parameter(char *right_html_str,struct PhotoCapStr *phcap);
extern void init_camera();
extern int display_search_photo_parameter(char *right_html_str,int camera_no);
extern int display_history_a_photo(char *right_html_str,char *photo_name,int page,char * sttmstr,char *endtmstr,int camno);

extern int play_video_sttm_endtm(char *right_html_str,int page,char * sttmstr,char *endtmstr,int camera_no);


extern int take_a_video(char *right_html_str,int camera_no);


#endif
