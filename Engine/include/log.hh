#pragma once

namespace engine {
    void log(const char* fmt, ...);
    void logl(const char* fmt, ...);
    void _debug_assert(const bool);
#define DEBUG_ASSERT(x) engine::_debug_assert(x)
}
