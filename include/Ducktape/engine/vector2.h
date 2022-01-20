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

#ifndef VECTOR2_H
#define VECTOR2_H

#include <string>
#include <SFML/Window.hpp>
#include <box2d/box2d.h>
#include "mathf.h"
#include <iostream>

namespace DT
{
    class Vector2
    {
    public:
        static const Vector2 ZERO;
        static const Vector2 UP;
        static const Vector2 DOWN;
        static const Vector2 LEFT;
        static const Vector2 RIGHT;
        static const Vector2 ONE;
        static const Vector2 NEGATIVE_INFINITY;
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

        float magnitude();

        Vector2 normalized();

        float sqrMagnitude();

        bool equals(Vector2 vec);

        void normalize();

        void set(Vector2 vec);

        static float distance(Vector2 vec1, Vector2 vec2);

        static Vector2 lerp(Vector2 start, Vector2 end, float delta);

        static Vector2 max(Vector2 vec1, Vector2 vec2);

        static Vector2 min(Vector2 vec1, Vector2 vec2);

        static Vector2 moveTowards(Vector2 vec1, Vector2 vec2, float delta);

        static Vector2 perpendicularClockwise(Vector2 vec);

        static Vector2 perpendicularCounterClockwise(Vector2 vec);

        operator std::string() const;
        operator sf::Vector2f() const;
        operator b2Vec2() const;
    };
}

#endif