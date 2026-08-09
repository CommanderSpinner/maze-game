#pragma once
#include <cstdio>

#ifndef NDEBUG
    #define DBG_PRINTF(...) std::printf(__VA_ARGS__)
#else
    #define DBG_PRINTF(...)
#endif