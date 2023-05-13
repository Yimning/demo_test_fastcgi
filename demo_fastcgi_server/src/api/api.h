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
#include "errno.h"
#include <iconv.h>
#include <sqlite3.h>
#include <json.h>
#include <pthread.h>

#ifndef	__ssize_t_defined
typedef __ssize_t ssize_t;
# define __ssize_t_defined
#endif

#define BASEPATH    "upload"

#define MAX_BUFFER_SIZE 1024*1024
#define MAXFILESIZE	65536

int CONSOLELOG(const char *filename,char *signstr,char *data);
int FPRINTF_LOG(const char *filename, char *fmt, ...);

struct tm* systemTimeNow();

int display_menu_device_readStatus(const char *filename, char* databuf);
int display_menu_device_writeStatus(const char *filename,  char *status);

/* get file size */
off_t get_file_size(const char *file_name);

/* write file content */
int write_file(const char *file_name,const char *modes,const char *content);

/* read file content */
int fread_file(const char *filename, char** fileBuff);

/* zero file */
int empty_file(const char *file_name); 

/* save file */
ssize_t savefile(const char *filepath, const void *buf, size_t size);

char *get_current_dir();

char* utf8_to_gb2312(const char *utf8_str);


//sqlite3 api
static int callback(void *NotUsed, int argc, char **argv, char **azColName);

int getUserListSqlite3(const char *sql_select,const char *json_string);

int insertUserListSqlite3(const char *sql_insert,const char *json_string);

int deleteUserListSqlite3(const char *sql_delete,const char *json_string);
#endif