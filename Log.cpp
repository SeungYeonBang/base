#include "Log.h"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstdbool>
#include <unistd.h>

#define ISPRINTABLE(c)  (((c)>=32 && (c)<=126))

static LOG_LEVEL_e  gLogLevel = LOG_LEVEL_TRACE;

static void stdoutWrite(FILE* fp, const char* color, const char* buf)
{
    if (color)
        fputs(color, fp);

    fputs(buf, fp);

    if(color)
        fputs(RESET, fp);

    fflush(fp);
}

void Log::LOGT(const char* fmt, ...)
{
    va_list ap;
    FILE* fp;
    char buf[4096] = {0, };

    fp = stdout;

    if(LOG_LEVEL_TRACE > gLogLevel)
        return;

    if(!fp)
        return;

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    buf[sizeof(buf) -1] = 0;
    stdoutWrite(fp, GREEN, buf);
}

void Log::LOGD(const char* fmt, ...)
{
        va_list ap;
    FILE* fp;
    char buf[4096] = {0, };

    fp = stdout;

    if(LOG_LEVEL_DEBUG > gLogLevel)
        return;

    if(!fp)
        return;

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    buf[sizeof(buf) -1] = 0;
    stdoutWrite(fp, BLUE, buf);
}

void Log::LOGI(const char* fmt, ...)
{
        va_list ap;
    FILE* fp;
    char buf[4096] = {0, };

    fp = stdout;

    if(LOG_LEVEL_INFO > gLogLevel)
        return;

    if(!fp)
        return;

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    buf[sizeof(buf) -1] = 0;
    stdoutWrite(fp, NONE, buf);
}

void Log::LOGW(const char* fmt, ...)
{
    va_list ap;
    FILE* fp;
    char buf[4096] = {0, };

    fp = stdout;

    if(LOG_LEVEL_WARN > gLogLevel)
        return;

    if(!fp)
        return;

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    buf[sizeof(buf) -1] = 0;
    stdoutWrite(fp, YELLOW, buf);
}

void Log::LOGE(const char* fmt, ...)
{
    va_list ap;
    FILE* fp;
    char buf[4096] = {0, };

    fp = stdout;

    if(LOG_LEVEL_ERROR > gLogLevel)
        return;

    if(!fp)
        return;

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    buf[sizeof(buf) -1] = 0;
    stdoutWrite(fp, RED, buf);
}

void Log::setLogLevel(LOG_LEVEL_e level)
{
    gLogLevel = level;
}

void Log::hexDump(const void* ptr, int size)
{
    uint8_t* pData = (uint8_t*)ptr;
    int lineSize = 0;
    int startData = 0;

    while (size > 0)
    {
        printLine(lineSize, size, pData + lineSize);

        if (size < 16)
            lineSize += size;
        else
            lineSize += 16;

        size -= 16;

    }
}

void Log::printLine(int line, int size, uint8_t* p)
{
    int ii = 0;
    // Print offset
    printf("%08X  ", line);

    // Print Hexs
    for (ii=0; ii < 16; ii++)
    {
        if (ii  < size - 1)
            printf("0x%02X ", p[ii]);
        else
            printf("   ");
    }

    printf("      ");

    // Print ASCIIs
    for (ii=0; ii < 16; ii++)
    {
        if (ii  < size - 1)
        {
            if (ISPRINTABLE(p[ii]))
                printf("%c ", p[ii]);
            else
                printf(".");
        }
        else
            printf("   ");
    }
    printf("\n");
}
