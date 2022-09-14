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

#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"

int display_menu_device_readStatus(char *filename, char* databuf);
int display_menu_device_writeStatus(char *filename, char *status);

#endif