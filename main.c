#include<stdio.h>

extern int rtuwg_fcgi_main();

int main()
{
   //sleep(60);//sleep for ui start
   return rtuwg_fcgi_main();
}

