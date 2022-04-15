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

#pragma once

namespace Ducktape
{
    enum Joystick
    {
        HAT_CENTERED = 0,
        HAT_UP = 1,
        HAT_RIGHT = 2,
        HAT_DOWN = 4,
        HAT_LEFT = 8,
        HAT_RIGHT_UP = HAT_RIGHT | HAT_UP,
        HAT_RIGHT_DOWN = HAT_RIGHT | HAT_DOWN,
        HAT_LEFT_UP = HAT_LEFT | HAT_UP,
        HAT_LEFT_DOWN = HAT_LEFT | HAT_DOWN
    };
}