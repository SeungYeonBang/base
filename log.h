
#include "log.h"

#define ISPRINTABLE(c)  (((c)>=32 && (c)<=126))

void Log_Hex_Dump(const void* ptr, int size)
{
    uint8_t* pData = (uint8_t*)ptr;
    int lineSize = 0;
    int startData = 0;

    while (size > 0)
    {
        Print_Line(lineSize, size, pData + lineSize);

        if (size < 16)
            lineSize += size;
        else
            lineSize += 16;

        size -= 16;

    }
}

void Print_Line(int line, int size, uint8_t* p)
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
