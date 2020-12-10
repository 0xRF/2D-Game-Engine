#include "../include/log.hh"
#include <valarray>

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