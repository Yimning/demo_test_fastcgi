/*
================================================================
 * Copyright © 2022 Yimning. All rights reserved.
 *   
 * @File Name: getparameter.c
 * @Author: Yimning
 * @Email: 1148967988@qq.com
 * @Created Time: 2022-08-11 00:12:47
 * @Description:getparameter
 *
================================================================
*/

#ifndef API_H
#define API_H
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdarg.h>
#include <time.h>
#include "common.h"

#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"


#define MAX_BUFFER_SIZE 1024*1024

int CONSOLELOG(const char *filename,char *signstr,char *data);
void FPRINTF_LOG(const char *filename, char *fmt, ...);

struct tm* systemTimeNow();

int display_menu_device_readStatus(const char *filename, char* databuf);
int display_menu_device_writeStatus(const char *filename,  char *status);

//read file content
int fread_file(const char *filename, char** fileBuff);

#endif