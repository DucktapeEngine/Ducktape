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

        float Abs(float val);

        float Acos(float val);

        bool Approximately(float val, float secondval);

        float Asin(float val);

        float Atan(float val);

        float Atan2(float val, float val2);

        static float Ceil(float val);

        float Clamp(float val, float min, float max);

        float Clamp01(float val);

        float Cos(float val);

        float DeltaAngle(float val, float val2);

        float Exp(float val);

        float Floor(float val);

        float Round(float val);

        float Lerp(float val, float target, float interpolation);

        float Max(float val, float val2);

        float Min(float val, float val2);

        float MoveTowards(float val, float target, float delta);

        float Pow(float val, float val2);

        float Sin(float val);

        float Sqrt(float val);

        float Tan(float val);
    };
}

#endif