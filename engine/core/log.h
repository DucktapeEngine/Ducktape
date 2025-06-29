#pragma once

// #ifndef NDEBUG
#define LOG(...)          \
    fmt::print("[LOG] "); \
    fmt::println(__VA_ARGS__);
// #else
// #define LOG(...) ;
// #endif

#define ERROR(...)        \
    fmt::print("[ERR] "); \
    fmt::println(__VA_ARGS__);
