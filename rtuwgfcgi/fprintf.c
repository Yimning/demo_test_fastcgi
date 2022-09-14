/*
 * @Author: Yimning 1148967988@qq.com
 * @Date: 2022-08-11 00:13:43
 */


#include "fprintf.h"

static struct tm* systemTimeNow()
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
void FPRINTF_LOG(const char *filename, char *fmt, ...)
{
    FILE* fp; 
    fp = fopen(filename, "a+");
    char buff[1024] = {0};

	struct tm *time = systemTimeNow();

    //可变参数第一步,定义va_list变量
	va_list va_ptr;

	//可变参数第二步，初始化va_ptr,将va_ptr指向第一个可选参数
	va_start(va_ptr,fmt);
    
    vsnprintf(buff,256,fmt,va_ptr);

    //把buff数据写入文件
    fprintf(fp,"%d.%d.%d %d:%d:%d --------log information\r\n%s\r\n",time->tm_year+1900, time->tm_mon, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec ,buff);   

	//可变参数最后一步
	va_end(va_ptr);

    fclose(fp);
}





#if 0
static FILE* fp; 
//函数声明
void printDec(int dec);
void printHex(int hex);
void printOct(unsigned oct);
void printNum(unsigned long num, int base);
void printStr(char *str);
void printFloat(double f);
void printAddr(unsigned long);

void my_fprintf(const char *filename,char *fmt, ...);
void my_fprintf(const char *filename, char *fmt, ...)
{

    fp = fopen(filename, "a+");
	//可变参数第一步,定义va_list变量
	va_list va_ptr;
	//可变参数第一步，初始化va_ptr,将va_ptr指向第一个可选参数
	va_start(va_ptr,fmt);

	//使用循环，打印完所有格式字符串
	while(*fmt)
	{				
		//普通字符照常输出
		if(*fmt != '%')
		{
			putchar(*fmt++);
            fprintf(fp,"%c",*fmt++);
			continue;
		}
		
		//处理%后要打印的对应格式
		switch(*(++fmt))//先++是为了跳过%
		{
			case 'd'://打印十进制数
                fprintf(fp,"%d",va_arg(va_ptr,int));
				break;
			case 'c'://打印字符
                fprintf(fp,"%c",va_arg(va_ptr,int));
				break;
			case 's'://打印字符串
                fprintf(fp,"%s",va_arg(va_ptr,char*));
				break;
			case 'x':
			case 'X'://打印十六进制数
                fprintf(fp,"%X",va_arg(va_ptr,unsigned int));
				break;
			case 'o'://打印八进制数
                fprintf(fp,"%o",va_arg(va_ptr,unsigned int));
				break;
			case 'f'://打印浮点数
                fprintf(fp,"%f",va_arg(va_ptr,double));
				break;
			case 'p'://打印地址
                fprintf(fp,"%p",va_arg(va_ptr,unsigned long)); 
				break;
			case '%'://打印%
                fprintf(fp,"%c",'%');
				break;
			default:
				break;
		}
		fmt++;//别忘记++，继续查询字符
	}
	
	//可变参数最后一步
	va_end(va_ptr);

    fclose(fp);
}




//因为用到此函数打印地址，所以函数的第一个参数用unsigned long最为保险
//16位编译器，地址占16位，2字节，可以使用short或者int保存。
//32位编译器，地址占32位，4字节，可以使用int或long保存
//64位编译器，地址占64位，8字节，可以使用long保存。
void printNum(unsigned long num, int base)
{
	//递归结束条件
	if(num == 0)
	{
		return;
	}
	
	//继续递归
	printNum(num/base,base);
	//逆序打印结果
	putchar("0123456789abcdef"[num%base]);
    fprintf(fp,"%c","0123456789abcdef"[num%base]);
}

//打印十进制数
void printDec(int dec)
{
	//处理负数的情况
	if(dec < 0)
	{
		//putchar('-');
        fprintf(fp,"%c",'-');
		dec = -dec;
	}
	
	if(dec == 0)
	{
		putchar('0');
        fprintf(fp,"%c",'0');
		return;
	}
	
	printNum(dec,10);
}

//打印十六进制数
void printHex(int hex)
{
	if(hex == 0)
	{
		putchar('0');
        fprintf(fp,"%c",'0');
		return;
	}
	
	printNum(hex,16);
}

//打印八进制数
void printOct(unsigned oct)
{
	if(oct == 0)
	{
		putchar('0');
        fprintf(fp,"%c",'0');
		return;
	}
	
	printNum(oct,8);
}

//打印字符串
void printStr(char *str)
{
	char *p = str;
	while(*p)
	{
		putchar(*p++);
         
        fprintf(fp,"%c",*p++);
	}
}

//打印浮点数
void printFloat(double f)
{
	int tmp = (int)f;
	//先打印整数部分
	printNum(tmp,10);
	//小数点
	putchar('.');
    fprintf(fp,"%c",'.');
	
	//再打印小数部分
	f -= tmp;
	if(f == 0)
	{
		int i; 
		//浮点型精度至少6位
		for(i = 0; i < 6; i++)
		{
			putchar('0');
            fprintf(fp,"%c",'0');
		}
		return;
	}
	
	tmp = (int)(f*1000000);
	printNum(tmp,10);
}

void printAddr(unsigned long addr)
{
	printStr("0x");
	
	//内存地址是用十六进制表示的
	printNum(addr,16);
}
#endif

