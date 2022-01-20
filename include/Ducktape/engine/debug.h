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

#ifndef DEBUG_H
#define DEBUG_H

#define FATAL_ERROR 8

#include <Ducktape/engine/vector2.h>
#include <Ducktape/engine/color.h>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace DT
{
    namespace Debug
    {
        // valing
        void log(std::string val);

        void logError(std::string val);

        void logFatalError(std::string val);

        void logWarning(std::string val);

        void logSuccess(std::string val);

        // float overload

        void log(float val);

        void logError(float val);

        void logFatalError(float val);

        void logWarning(float val);

        void logSuccess(float val);

        void drawLine(Vector2 start, Vector2 end, Color color);

        void drawRay(Vector2 start, Vector2 dir, float length, Color color);
    };
}

#endif