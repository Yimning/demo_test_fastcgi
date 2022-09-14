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

#include "api.h"

int display_menu_device_readStatus(char *filename, char* databuf)
{
	int fd, retvalue=-1;
	char buf[20];
	/* 打开设备驱动 */
	fd = open(filename, O_RDWR);
	if(fd < 0){
		printf("file %s open failed!\r\n", filename);
		return -1;
	}

	/* 向文件读数据 */
	memset(buf, 0, sizeof(buf));
	retvalue = read(fd, buf, sizeof(buf));
	if(retvalue < 0){
		printf("Device Control Failed!\r\n");
		close(fd);
		return -1;
	}
	memcpy(databuf, buf, sizeof(buf));

	retvalue = close(fd); /* 关闭文件 */
	if(retvalue < 0){
		printf("file %s close failed!\r\n", filename);
		return -1;
	}
	return retvalue;
}



int display_menu_device_writeStatus(char *filename, char *status)
{
	int fd, retvalue;
	unsigned char databuf[1];

	/* 打开设备驱动 */
	fd = open(filename, O_RDWR);
	if(fd < 0){
		printf("file %s open failed!\r\n", filename);
		return -1;
	}

	databuf[0] = atoi(status);	/* 要执行的操作：打开或关闭 */

	/* 向文件写入数据 */
	retvalue = write(fd, databuf, sizeof(databuf));
	if(retvalue < 0){
		printf("Device Control Failed!\r\n");
		close(fd);
		return -1;
	}

	retvalue = close(fd); /* 关闭文件 */
	if(retvalue < 0){
		printf("file %s close failed!\r\n", filename);
		return -1;
	}
	return 0;
}


