#include "../include/log.hh"
#include <stdarg.h>
#include <valarray>
#include <iostream>

namespace engine{
    void log(const char* fmt, ...){
        va_list list;
        va_start(list, fmt);
        vprintf(fmt, list);
        va_end(list);
    }

    void logl(const char *fmt, ...) {
        va_list list;
        va_start(list, fmt);
        vprintf(fmt, list);
        va_end(list);
        printf("\n");
    }
}
