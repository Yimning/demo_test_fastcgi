#!/bin/sh

export TOPDIR=`pwd`
a=$(pgrep fcgitest.fcgi.fcgi)
if (pgrep fcgitest.fcgi.fcgi)
then
   sudo  kill -9 $(pgrep fcgitest.fcgi.fcgi)

   echo "pkill lighttpd执行以下语句..."

   echo "pkill lighttpd"
   sudo pkill lighttpd 

   #echo "sudo cp fcgitest.fcgi.fcgi /home/yimning/FastCGI/lighttpd/www/tengent/cgi-bin/usr -rf"
   #sudo cp fcgitest.fcgi.fcgi /home/yimning/FastCGI/lighttpd/www/tengent/cgi-bin/usr/ -rf

   echo "sudo  /home/yimning/FastCGI/lighttpd/sbin/lighttpd -f /home/yimning/FastCGI/lighttpd/config/lighttpd.conf"
   sudo  /home/yimning/FastCGI/lighttpd/sbin/lighttpd -f /home/yimning/FastCGI/lighttpd/config/lighttpd.conf

else
   echo "执行以下语句..."

   #echo "sudo cp fcgitest.fcgi.fcgi /home/yimning/FastCGI/lighttpd/www/tengent/cgi-bin/usr -rf"
   #sudo cp fcgitest.fcgi.fcgi /home/yimning/FastCGI/lighttpd/www/tengent/cgi-bin/usr/ -rf

   echo "sudo  /home/yimning/FastCGI/lighttpd/sbin/lighttpd -f /home/yimning/FastCGI/lighttpd/config/lighttpd.conf"
   sudo  /home/yimning/FastCGI/lighttpd/sbin/lighttpd -f /home/yimning/FastCGI/lighttpd/config/lighttpd.conf

fi

