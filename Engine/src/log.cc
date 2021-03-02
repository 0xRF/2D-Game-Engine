#include "../include/log.hh"
#include <iostream>
#include <stdarg.h>
#include <valarray>

namespace engine {
void log(const char *fmt, ...) {
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

void _debug_assert(const bool b) {
  if (!b) {
    logl("Assertion Failed %s %s %s", __FUNCTION__, __FILE__, __LINE__);
    exit(EXIT_FAILURE);
  }
}

#define DEBUG_ASSERT(x) _debug_assert(x)
} // namespace engine
