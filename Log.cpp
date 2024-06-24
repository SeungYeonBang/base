#include "Log.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdbool>
#include <unistd.h>

#define MAX_FUNCION_SIZE    (1024)

#define ISPRINTABLE(c)  (((c)>=32 && (c)<=126))

static LOG_LEVEL_e  gLogLevel = LOG_LEVEL_TRACE;

const char* Log::methodNm(const char* func)
{
    char tmp[MAX_FUNCION_SIZE];
    char *begin, *end, *p;

    strncpy(tmp, func, MAX_FUNCION_SIZE-1);
    tmp[MAX_FUNCION_SIZE-1] = 0;

    end = strrchr(tmp, '(');
    if (end) *end = 0;

    begin = NULL;
    p = tmp;
    while((p = strchr(p, ' '))) { begin = p; p++; }
    if (begin) begin++;

    return begin;
}

static void stdoutWrite(FILE* fp, const char* color, const char* buf)
{
    if (color)
        fputs(color, fp);

    fputs(buf, fp);

    if(color)
        fputs(RESET, fp);

    fflush(fp);
}
void Log::printLog(int priority, const char* color, const char* fmt, ...)
{
    va_list ap;
    FILE* fp;
    char buf[4096];

    if(priority > gLogLevel)
        return;

    fp = stdout;

    if(!fp)
        return;

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    buf[sizeof(buf) -1] = 0;
    stdoutWrite(fp, color, buf);
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
