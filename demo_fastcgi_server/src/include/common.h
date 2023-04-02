#ifndef COMMON_H
#define COMMON_H
#include <string.h>
#include <time.h>

#define ARRAY_SIZE(aa) (sizeof(aa)/sizeof(aa[0]))

#define TIME_LEN (7*sizeof(int))
#define TIME_ARRAY  (TIME_LEN/sizeof(int))
#define DEBUG_PATH ("/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/demo_fastcgi_server/src/debug/debug.txt")
#define LOGIN_PATH ("/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/demo_fastcgi_server/src/debug/login")


static int compare_time(int tm1[TIME_ARRAY],int tm2[TIME_ARRAY])
{
        int i=0;
        for(i=TIME_ARRAY-2;i>=0;i--)//omit week, so TIME_ARRAY-2
        {
            if(tm1[i]!=tm2[i])
                break;
        }

        if(i<0)  return 0;
        if(i>=0) return tm1[i]-tm2[i];
}

static int tmarray2tmstruct(int *tm_array,struct tm *tm_struct)
{
        if(!tm_array && !tm_struct) return -1;

        tm_struct->tm_year = tm_array[5]-1900 ;
        tm_struct->tm_mon = tm_array[4]-1;
        tm_struct->tm_mday = tm_array[3];
        tm_struct->tm_hour = tm_array[2];
        tm_struct->tm_min = tm_array[1];
        tm_struct->tm_sec = tm_array[0];

        return 0;
}

static int tmstruct2tmarray(int *tm_array,struct tm *tm_struct)
{
        if(!tm_array && !tm_struct) return -1;

        tm_array[5] = tm_struct->tm_year+1900;
        tm_array[4] = tm_struct->tm_mon+1;
        tm_array[3] = tm_struct->tm_mday;
        tm_array[2] = tm_struct->tm_hour;
        tm_array[1] = tm_struct->tm_min;
        tm_array[0] = tm_struct->tm_sec;	

        return 0;
}  

static int tmarray2tmlong(int *tm_array,time_t *time_long)
{
    struct tm tm_str;
    
    if(!tm_array && !time_long) return -1;
    
    tmarray2tmstruct(tm_array,&tm_str);
    //chinese jiffs from 1970-01-01 08:00:00
    *time_long = mktime(&tm_str);//count from 1970-1-1 8:0:0
    return 0;
}

static int tmlong2tmarray(int *tm_array,time_t *time_long)
{
    struct tm tm_str;
    
    if(!tm_array && !time_long) return -1;
    
    //gmtime_r(time_long,&tm_str);//count from 1970-1-1 0:0:0 , error for china
    //chinese jiffs from 1970-01-01 08:00:00
    //memcpy(&tm_str,localtime(time_long),sizeof(struct tm));//count from 1970-1-1 8:0:0	
    localtime_r(time_long,&tm_str);
    tmstruct2tmarray(tm_array,&tm_str);

    return 0;
}

static int time_increase(int tm_src[TIME_ARRAY],int tm_dst[TIME_ARRAY],unsigned long seconds)
{
    struct tm tm_struct;
    time_t time_long;

    if(!tm_src || !tm_dst) return -1;

    if(seconds==0)
    {
            memcpy(tm_dst,tm_src,sizeof(int)*TIME_ARRAY);
            return 0;
     }

    if(tmarray2tmstruct(tm_src,&tm_struct)) return -1;
    time_long = mktime(&tm_struct);
    time_long +=seconds;
    //gmtime_r(time_long,&tm_struct);//count from 1970-1-1 0:0:0 , error for china
    //chinese jiffs from 1970-01-01 08:00:00
    //memcpy(&tm_struct,localtime(&time_long),sizeof(struct tm));//count from 1970-1-1 8:0:0	
    localtime_r(&time_long,&tm_struct);
    if(tmstruct2tmarray(tm_dst,&tm_struct)) return -1;

    return 0;
}

static int time_decrease(int tm_src[TIME_ARRAY],int tm_dst[TIME_ARRAY],unsigned long seconds)
{
    struct tm tm_struct;
    time_t time_long;

    if(!tm_src || !tm_dst) return -1;

    if(seconds==0)
    {
            memcpy(tm_dst,tm_src,sizeof(int)*TIME_ARRAY);
            return 0;
     }
    
    if(tmarray2tmstruct(tm_src,&tm_struct)) return -1;
    time_long = mktime(&tm_struct);
    time_long -=seconds;
    //gmtime_r(time_long,&tm_struct);//count from 1970-1-1 0:0:0 , error for china
    //chinese jiffs from 1970-01-01 08:00:00
    //memcpy(&tm_struct,localtime(&time_long),sizeof(struct tm));//count from 1970-1-1 8:0:0	
    localtime_r(&time_long,&tm_struct);
    if(tmstruct2tmarray(tm_dst,&tm_struct)) return -1;

    return 0;
}

static void read_system_time(int  *tm)
{
    struct tm tm_struct;
    time_t time_long;
    
    if(!tm) return ;
    
    time_long = time(NULL);
    //gmtime_r(time_long,&tm_struct);//count from 1970-1-1 0:0:0 , error for china
    //chinese jiffs from 1970-01-01 08:00:00
    //memcpy(&tm_struct,localtime(&time_long),sizeof(struct tm));//count from 1970-1-1 8:0:0	
    localtime_r(&time_long,&tm_struct);
    tmstruct2tmarray(tm,&tm_struct);
}


static void str_replace_ch2ch(char *str,int len,char src,char dst)
{
	int i=0;
	if(!str || len<=0) return ;

    for(i=0;i<len;i++)
    {
    	if(str[i]==src) str[i]=dst;
    }
}

#endif
