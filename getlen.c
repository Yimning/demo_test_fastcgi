/*
 * @Author: your name
 * @Date: 2022-09-12 05:52:15
*/
#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

#define BEEPOFF 	0
#define BEEPON 	1

/*
 * @description		: main主程序
 * @param - argc 	: argv数组元素个数
 * @param - argv 	: 具体参数
 * @return 			: 0 成功;其他 失败
 */
int main(int argc, char *argv[])
{
	int fd, retvalue;
	char *filename;
	unsigned char databuf[10];
	
	if(argc != 3){
		printf("Error Usage!\r\n");
		return -1;
	}

	filename = argv[1];

	/* 打开beep驱动 */
	fd = open(filename, O_RDWR);
	if(fd < 0){
		printf("file %s open fail beep!\r\n", argv[1]);
		return -1;
	}

	memset(databuf, 0, sizeof(databuf));
	retvalue = read(fd, databuf, sizeof(databuf));
	if(retvalue < 0){
		printf("Device Control Failed!\r\n");
		close(fd);
		return -1;
	}
    printf("getlen %d!\r\n",retvalue);

	retvalue = close(fd); /* 关闭文件 */
	if(retvalue < 0){
		printf("file %s close fail beep!\r\n", argv[1]);
		return -1;
	}
	return 0;
}