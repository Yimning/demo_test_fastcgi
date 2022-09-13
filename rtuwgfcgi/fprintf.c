/*
 * @Author: Yimning 1148967988@qq.com
 * @Date: 2022-08-11 00:13:43
 */


#include "fprintf.h"

int CONSOLELOG(const char *filename,char *signstr,char *data)
{
    FILE* fp;
    fp = fopen(filename, "a+");
    fprintf(fp, "%s %s--->%s:%s\r\n", __DATE__ , __TIME__ , signstr ,data);
    fclose(fp);
    return 0;
    return 0;
}