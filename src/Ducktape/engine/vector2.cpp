#include "vector2.h"
using namespace DT;

Vector2::Vector2()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2::Vector2(float xpos, float ypos)
{
    x = xpos;
    y = ypos;
}

Vector2 Vector2::operator+(Vector2 vec2)
{
    return Vector2(x + vec2.x, y + vec2.y);
}

Vector2 Vector2::operator-(Vector2 vec2)
{
    return Vector2(x - vec2.x, y - vec2.y);
}

Vector2 Vector2::operator*(float val)
{
    return Vector2(x * val, y * val);
}

Vector2 Vector2::operator/(float val)
{
    return Vector2(x / val, y / val);
}

Vector2& Vector2::operator=(Vector2 vec)
{
    x = vec.x;
    y = vec.y;
    return *this;
}

bool Vector2::operator==(Vector2 vec)
{
    if(Mathf::Approximately(x, vec.x) && Mathf::Approximately(y, vec.y))
    {
        return true;
    }
    return false;
}

float Vector2::Magnitude()
{
    return Mathf::Sqrt((x * x) + (y * y));
}

Vector2 Vector2::Normalized()
{
    float mag = Magnitude();
    return Vector2(x/mag, y/mag);
}

float Vector2::SqrMagnitude()
{
    return (x * x) + (y * y);
}

bool Vector2::Equals(Vector2 vec)
{
    if(x == vec.x && y == vec.y)
    {
        return true;
    }
    return false;
}

void Vector2::Normalize()
{
    x = Normalized().x;
    y = Normalized().y;
}

void Vector2::Set(Vector2 vec)
{
    x = vec.x;
    y = vec.y;
}

std::string Vector2::ToString()
{
    return "Vector2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

float Vector2::Distance(Vector2 vec1, Vector2 vec2)
{
    return (vec2 - vec1).Magnitude();
}

Vector2 Vector2::Lerp(Vector2 start, Vector2 end, float delta)
{
    return Vector2(Mathf::Lerp(start.x, end.x, delta), Mathf::Lerp(start.y, end.y, delta));
}

Vector2 Vector2::Max(Vector2 vec1, Vector2 vec2)
{
    return Vector2(Mathf::Max(vec1.x, vec2.x), Mathf::Max(vec1.y, vec2.y));
}

Vector2 Vector2::Min(Vector2 vec1, Vector2 vec2)
{
    return Vector2(Mathf::Min(vec1.x, vec2.x), Mathf::Min(vec1.y, vec2.y));
}

Vector2 Vector2::MoveTowards(Vector2 vec1, Vector2 vec2, float delta)
{
    return Vector2(Mathf::MoveTowards(vec1.x, vec2.x, delta), Mathf::MoveTowards(vec1.y, vec2.y, delta));
}

Vector2 Vector2::PerpendicularClockwise(Vector2 vec)
{
    return Vector2(vec.y, -vec.x);
}

Vector2 Vector2::PerpendicularCounterClockwise(Vector2 vec)
{
    return Vector2(-vec.y, vec.x);
}

sf::Vector2f Vector2::ToSFMLVector()
{
    return sf::Vector2f(x, y);
}

b2Vec2 Vector2::ToBox2DVector()
{
    return b2Vec2(x, y);
}

std::ostream &operator << (std::ostream &out, const Vector2 &vec)
{
    out << "Vector2(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ")";
    return out;
}
 
std::istream &operator >> (std::istream &in, Vector2 &vec)
{
    in >> vec.x;
    in >> vec.y;
    return in;
}

const Vector2 Vector2::ZERO  = Vector2( 0.0f,  0.0f);
const Vector2 Vector2::UP    = Vector2( 0.0f,  1.0f);
const Vector2 Vector2::DOWN  = Vector2( 0.0f, -1.0f);
const Vector2 Vector2::LEFT  = Vector2(-1.0f,  0.0f);
const Vector2 Vector2::RIGHT = Vector2( 1.0f,  0.0f);
const Vector2 Vector2::ONE   = Vector2( 1.0f,  1.0f);
const Vector2 Vector2::NEGATIVE_INFINITY = Vector2(Mathf::NegativeInfinity, Mathf::NegativeInfinity);
const Vector2 Vector2::POSITIVE_INFINITY = Vector2(Mathf::PositiveInfinity, Mathf::PositiveInfinity);
