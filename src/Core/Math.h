#pragma once

float Deg2Rad = 0.01745329251;
float Epsilon = 2.2204460492503130808472633361816E-16;
float PositiveInfinity = 3.40282e+038;
float NegativeInfinity = 1.17549e-038;
float PI = 3.14159265358979;
float Rad2Deg = 57.2957795131;
float GoldenRatio = 1.61803398875;

using namespace glm;

namespace Ducktape
{
    namespace Math
    {
        // Float overloads

        float Abs(float value)
        {
            return std::abs(value);
        }

        float Acos(float value)
        {
            return std::acos(value);
        }

        bool Approximately(float value, float value2)
        {
            if (Abs(value - value2) <= Epsilon)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        float Asin(float value)
        {
            return std::asin(value);
        }

        float Atan(float value)
        {
            return std::atan(value);
        }

        float Atan2(float value, float value2)
        {
            return std::atan2(value, value2);
        }

        float Ceil(float value)
        {
            return ceil(value);
        }

        float Clamp(float value, float min, float max)
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

        float Cos(float value)
        {
            return std::cos(value);
        }

        float DeltaAngle(float value, float value2)
        {
            float diff = ((int)value2 - (int)value + 180) % 360 - 180;
            return diff < -180 ? diff + 360 : diff;
        }

        float Exp(float value)
        {
            return std::exp(value);
        }

        float Floor(float value)
        {
            return floor(value);
        }

        float Round(float value)
        {
            return round(value);
        }

        float Lerp(float value, float target, float interpolation)
        {
            return value + (target - value) * interpolation;
        }

        float Max(float value, float value2)
        {
            return std::max(value, value2);
        }

        float Min(float value, float value2)
        {
            return std::min(value, value2);
        }

        float MoveTowards(float value, float target, float delta)
        {
            if (value > target)
            {
                return Clamp(value + delta, value, target);
            }
            else
            {
                return Clamp(value - delta, target, value);
            }
        }

        float Pow(float value, float value2)
        {
            return std::pow(value, value2);
        }

        float Sin(float value)
        {
            return std::sin(value);
        }

        float Sqrt(float value)
        {
            return sqrt(value);
        }

        float Tan(float value)
        {
            return std::tan(value);
        }

        // Int overloads

        int Abs(int value)
        {
            return std::abs(value);
        }

        int Acos(int value)
        {
            return std::acos(value);
        }

        bool Approximately(int value, int value2)
        {
            if (Abs(value - value2) <= Epsilon)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        int Asin(int value)
        {
            return std::asin(value);
        }

        int Atan(int value)
        {
            return std::atan(value);
        }

        int Atan2(int value, int value2)
        {
            return std::atan2(value, value2);
        }

        int Ceil(int value)
        {
            return ceil(value);
        }

        int Clamp(int value, int min, int max)
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

        int Cos(int value)
        {
            return std::cos(value);
        }

        int DeltaAngle(int value, int value2)
        {
            int diff = ((int)value2 - (int)value + 180) % 360 - 180;
            return diff < -180 ? diff + 360 : diff;
        }

        int Exp(int value)
        {
            return std::exp(value);
        }

        int Floor(int value)
        {
            return floor(value);
        }

        int Round(int value)
        {
            return round(value);
        }

        int Lerp(int value, int target, int interpolation)
        {
            return value + (target - value) * interpolation;
        }

        int Max(int value, int value2)
        {
            return std::max(value, value2);
        }

        int Min(int value, int value2)
        {
            return std::min(value, value2);
        }

        int MoveTowards(int value, int target, int delta)
        {
            if (value > target)
            {
                return Clamp(value + delta, value, target);
            }
            else
            {
                return Clamp(value - delta, target, value);
            }
        }

        int Pow(int value, int value2)
        {
            return std::pow(value, value2);
        }

        int Sin(int value)
        {
            return std::sin(value);
        }

        int Sqrt(int value)
        {
            return sqrt(value);
        }

        int Tan(int value)
        {
            return std::tan(value);
        }

        // Use template to have other types of overloads

        template <typename T>
        T Abs(T value)
        {
            return std::abs(value);
        }

        template <typename T>
        T Acos(T value)
        {
            return std::acos(value);
        }

        template <typename T>
        bool Approximately(T value, T value2)
        {
            if (Abs(value - value2) <= Epsilon)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        template <typename T>
        T Asin(T value)
        {
            return std::asin(value);
        }

        template <typename T>
        T Atan(T value)
        {
            return std::atan(value);
        }

        template <typename T>
        T Atan2(T value, T value2)
        {
            return std::atan2(value, value2);
        }

        template <typename T>
        T Ceil(T value)
        {
            return ceil(value);
        }

        template <typename T>
        T Clamp(T value, T min, T max)
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

        template <typename T>
        T Cos(T value)
        {
            return std::cos(value);
        }

        template <typename T>
        T DeltaAngle(T value, T value2)
        {
            T diff = ((int)value2 - (int)value + 180) % 360 - 180;
            return diff < -180 ? diff + 360 : diff;
        }

        template <typename T>
        T Exp(T value)
        {
            return std::exp(value);
        }

        template <typename T>
        T Floor(T value)
        {
            return floor(value);
        }

        template <typename T>
        T Round(T value)
        {
            return round(value);
        }

        template <typename T>
        T Lerp(T value, T target, T interpolation)
        {
            return value + (target - value) * interpolation;
        }

        template <typename T>
        T Max(T value, T value2)
        {
            return std::max(value, value2);
        }

        template <typename T>
        T Min(T value, T value2)
        {
            return std::min(value, value2);
        }

        template <typename T>
        T MoveTowards(T value, T target, T delta)
        {
            if (value > target)
            {
                return Clamp(value + delta, value, target);
            }
            else
            {
                return Clamp(value - delta, target, value);
            }
        }

        template <typename T>
        T Pow(T value, T value2)
        {
            return std::pow(value, value2);
        }

        template <typename T>
        T Sin(T value)
        {
            return std::sin(value);
        }

        template <typename T>
        T Sqrt(T value)
        {
            return sqrt(value);
        }

        template <typename T>
        T Tan(T value)
        {
            return std::tan(value);
        }
    }
}