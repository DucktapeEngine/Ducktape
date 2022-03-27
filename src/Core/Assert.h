#pragma once

#define DT_ASSERT(condition, message) do {\
    if (condition == false)\
    {\
        std::cout << "Assertion failed: " + std::string(message) << '\n' << "In file: " << std::string(__FILE__) << ":" << std::to_string(__LINE__) << '\n';\
    }\
} while(0)\

#define DT_FATAL_ASSERT(condition, message) do {\
    if (condition == false)\
    {\
        std::cout << "Assertion failed: " + std::string(message) << '\n' << "In file: " << std::string(__FILE__) << ":" << std::to_string(__LINE__) << '\n';\
        exit(1);\
    }\
} while(0)\


