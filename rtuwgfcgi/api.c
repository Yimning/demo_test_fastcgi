/*
================================================================
 * Copyright © 2022 Yimning. All rights reserved.
 *   
 * @File Name: api.c
 * @Author: Yimning
 * @Email: 1148967988@qq.com
 * @Created Time: 2022-08-11 00:12:47
 * @Description:api 
 *
================================================================
*/

#include "api.h"


struct tm* systemTimeNow()
{
    time_t t;
    struct tm *tm;
    //获取Unix时间戳。
    time (&t);
    //转为时间结构。
    tm = localtime (&t);

    //printf ( "%d/%d/%d %d:%d:%d\n",tm->tm_year+1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    return tm; 
}

int CONSOLELOG(const char *filename,char *signstr,char *data)
{
    FILE* fp;
    fp = fopen(filename, "a+");
	/* 	 __DATE__ 和 __TIME__  分别为编译日期、当前编译时间 */
    fprintf(fp, "%s %s--->%s:%s\r\n", __DATE__ , __TIME__ , signstr ,data);
    fclose(fp);
    return 0;
}


/*
================================================================
 *
 * @Description:FPRINTF_LOG
 *
================================================================
*/
int FPRINTF_LOG(const char *filename, char *fmt, ...)
{
	if(get_file_size(filename)> (MAX_BUFFER_SIZE/2)){
		empty_file(filename);
	}

    FILE* fp; 
    fp = fopen(filename, "a+");
    char buff[MAX_BUFFER_SIZE] = {0};

	struct tm *time = systemTimeNow();

    //可变参数第一步,定义va_list变量
	va_list va_ptr;

	//可变参数第二步，初始化va_ptr,将va_ptr指向第一个可选参数
	va_start(va_ptr,fmt);
    
    vsnprintf(buff,MAX_BUFFER_SIZE,fmt,va_ptr);

    //把buff数据写入文件
    fprintf(fp,"%d.%d.%d %d:%d:%d --------log information\r\n%s\r\n",time->tm_year+1900, time->tm_mon, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec ,buff);   

	//可变参数最后一步
	va_end(va_ptr);

    fclose(fp);
	
	return 0;
}



int display_menu_device_readStatus(const char *filename, char* databuf)
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



int display_menu_device_writeStatus(const char *filename,  char *status)
{
	int fd, retvalue;
	unsigned char databuf[256]={0};

	/* 打开设备驱动 */
	fd = open(filename, O_RDWR);
	if(fd < 0){
		//printf("file %s open failed!\r\n", filename);
		FPRINTF_LOG(DEBUG_PATH,"file %s open failed!\r\n", filename);
		return -1;
	}

	//databuf[0] = atoi(status);	/* 要执行的操作：打开或关闭 */
	strncpy((char *)databuf, status,strlen(status));

	/* 向文件写入数据 */
	retvalue = write(fd, databuf, sizeof(databuf));

	if(retvalue < 0){
		//printf("Device Control Failed!\r\n");
		FPRINTF_LOG(DEBUG_PATH,"Device Control Failed!\r\n");
		close(fd);
		return -1;
	}

	retvalue = close(fd); /* 关闭文件 */
	if(retvalue < 0){
		//printf("file %s close failed!\r\n", filename);
		FPRINTF_LOG(DEBUG_PATH,"file %s close failed!\r\n");
		return -1;
	}
	return 0;
}


off_t get_file_size(const char *file_name)
{
	int ret;
	int fd;
	struct stat file_stat;

	fd = open(file_name, O_RDONLY);	// 打开文件
	if (fd == -1) {
		printf("Open file %s failed : %s\n", file_name, strerror(errno));
		return -1;
	}
	ret = fstat(fd, &file_stat);	// 获取文件状态
	if (ret == -1) {
		printf("Get file %s stat failed:%s\n", file_name, strerror(errno));
		close(fd);
		return -1;
	}
	close(fd);
	return file_stat.st_size;
}

int empty_file(const char *file_name)
{
	FILE* fp;
	fp=fopen(file_name,"w+");
	if(fp == NULL)
	{
		printf("Open file %s failed : %s\n", file_name, strerror(errno));
		return -1;
	}
	fclose(fp);
	return 0;
}

int fread_file(const char *filename, char** fileBuff)
{
	FILE* fp;

	if ((fp = fopen(filename, "r")) < 0)
	{
		*fileBuff = NULL;
	} 
	else 
	{
		//读取文件
		char buffer[MAX_BUFFER_SIZE]={0};
		size_t n=fread(buffer,1,sizeof(char)*MAX_BUFFER_SIZE,fp);

		*fileBuff = buffer; 

	}
	fclose(fp);

	return 0;
}