#!/bin/sh
###
 # @Author: Yimning 1148967988@qq.com
 # @Date: 2022-08-10 04:09:41
 # @LastEditors: Yimning 1148967988@qq.com
 # @LastEditTime: 2022-08-10 04:23:18
 # @FilePath: /www/demo_test_cgifast/cp_to_nginx.sh
 # @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
### 
export TOPDIR=`pwd`
a=$(pgrep rtuwg.fcgi)
if (pgrep rtuwg.fcgi)
then
   #echo $a
   sudo  kill -9 $(pgrep rtuwg.fcgi)
   echo "执行以下语句..."
   echo $TOPDIR
   echo "sudo cp rtuwg.fcgi /usr/local/nginx/html/tengent/cgi-bin/usr/ -rf"
   sudo cp rtuwg.fcgi /usr/local/nginx/html/tengent/cgi-bin/usr/ -rf
   echo "spawn-fcgi -a 127.0.0.1 -p 8080 -f /usr/local/nginx/html/tengent/cgi-bin/usr/rtuwg.fcgi"
   spawn-fcgi -a 127.0.0.1 -p 8080 -f /usr/local/nginx/html/tengent/cgi-bin/usr/rtuwg.fcgi
   lsof -i:8080

else
   echo "执行以下语句..."
   echo $TOPDIR
   echo "sudo cp rtuwg.fcgi /usr/local/nginx/html/tengent/cgi-bin/usr/ -rf"
   sudo cp rtuwg.fcgi /usr/local/nginx/html/tengent/cgi-bin/usr/ -rf
   echo "spawn-fcgi -a 127.0.0.1 -p 8080 -f /usr/local/nginx/html/tengent/cgi-bin/usr/rtuwg.fcgi"
   spawn-fcgi -a 127.0.0.1 -p 8080 -f /usr/local/nginx/html/tengent/cgi-bin/usr/rtuwg.fcgi
   lsof -i:8080
fi
  
  
