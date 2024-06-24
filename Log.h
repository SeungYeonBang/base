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

#define __BASE_FILE_NAME__  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

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



#define LOGT(fmt, args...)      Log::printLog(LOG_LEVEL_TRACE, GREEN, fmt, ##args);

#define LOGD(fmt, args...)      Log::printLog(LOG_LEVEL_DEBUG, BLUE, fmt, ##args);
            
#define LOGI(fmt, args...)      { \
                                    const char* func = Log::methodNm(__PRETTY_FUNCTION__); \
                                    Log::printLog(LOG_LEVEL_INFO, NONE, "[%s:%d] %s() " fmt, __BASE_FILE_NAME__, __LINE__, func, ##args); \
                                }

#define LOGW(fmt, args...)      { \
                                    const char* func = Log::methodNm(__PRETTY_FUNCTION__); \
                                    Log::printLog(LOG_LEVEL_WARN, YELLOW, "[%s:%d] %s() " fmt, __BASE_FILE_NAME__, __LINE__, func, ##args); \
                                }

#define LOGE(fmt, args...)      { \
                                    const char* func = Log::methodNm(__PRETTY_FUNCTION__); \
                                    Log::printLog(LOG_LEVEL_ERROR, RED, "[%s:%d] %s() " fmt, __BASE_FILE_NAME__, __LINE__, func, ##args); \
                                }

class Log
{
public:
    static const char* methodNm(const char* func);
    static void printLog(int priority, const char* color, const char* fmt, ...);

    void setLogLevel(LOG_LEVEL_e level);
    static void hexDump(const void* ptr, int size);

private:
    Log() {}
    virtual ~Log() {}

    static void printLine(int line, int size, uint8_t* p);
};
#endif /* __LOG_H_ */
