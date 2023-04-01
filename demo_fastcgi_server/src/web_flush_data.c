/*
 * @Author: Yimning 1148967988@qq.com
 * @Date: 2022-09-27 13:36:48
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "web_flush_data.h"  

#define PACKAGE_BUFFER (pack_buffer+strlen(pack_buffer))


int status_flush_package(char *pack_buffer)
{//printf("{\"status\":[{\"UserName\":\"123\",\"Sex\":\"456\"},{\"UserName\":\"789\",\"Sex\":\"0\"}]}");
	
	int ret=0,i;
	
	if(!pack_buffer) return -1;
  
	sprintf(PACKAGE_BUFFER,"flush status menory error");

	return 0;
}
