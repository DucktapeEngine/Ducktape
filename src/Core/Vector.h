#pragma once

namespace Ducktape
{
    template <typename T = float, int N = 3>
    class Vec
    {
    public:
        std::array<T, N> data;

        Vec()
        {
            for (int i = 0; i < N; i++)
            {
                data[i] = 0.0f;
            }
        }

        Vec(std::array<T, N> data)
        {
            for (int i = 0; i < N; i++)
            {
                this->data[i] = data[i];
            }
        }

        T x()
        {
            if (N >= 1)
            {
                return data[0];
            }
            else
            {
                return 0.0f;
            }
        }

        T y()
        {
            if (N >= 2)
            {
                return data[1];
            }
            else
            {
                return 0.0f;
            }
        }

        T z()
        {
            if (N >= 3)
            {
                return data[2];
            }
            else
            {
                return 0.0f;
            }
        }

        T w()
        {
            if (N >= 4)
            {
                return data[3];
            }
            else
            {
                return 0.0f;
            }
        }

        Vec operator=(Vec<T, N> other)
        {
            for (int i = 0; i < N; i++)
            {
                data[i] = other.data[i];
            }
            return *this;
        }

        Vec operator+(const Vec &other)
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = data[i] + other.data[i];
            }
            return result;
        }

        Vec operator+=(const Vec &other)
        {
            for (int i = 0; i < N; i++)
            {
                data[i] += other.data[i];
            }
            return *this;
        }

        Vec operator-(const Vec &other)
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = data[i] - other.data[i];
            }
            return result;
        }

        Vec operator-=(const Vec &other)
        {
            for (int i = 0; i < N; i++)
            {
                data[i] -= other.data[i];
            }
            return *this;
        }

        Vec operator-()
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = -data[i];
            }
            return result;
        }

        T operator*(const Vec &other)
        {
            T result = 0.0f;
            for (int i = 0; i < N; i++)
            {
                result += data[i] * other.data[i];
            }
            return result;
        }

        Vec operator*(const T &other)
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = data[i] * other;
            }
            return result;
        }

        Vec operator*=(const T &other)
        {
            for (int i = 0; i < N; i++)
            {
                data[i] *= other;
            }
            return *this;
        }

        Vec operator/(const T &other)
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = data[i] / other;
            }
            return result;
        }

        Vec operator/=(const T &other)
        {
            for (int i = 0; i < N; i++)
            {
                data[i] /= other;
            }
            return *this;
        }

        T &operator[](int index)
        {
            return data[index];
        }

        T operator[](int index) const
        {
            return data[index];
        }

        T Length()
        {
            T result = 0.0f;
            for (int i = 0; i < N; i++)
            {
                result += data[i] * data[i];
            }
            return sqrt(result);
        }

        Vec Normalize()
        {
            T length = this->length();
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = data[i] / length;
            }
            return result;
        }

        static Vec Lerp(Vec a, Vec b, T t)
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = a.data[i] + (b.data[i] - a.data[i]) * t;
            }
            return result;
        }

        static Vec Clamp(Vec v, T min, T max)
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = std::min(std::max(v.data[i], min), max);
            }
            return result;
        }

        static Vec Min(Vec a, Vec b)
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = std::min(a.data[i], b.data[i]);
            }
            return result;
        }

        static Vec Max(Vec a, Vec b)
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = std::max(a.data[i], b.data[i]);
            }
            return result;
        }

        static Vec Abs(Vec v)
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = std::abs(v.data[i]);
            }
            return result;
        }

        static Vec Sqrt(Vec v)
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = std::sqrt(v.data[i]);
            }
            return result;
        }

        static Vec Pow(Vec v, T p)
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = std::pow(v.data[i], p);
            }
            return result;
        }

        static Vec Floor(Vec v)
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = std::floor(v.data[i]);
            }
            return result;
        }

        static Vec Ceil(Vec v)
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = std::ceil(v.data[i]);
            }
            return result;
        }

        static Vec Round(Vec v)
        {
            Vec result;
            for (int i = 0; i < N; i++)
            {
                result.data[i] = std::round(v.data[i]);
            }
            return result;
        }
    };

    using Vec2f = Vec<float, 2>;
    using Vec3f = Vec<float, 3>;
    using Vec4f = Vec<float, 4>;
    using Vec2i = Vec<int, 2>;
    using Vec3i = Vec<int, 3>;
    using Vec4i = Vec<int, 4>;
}