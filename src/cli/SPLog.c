#include <stdio.h>
#include <stdarg.h>

#include "SPLog.h"


int currentLevel = VERBOSE;


void setVerboseLevel(int level)
{
    currentLevel = level;
}


void splog(char *format, ...)
{
    va_list args;
    va_start(args, format);

    if(currentLevel > QUITE)
    {
        vprintf(format, args);
    }

    va_end(args);
}