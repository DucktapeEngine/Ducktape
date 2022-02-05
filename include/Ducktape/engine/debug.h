/*
MIT License

Copyright (c) 2022 Ducktape

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

#ifndef DUCKTAPE_ENGINE_DEBUG_H_
#define DUCKTAPE_ENGINE_DEBUG_H_

#define FATAL_ERROR 8

#include <iostream>

#include <SFML/Graphics.hpp>

#include <Ducktape/engine/vector2.h>
#include <Ducktape/engine/color.h>

namespace DT
{
    /**
     * @brief Debugging functions.
     */
    namespace Debug
    {
        /**
         * @brief Prints a message to the console.
         * @param message The message to print.
         */
        template <typename T>               
        void Log(T message)
        {
        #ifndef PRODUCTION
            std::cout << message << "\n";
        #endif
        }

        /**
         * @brief Prints an error to the console in red.
         * @param message The message to print.
         */
        template <typename T>               
        void LogError(T message)
        {
            std::cout << "\033[0;31m" << message << "\033[0m\n";
        }

        /**
         * @brief Prints a warning to the console in red and aborts the program.
         * @param message The message to print.
         */
        template <typename T>       
        void LogFatalError(T message)
        {
            std::cout << "\033[0;31m [FATAL ERR] " << message << "\033[0m" << std::endl;
            exit(FATAL_ERROR);
        }

        /**
         * @brief Prints a warning to the console in yellow.
         * @param message The message to print.
         */
        template <typename T>       
        void LogWarning(T message)
        {
        #ifndef PRODUCTION
            std::cout << "\033[0;33m" << message << "\033[0m\n";
        #endif
        }

        /**
         * @brief Prints a message to the console in green.
         * @param message The message to print.
         */
        template <typename T>       
        void LogSuccess(T message)
        {
        #ifndef PRODUCTION
            std::cout << "\033[0;32m" << message << "\033[0m\n";
        #endif
        }

        void DrawLine(Vector2 start, Vector2 end, Color color);

        void DrawRay(Vector2 start, Vector2 dir, float length, Color color);
    };
}

#endif