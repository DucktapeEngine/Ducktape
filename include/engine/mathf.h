#ifndef MATHF_H
#define MATHF_H

#include <cmath>

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