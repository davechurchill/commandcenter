#pragma once

#include <cstdio>
#include <cstdarg>
#include <sstream>
#include <stdarg.h>

#include <ctime>
#include <iomanip>

#ifdef WIN32
    #define BOT_BREAK __debugbreak();
#else
    #define BOT_BREAK ;
#endif

#if true
    #define BOT_ASSERT(cond, msg, ...) \
        do \
        { \
            if (!(cond)) \
            { \
                Assert::ReportFailure(#cond, __FILE__, __LINE__, (msg), ##__VA_ARGS__); \
                BOT_BREAK \
            } \
        } while(0)
#else
    #define BOT_ASSERT(cond, msg, ...) 
#endif

namespace Assert
{
    extern std::string lastErrorMessage;

    const std::string CurrentDateTime();

    void ReportFailure(const char * condition, const char * file, int line, const char * msg, ...);
}
