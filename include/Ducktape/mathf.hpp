#pragma once

struct Mathf
{
    static constexpr float Deg2Rad = 0.01745329251;
    static constexpr float Epsilon = 2.2204460492503130808472633361816E-16;
    static constexpr float PositiveInfinity = 3.40282e+038;
    static constexpr float NegativeInfinity = 1.17549e-038;
    static constexpr float PI = 3.14159265358979;
    static constexpr float Rad2Deg = 57.2957795131;

    static float Abs(float val);

    static float Acos(float val);

    static bool Approximately(float val, float secondval);

    static float Asin(float val);

    static float Atan(float val);

    static float Atan2(float val, float val2);

    static float Ceil(float val);

    static float Clamp(float val, float min, float max);

    static float Clamp01(float val);

    static float Cos(float val);

    static float DeltaAngle(float val, float val2);

    static float Exp(float val);

    static float Floor(float val);

    static float Round(float val);

    static float Lerp(float val, float target, float interpolation);

    static float Max(float val, float val2);

    static float Min(float val, float val2);

    static float MoveTowards(float val, float target, float delta);

    static float Pow(float val, float val2);

    static float Sin(float val);

    static float Sqrt(float val);

    static float Tan(float val);
};