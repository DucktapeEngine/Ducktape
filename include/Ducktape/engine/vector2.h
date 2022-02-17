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

#ifndef DUCKTAPE_ENGINE_VECTOR2_H_
#define DUCKTAPE_ENGINE_VECTOR2_H_

#include <string>
#include <iostream>

#include <SFML/Window.hpp>
#include <box2d/box2d.h>

#include <Ducktape/engine/mathf.h>

namespace DT
{
    /**
     * @brief A class representing a 2D vector.
     */
    class Vector2
    {
    public:
        /**
         * @brief Short form for Vector2(0.0f, 0.0f).
         */
        static const Vector2 ZERO;

        /**
         * @brief Short form for Vector2(0.0f, 1.0f).
         */
        static const Vector2 UP;

        /**
         * @brief Short form for Vector2(0.0f, -1.0f).
         */
        static const Vector2 DOWN;

        /**
         * @brief Short form for Vector2(-1.0f, 0.0f).
         */
        static const Vector2 LEFT;

        /**
         * @brief Short form for Vector2(1.0f, 0.0f).
         */
        static const Vector2 RIGHT;

        /**
         * @brief Short form for Vector2(1.0f, 1.0f).
         */
        static const Vector2 ONE;

        /**
         * @brief Short form for Vector2(Mathf::NegativeInfinity, Mathf::NegativeInfinity).
         */
        static const Vector2 NEGATIVE_INFINITY;

        /**
         * @brief Short form for Vector2(Mathf::PositiveInfinity, Mathf::PositiveInfinity).
         */
        static const Vector2 POSITIVE_INFINITY;

        float x, y;

        Vector2();
        Vector2(float xpos, float ypos);

        Vector2 operator+(Vector2 vec2);
        Vector2 operator-(Vector2 vec2);
        Vector2 operator*(float val);
        Vector2 operator/(float val);
        Vector2 &operator=(Vector2 vec);
        bool operator==(Vector2 vec);

        /**
         * @brief Returns the magntiude of the vector.
         *
         * @return float Magnitude of the vector.
         */
        float Magnitude();

        /**
         * @brief Returns the normalized vector.
         *
         * @return float Normalized vector.
         */
        Vector2 Normalized();

        /**
         * @brief Returns the squared magnitude of the vector.
         *
         * @return float The squared magnitude of the vector.
         */
        float SqrMagnitude();

        /**
         * @brief Distance between two vectors.
         *
         * @param vec1 First vector.
         * @param vec2 Second vector.
         * @return float Distance between the two vectors.
         */
        static float Distance(Vector2 vec1, Vector2 vec2);

        /**
         * @brief Get the interpolated float result between the two vectors.
         *
         * @param start Initial vector.
         * @param target Target vector.
         * @param delta Interpolation value.
         * @return Vector2 Interpolated vector.
         */
        static Vector2 Lerp(Vector2 start, Vector2 target, float delta);

        /**
         * @brief Get the maxiumum of the two vectors.
         *
         * @param vec1 First vector.
         * @param vec2 Second vector.
         * @return Vector2 Maximum vector.
         */
        static Vector2 Max(Vector2 vec1, Vector2 vec2);

        /**
         * @brief Get the minimum of the two vectors.
         *
         * @param vec1 First vector.
         * @param vec2 Second vector.
         * @return Vector2 Minimum vector.
         */
        static Vector2 Min(Vector2 vec1, Vector2 vec2);

        /**
         * @brief Moves value towards target.
         *
         * @param value The current value.
         * @param target The target value.
         * @param delta The amount to move.
         * @return float The moved value.
         */
        static Vector2 MoveTowards(Vector2 value, Vector2 target, float delta);

        operator std::string() const;
        operator sf::Vector2f() const;
        operator b2Vec2() const;
    };
}

#endif