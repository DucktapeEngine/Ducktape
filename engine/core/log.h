/*
MIT License

Copyright (c) 2021 - 2025 Aryan Baburajan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

// reset
#define ANSI_RESET "\033[0m"

// text styles
#define ANSI_BOLD "\033[1m"
#define ANSI_DIM "\033[2m"
#define ANSI_ITALIC "\033[3m"
#define ANSI_UNDERLINE "\033[4m"
#define ANSI_BLINK "\033[5m"
#define ANSI_INVERT "\033[7m"
#define ANSI_HIDDEN "\033[8m"
#define ANSI_STRIKETHROUGH "\033[9m"

// foreground (text) colors
#define ANSI_FG_BLACK "\033[30m"
#define ANSI_FG_RED "\033[31m"
#define ANSI_FG_GREEN "\033[32m"
#define ANSI_FG_YELLOW "\033[33m"
#define ANSI_FG_BLUE "\033[34m"
#define ANSI_FG_MAGENTA "\033[35m"
#define ANSI_FG_CYAN "\033[36m"
#define ANSI_FG_WHITE "\033[37m"

// bright foreground colors
#define ANSI_FG_BBLACK "\033[90m"
#define ANSI_FG_BRED "\033[91m"
#define ANSI_FG_BGREEN "\033[92m"
#define ANSI_FG_BYELLOW "\033[93m"
#define ANSI_FG_BBLUE "\033[94m"
#define ANSI_FG_BMAGENTA "\033[95m"
#define ANSI_FG_BCYAN "\033[96m"
#define ANSI_FG_BWHITE "\033[97m"

// background colors
#define ANSI_BG_BLACK "\033[40m"
#define ANSI_BG_RED "\033[41m"
#define ANSI_BG_GREEN "\033[42m"
#define ANSI_BG_YELLOW "\033[43m"
#define ANSI_BG_BLUE "\033[44m"
#define ANSI_BG_MAGENTA "\033[45m"
#define ANSI_BG_CYAN "\033[46m"
#define ANSI_BG_WHITE "\033[47m"

// bright background colors
#define ANSI_BG_BBLACK "\033[100m"
#define ANSI_BG_BRED "\033[101m"
#define ANSI_BG_BGREEN "\033[102m"
#define ANSI_BG_BYELLOW "\033[103m"
#define ANSI_BG_BBLUE "\033[104m"
#define ANSI_BG_BMAGENTA "\033[105m"
#define ANSI_BG_BCYAN "\033[106m"
#define ANSI_BG_BWHITE "\033[107m"

// #ifndef NDEBUG
#define LOG(...)             \
    fmt::print("[LOG] ");    \
    fmt::print(__VA_ARGS__); \
    fmt::println(ANSI_RESET);
// #else
// #define LOG(...) ;
// #endif

#define ERROR(...)                                     \
    fmt::print("{}[ERR]{} ", ANSI_BG_RED, ANSI_RESET); \
    fmt::print(__VA_ARGS__);                           \
    fmt::println(ANSI_RESET);
