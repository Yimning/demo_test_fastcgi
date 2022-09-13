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

//函数声明
void printDec(int dec);
void printHex(int hex);
void printOct(unsigned oct);
void printNum(unsigned long num, int base);
void printStr(char *str);
void printFloat(double f);
void printAddr(unsigned long);

void my_fprintf(const char *filename,char *fmt, ...);

#endif