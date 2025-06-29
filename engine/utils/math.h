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

#include <cmath>

namespace glm
{
    inline double normalize(const double value, const double start, const double end)
    {
        const double width = end - start;
        const double offsetValue = value - start;
        return (offsetValue - (floor(offsetValue / width) * width)) + start;
    }

    inline float angNormalize(const float &angle)
    {
        const float offset = angle + 180.f;
        return (offset - (floor(offset / 360.f) * 360.f)) - 180.f;
    }

    inline glm::vec3 angNormalize(const glm::vec3 &angle)
    {
        return glm::vec3(angNormalize(angle.x), angNormalize(angle.y), angNormalize(angle.z));
    }
}