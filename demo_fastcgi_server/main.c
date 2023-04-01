#include<stdio.h>

extern int server_fcgi_main();

int main()
{
   //sleep(60);//sleep for ui start
   return server_fcgi_main();
}

