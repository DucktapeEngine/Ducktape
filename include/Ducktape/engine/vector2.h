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
        float x, y;
        Vector2();

        Vector2(float xpos, float ypos);

        Vector2 operator+(Vector2 vec2);

        Vector2 operator-(Vector2 vec2);

        Vector2 operator*(float val);

        Vector2 operator/(float val);

        Vector2& operator=(Vector2 vec);

        bool operator==(Vector2 vec);

        static Vector2 Down();

        static Vector2 Left();

        static Vector2 NegativeInfinity();

        static Vector2 One();

        static Vector2 PositiveInfinity();

        static Vector2 Right();

        static Vector2 Up();

        static Vector2 Zero();

        float Magnitude();

        Vector2 Normalized();

        float SqrMagnitude();

        bool Equals(Vector2 vec);

        void Normalize();

        void Set(Vector2 vec);

        std::string ToString();

        static float Distance(Vector2 vec1, Vector2 vec2);

        static Vector2 Lerp(Vector2 start, Vector2 end, float delta);

        static Vector2 Max(Vector2 vec1, Vector2 vec2);

        static Vector2 Min(Vector2 vec1, Vector2 vec2);

        static Vector2 MoveTowards(Vector2 vec1, Vector2 vec2, float delta);

        static Vector2 PerpendicularClockwise(Vector2 vec);

        static Vector2 PerpendicularCounterClockwise(Vector2 vec);

        sf::Vector2f ToSFMLVector();

        b2Vec2 ToBox2DVector();
    };

    std::ostream &operator << (std::ostream &out, const Vector2 &vec);
     
    std::istream &operator >> (std::istream &in, Vector2 &vec);
}

#endif