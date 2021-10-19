#include "mathf.hpp"
#include <cmath>
#include <math.h>

float Mathf::Abs(float val)
{
    return abs(val);
}

float Mathf::Acos(float val)
{
    return std::acos(val);
}

bool Mathf::Approximately(float val, float secondval)
{
    if(Mathf::Abs(val - secondval) <= Mathf::Epsilon)
    {
        return true;
    }
    else
    {
        return false;
    }
}

float Mathf::Asin(float val)
{
    return std::asin(val);
}

float Mathf::Atan(float val)
{
    return std::atan(val);
}

float Mathf::Atan2(float val, float val2)
{
    return std::atan2(val, val2);
}

float Mathf::Ceil(float val)
{
    return ceil(val);
}

float Mathf::Clamp(float val, float min, float max)
{
    if(val < min)
    {
        return min;
    } 
    else if(val > max)
    {
        return max;
    }
    return val;
}

float Mathf::Clamp01(float val)
{
    return Mathf::Clamp(val, 0.0, 1.0);
}

float Mathf::Cos(float val)
{
    return std::cos(val);
}

float Mathf::DeltaAngle(float val, float val2)
{
    float diff = ( (int)val2 - (int)val + 180 ) % 360 - 180;
    return diff < -180 ? diff + 360 : diff;
}

float Mathf::Exp(float val)
{
    return std::exp(val);
}

float Mathf::Floor(float val) 
{
    return floor(val);
}

float Mathf::Round(float val)
{
    return round(val);
}

float Mathf::Lerp(float val, float target, float interpolation)
{
    return std::lerp(val, target, interpolation);
}

float Mathf::Max(float val, float val2)
{
    return std::max(val, val2);
}

float Mathf::Min(float val, float val2)
{
    return std::min(val, val2);
}

float Mathf::MoveTowards(float val, float target, float delta)
{
    if(val > target)
    {
        return Mathf::Clamp(val + delta, val, target);
    }
    else
    {
        return Mathf::Clamp(val - delta, target, val);
    }
}

float Mathf::Pow(float val, float val2)
{
    return std::pow(val, val2);
}

float Mathf::Sin(float val)
{
    return std::sin(val);
}

float Mathf::Sqrt(float val)
{
    return sqrt(val);
}

float Mathf::Tan(float val)
{
    return std::tan(val);
}