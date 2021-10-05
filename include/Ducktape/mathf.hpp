#pragma once
#include <cmath>

struct Mathf
{
    static constexpr float Deg2Rad = 0.01745329251;
    static constexpr float Epsilon = 2.2204460492503130808472633361816E-16;
    static constexpr float PositiveInfinity = 3.40282e+038;
    static constexpr float NegativeInfinity = 1.17549e-038;
    static constexpr float PI = 3.14159265358979;
    static constexpr float Rad2Deg = 57.2957795131;

    inline static float Abs(float val)
    {
        return abs(val);
    }

    inline static float Acos(float val)
    {
        return std::acos(val);
    }

    inline static bool Approximately(float val, float secondval)
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

    inline static float Asin(float val)
    {
        return std::asin(val);
    }

    inline static float Atan(float val)
    {
        return std::atan(val);
    }

    inline static float Atan2(float val, float val2)
    {
        return std::atan2(val, val2);
    }

    inline static float Ceil(float val)
    {
        return ceil(val);
    }

    inline static float Clamp(float val, float min, float max)
    {
        return std::clamp(val, min, max);
    }

    inline static float Clamp01(float val)
    {
        return Mathf::Clamp(val, 0.0, 1.0);
    }

    inline static float Cos(float val)
    {
        return std::cos(val);
    }

    inline static float DeltaAngle(float val, float val2)
    {
        float diff = ( (int)val2 - (int)val + 180 ) % 360 - 180;
        return diff < -180 ? diff + 360 : diff;
    }

    inline static float Exp(float val)
    {
        return std::exp(val);
    }

    inline static float Floor(float val)
    {
        return floor(val);
    }

    inline static float Round(float val)
    {
        return round(val);
    }

    inline static float Lerp(float val, float target, float interpolation)
    {
        return std::lerp(val, target, interpolation);
    }

    inline static float Max(float val, float val2)
    {
        return std::max(val, val2);
    }

    inline static float Min(float val, float val2)
    {
        return std::min(val, val2);
    }

    inline static float MoveTowards(float val, float target, float delta)
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

    inline static float Pow(float val, float val2)
    {
        return std::pow(val, val2);
    }

    inline static float Sin(float val)
    {
        return std::sin(val);
    }

    inline static float Sqrt(float val)
    {
        return sqrt(val);
    }

    inline static float Tan(float val)
    {
        return std::tan(val);
    }
};
