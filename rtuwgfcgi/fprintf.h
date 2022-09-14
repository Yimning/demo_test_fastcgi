/*
 * @Author: Yimning 1148967988@qq.com
 * @Date: 2022-08-11 00:13:43
 */


#ifndef FPRINTF_H
#define FPRINTF_H
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdarg.h>

int CONSOLELOG(const char *filename,char *signstr,char *data);
void FPRINTF_LOG(const char *filename, char *fmt, ...);


#endif