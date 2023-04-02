#ifndef DEGOUT_H_
#define DEGOUT_H_

#ifdef __cplusplus 
extern "C" {
#endif

enum LogLevel
{
    ERROR = 1,
    WARN  = 2,
    INFO  = 3,
    DEBUG = 4,
};
#define DEBUG_PATH ("/home/yimning/FastCGI/lighttpd/www/demo_test_fastcgi/demo_fastcgi_server/src/debug/debug.log")
void Log(const char* filename, int line, enum LogLevel level, const char* fmt, ...) __attribute__((format(printf,4,5)));

#define DEBUG_PRINTF(level, format, ...) Log(__FILE__, __LINE__, level, format, ## __VA_ARGS__)
#define DEBUG_LOG(filename, level, format, ...) LogFile(filename,__FILE__, __LINE__, level, format, ## __VA_ARGS__)

#ifdef __cplusplus 
};
#endif

#endif