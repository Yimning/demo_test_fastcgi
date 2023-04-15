#ifndef REST_COMMOM_H
#define REST_COMMOM_H
#ifdef ENABLE_FASTCGI
#include "fcgi_stdio.h"
#else
#include <stdio.h>
#endif
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <time.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <sys/socket.h>
#include "rest_types.h"
#include <sys/ioctl.h>
#include <sys/file.h>
#include "json.h"
#include "qdecoder.h"
#include "dbgout.h"

//AUTOMATION ENGINE SCRIPTS/TASKS
#define HTTPHEADER	"POST /api HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: keep-alive\r\nContent-Type: application/json\r\n"
#define REQSIZE		1024
#define RESLEN			2048

#define RPC_HAPI_SUCCESS    0
#define DEFAULT_TIMEOUT 30
#define WEBPAGE_HANDLE      wp

#define LIGHTTPD_CONF_PATH "/conf/lighttpd.conf"
#define LIGHTTPD_TEMP_CONF_PATH "/tmp/lighttpd.conf"
#define LIGHTTPD_RESTART_CONF "/etc/init.d/lighttpd.sh restart &"
#define LIGHTTPD_DELAYED_RESTART "/usr/local/bin/lighttpd_delayed_restart.sh 2 &"

#define STATUS_100 "100 Continue"
#define STATUS_101 "101 Switching Protocols"
#define STATUS_200 "200 OK"
#define STATUS_201 "201 Created"
#define STATUS_202 "202 Accepted"
#define STATUS_203 "203 Non-Authoritative Information"
#define STATUS_204 "204 No Content"
#define STATUS_205 "205 Reset Content"
#define STATUS_206 "206 Partial Content"
#define STATUS_300 "300 Multiple Choices"
#define STATUS_301 "301 Moved Permanently"
#define STATUS_302 "302 Found"
#define STATUS_303 "303 See Other"
#define STATUS_304 "304 Not Modified"
#define STATUS_305 "305 Use Proxy"
#define STATUS_307 "307 Temporary Redirect"
#define STATUS_400 "400 Bad Request"
#define STATUS_401 "401 Unauthorized"
#define STATUS_402 "402 Payment Required"
#define STATUS_403 "403 Forbidden"
#define STATUS_404 "404 Not Found"
#define STATUS_405 "405 Method Not Allowed"
#define STATUS_406 "406 Not Acceptable"
#define STATUS_407 "407 Proxy Authentication Required"
#define STATUS_408 "408 Request Timeout"
#define STATUS_409 "409 Conflict"
#define STATUS_410 "410 Gone"
#define STATUS_411 "411 Length Required"
#define STATUS_412 "412 Precondition Failed"
#define STATUS_413 "413 Request Entity Too Large"
#define STATUS_414 "414 Request-URI Too Long"
#define STATUS_415 "415 Unsupported Media Type"
#define STATUS_416 "416 Requested Range Not Satisfiable"
#define STATUS_417 "417 Expectation Failed"
#define STATUS_500 "500 Internal Server Error"
#define STATUS_501 "501 Not Implemented"
#define STATUS_502 "502 Bad Gateway"
#define STATUS_503 "503 Service Unavaiable"
#define STATUS_504 "504 Gateway Timeout"
#define STATUS_505 "505 HTTP Version Not Supported"
// KVM Related status codes
#define STATUS_519 "519 Custom Status Message"
#define STATUS_1442 "1442 Recording in progress"
#define STATUS_12012 "12012 Large File Size"
#define STATUS_12013 "12013 No License"
#define STATUS_1232  "1232 Data File Not Available"
#define STATUS_1233  "1233 Data File Reset issue"

typedef enum CGI_CONST_MAP {
    CGI_1 = 0x04, //GET
    CGI_2 = 0x02, //POST
    CGI_3 = 0x03, //PUT
    CGI_4 = 0x09, //HEAD
    CGI_5 = 0x05, //DELETE
    CGI_6 = 0x10 //PATCH

} CGI_CONT_MAP_T;
#endif
