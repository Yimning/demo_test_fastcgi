# demo_test_fastcgi
This is a demo for testing fastcgi and cjson project. 
  
# Destination
处理客户端发起fcgi请求时，然后去解析参数并返回结果。可构造成cjson并返回json字符串。 
     
               
# Dependent installation 相关依赖安装           
（略）                             
                                    
# You know     
fcgi处理步骤<br>    
通过Internet 把用户请求送到Web 服务器<br>     
Web 服务器接收到用户请求并交给CGI 程序<br>   
CGI 程序把处理结果传送给Web 服务器<br>
Web 服务器把结果送回到用户<br> 
# Demo  
eg.<br>
得到参数 char *query_string = "CMD=LOGON&SELECT=0&USERNAME=user&PASSWORD=123";<br>
对其解析成字符串：
```json  
0---CMD=LOGON 
1---SELECT=0
2---USERNAME=user
3---PASSWORD=123
```
     
对其解析成json字符串
```json
{
        "CMD":  "LOGON",
        "SELECT":       "0",
        "USERNAME":     "user",
        "PASSWORD":     "123"
}   
```
# Debug
```
下面是一些具体方法和步骤，可以帮助你调试FastCGI：

确认FastCGI程序是否正常运行。使用命令 ps aux | grep fcgitest 检查进程是否存在，并使用 netstat -anp | grep :端口号 检查FastCGI监听的端口是否已经打开。

使用 nc 命令发送请求，手动测试FastCGI程序是否能够正确处理请求并返回响应。例如：echo "Content-type: text/plain" | nc localhost 8000

检查FastCGI程序中是否存在语法错误、链接库缺失或权限不足等问题。在命令行下直接执行FastCGI程序，查看是否有异常提示。例如：./fcgitest

在FastCGI程序中添加一些输出信息，以便于更好地定位问题。例如，在程序中添加一些日志记录，可以使用 syslog 或者 printf 等函数来输出调试信息。

可以使用 tcpdump 或 wireshark 等工具来捕获网络数据包，分析请求和响应之间的交互情况，从而找到问题所在。

使用 gdb 等调试工具来进行源代码级别的调试，可以更加深入地了解程序的内部运行情况。

检查lighttpd.conf文件中是否正确配置了FastCGI映射关系，并且对应的socket文件是否存在以及具有读写权限。

如果以上步骤都没有解决问题，可以尝试重新安装lighttpd和相关依赖，并重新配置FastCGI映射关系。

总之，FastCGI调试需要结合具体情况进行，需要根据问题的表现来选择合适的方法和步骤进行排查。
```   

