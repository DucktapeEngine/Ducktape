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

#include <Ducktape/engine/mathf.h>
using namespace DT;

float Mathf::Deg2Rad = 0.01745329251;
float Mathf::Epsilon = 2.2204460492503130808472633361816E-16;
float Mathf::PositiveInfinity = 3.40282e+038;
float Mathf::NegativeInfinity = 1.17549e-038;
float Mathf::PI = 3.14159265358979;
float Mathf::Rad2Deg = 57.2957795131;
float Mathf::GoldenRatio = 1.61803398875;

float Mathf::abs(float value)
{
    return std::abs(value);
}

float Mathf::Acos(float value)
{
    return std::acos(value);
}

bool Mathf::Approximately(float value, float value2)
{
    if (Mathf::abs(value - value2) <= Mathf::Epsilon)
    {
        return true;
    }
    else
    {
        return false;
    }
}

float Mathf::Asin(float value)
{
    return std::asin(value);
}

float Mathf::Atan(float value)
{
    return std::atan(value);
}

float Mathf::Atan2(float value, float value2)
{
    return std::atan2(value, value2);
}

float Mathf::Ceil(float value)
{
    return Ceil(value);
}

float Mathf::Clamp(float value, float min, float max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    return value;
}

float Mathf::Cos(float value)
{
    return std::cos(value);
}

float Mathf::DeltaAngle(float value, float value2)
{
    float diff = ((int)value2 - (int)value + 180) % 360 - 180;
    return diff < -180 ? diff + 360 : diff;
}

float Mathf::Exp(float value)
{
    return std::exp(value);
}

float Mathf::Floor(float value)
{
    return Floor(value);
}

float Mathf::Round(float value)
{
    return Round(value);
}

float Mathf::Lerp(float value, float target, float interpolation)
{
    return value + (target - value) * interpolation;
}

float Mathf::Max(float value, float value2)
{
    return std::max(value, value2);
}

float Mathf::Min(float value, float value2)
{
    return std::min(value, value2);
}

float Mathf::MoveTowards(float value, float target, float delta)
{
    if (value > target)
    {
        return Mathf::Clamp(value + delta, value, target);
    }
    else
    {
        return Mathf::Clamp(value - delta, target, value);
    }
}

float Mathf::Pow(float value, float value2)
{
    return std::pow(value, value2);
}

float Mathf::Sin(float value)
{
    return std::sin(value);
}

float Mathf::Sqrt(float value)
{
    return Sqrt(value);
}

float Mathf::Tan(float value)
{
    return std::tan(value);
}