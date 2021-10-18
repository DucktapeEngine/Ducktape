#pragma once
#include "mathf.hpp"
#include <string>
#include <SFML/System/Vector2.hpp>
struct Vector2
{
    float x, y;
    inline Vector2(float xpos, float ypos)
    {
        x = xpos;
        y = ypos;
	*Down = Vector2(0.0, -1.0);

    *Left = Vector2(-1.0, 0.0);

    *NegativeInfinity = Vector2(Mathf::NegativeInfinity, Mathf::NegativeInfinity);

    *One = Vector2(1.0, 1.0);

    *PositiveInfinity = Vector2(Mathf::PositiveInfinity, Mathf::PositiveInfinity);
   
    *Right = Vector2(1.0, 0.0);
    
    *Up = Vector2(0.0, 1.0);
    
    *Zero = Vector2(0.0, 0.0);    
    }

    inline Vector2 operator+(Vector2 vec2)
    {
        return Vector2(x + vec2.x, y + vec2.y);
    }

    inline Vector2 operator-(Vector2 vec2)
    {
        return Vector2(x - vec2.x, y - vec2.y);
    }

    inline Vector2 operator*(float val)
    {
        return Vector2(x * val, y * val);
    }

    inline Vector2 operator/(float val)
    {
        return Vector2(x / val, y / val);
    }

    inline bool operator==(Vector2 vec)
    {
        if(Mathf::Approximately(x, vec.x) && Mathf::Approximately(y, vec.y))
        {
            return true;
        }
        return false;
    }
  static Vector2* Down;// = Vector2(0.0, -1.0);

  static Vector2* Left;// = Vector2(-1.0, 0.0);

  static Vector2* NegativeInfinity;// = Vector2(Mathf::NegativeInfinity, Mathf::NegativeInfinity);

  static Vector2* One;// = Vector2(1.0, 1.0);

  static Vector2* PositiveInfinity;// = Vector2(Mathf::PositiveInfinity, Mathf::PositiveInfinity);
   
  static Vector2* Right;// = Vector2(1.0, 0.0);
    
  static Vector2* Up;// = Vector2(0.0, 1.0);
    
  static Vector2* Zero;// = Vector2(0.0, 0.0);    


    inline float Magnitude()
    {
        return Mathf::Sqrt((x * x) + (y * y));
    }

    inline Vector2 Normalized()
    {
        float mag = Magnitude();
        return Vector2(x/mag, y/mag);
    }

    inline float SqrMagnitude()
    {
        return (x * x) + (y * y);
    }

    inline bool Equals(Vector2 vec)
    {
        if(x == vec.x && y == vec.y)
        {
            return true;
        }
        return false;
    }

    inline void Normalize()
    {
        x = Normalized().x;
        y = Normalized().y;
    }

    inline void Set(Vector2 vec)
    {
        x = vec.x;
        y = vec.y;
    }

    inline std::string ToString()
    {
        return "Vector2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

    inline static float Distance(Vector2 vec1, Vector2 vec2)
    {
        return (vec2 - vec1).Magnitude();
    }

    inline static Vector2 Lerp(Vector2 start, Vector2 end, float delta)
    {
        return Vector2(Mathf::Lerp(start.x, end.x, delta), Mathf::Lerp(start.y, end.y, delta));
    }

    inline static Vector2 Max(Vector2 vec1, Vector2 vec2)
    {
        return Vector2(Mathf::Max(vec1.x, vec2.x), Mathf::Max(vec1.y, vec2.y));
    }

    inline static Vector2 Min(Vector2 vec1, Vector2 vec2)
    {
        return Vector2(Mathf::Min(vec1.x, vec2.x), Mathf::Min(vec1.y, vec2.y));
    }

    inline static Vector2 MoveTowards(Vector2 vec1, Vector2 vec2, float delta)
    {
        return Vector2(Mathf::MoveTowards(vec1.x, vec2.x, delta), Mathf::MoveTowards(vec1.y, vec2.y, delta));
    }

    inline static Vector2 PerpendicularClockwise(Vector2 vec)
    {
        return Vector2(vec.y, -vec.x);
    }

    inline static Vector2 PerpendicularCounterClockwise(Vector2 vec)
    {
        return Vector2(-vec.y, vec.x);
    }

    // static Vector2 Reflect(Vector2 vec, Vector2 normal)
    // {
    // https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
    // }

    inline sf::Vector2f ToSFMLVector()
    {
        return sf::Vector2f(x, y);
    }
};

// static Vector2 Rotate(this Vector2 v, float degrees) {
//     float sin = Mathf.Sin(degrees * Mathf.Deg2Rad);
//     float cos = Mathf.Cos(degrees * Mathf.Deg2Rad);

//     float tx = v.x;
//     float ty = v.y;
//     v.x = (cos * tx) - (sin * ty);
//     v.y = (sin * tx) + (cos * ty);
//     return v;
// }

// public static Vector2 Rotate(this Vector2 v, Vector2 center, float degrees) {
//     return center + (v - center).Rotate(degrees);
// }
