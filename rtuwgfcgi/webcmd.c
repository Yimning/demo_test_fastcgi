/*
 * @Author: Yimning
 * @Date: 2022-09-16 11:04:57
 * @Description: 
 */
#include "stdlib.h"
#include "string.h"

#include "common.h"
#include "webcmd.h"

web_cmd web_str2cmd(const char *cmd_str)
{
	int i=0;

	for(i=0;i<ARRAY_SIZE(web_cmd_str);i++)
	{
		if(i>=WEB_CMD_MAX) break;

		if(!strcmp(cmd_str,web_cmd_str[i])) return (web_cmd)i;
	}

	if(i>=WEB_CMD_MAX) return WEB_CMD_MAX;

	return WEB_CMD_MAX;
}

const char* web_cmd2str(web_cmd cmd)
{
	return web_cmd_str[cmd];
}















