#ifndef __LOG_H_
#define __LOG_H_

#include <stdio.h>
#include <stdint.h>

#define NONE    NULL
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

typedef enum
{
    LOG_LEVEL_NONE,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_TRACE,

    MAX_LOG_LEVEL
}LOG_LEVEL_e;

class Log
{
public:
    void setLogLevel(LOG_LEVEL_e level);

    static void hexDump(const void* ptr, int size);

    static void LOGT(const char* fmt, ...);
    static void LOGD(const char* fmt, ...);
    static void LOGI(const char* fmt, ...);
    static void LOGW(const char* fmt, ...);
    static void LOGE(const char* fmt, ...);
private:
    Log() {}
    virtual ~Log() {}

    static void printLine(int line, int size, uint8_t* p);
};
#endif /* __LOG_H_ */
