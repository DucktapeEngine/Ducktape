#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>

struct Vector2
{
    float x, y;
    Vector2(float xpos, float ypos);

    Vector2();

    Vector2 operator+(Vector2 vec2);

    void operator+=(Vector2 vec2);

    Vector2 operator-(Vector2 vec2);

    Vector2 operator*(float val);

    Vector2 operator/(float val);

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
};