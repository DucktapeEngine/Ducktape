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

#ifndef MATHF_H
#define MATHF_H

#include <cmath>
#include <algorithm>

namespace DT
{
    namespace Mathf
    {
        extern float Deg2Rad;
        extern float Epsilon;
        extern float PositiveInfinity;
        extern float NegativeInfinity;
        extern float PI;
        extern float Rad2Deg;
        extern float GoldenRatio;

        float abs(float val);

        float acos(float val);

        bool approximately(float val, float secondval);

        float asin(float val);

        float atan(float val);

        float atan2(float val, float val2);

        float ceil(float val);

        float clamp(float val, float min, float max);

        float cos(float val);

        float deltaAngle(float val, float val2);

        float exp(float val);

        float floor(float val);

        float round(float val);

        float lerp(float val, float target, float interpolation);

        float max(float val, float val2);

        float min(float val, float val2);

        float moveTowards(float val, float target, float delta);

        float pow(float val, float val2);

        float sin(float val);

        float sqrt(float val);

        float tan(float val);
    };
}

#endif