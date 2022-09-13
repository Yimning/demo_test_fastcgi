
#ifndef WEBCMD
#define WEBCMD

typedef enum web_cmd_t{
	WEB_CMD_HEARTBEAT,
	WEB_CMD_LOGIN,
	WEB_CMD_HOME_PAGE,
	WEB_CMD_MENU,
	WEB_CMD_FLUSH_DATA,
	WEB_CMD_DETAIL,
	WEB_CMD_DETAIL_CONFIG,
	WEB_CMD_DETAIL_SAVE,
	WEB_CMD_FLUSH_STATUS,
	WEB_CMD_UPLOAD,
	WEB_CMD_DETAIL_GET,
	WEB_CMD_DOWNLOAD,
	WEB_CMD_CALIB,
	WEB_CMD_FLV, // media flv

	WEB_CMD_MAX,
}web_cmd;

static const char * const  web_cmd_str[]={
	"HEARTBEAT",
	"LOGON",
	"HOME_PAGE",
	"MENU",
	"FLUSH_DATA",
	"DETAIL",
	"DETAIL_CONF",
	"DETAIL_SAVE",
	"FLUSH_STATUS",
	"UPLOAD",
	"DETAIL_GET",
	"DOWNLOAD",
	"CALIB",
	"FLV",

	"",
};


extern web_cmd web_str2cmd(const char *cmd_str);

#endif
