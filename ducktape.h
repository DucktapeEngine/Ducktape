#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

namespace DT
{
    int WIDTH = 1000;
    int HEIGHT = 600;
    int iFrameRateLimit = 0;
    bool bVerticalSync = true;

    struct Mathf
    {
        static constexpr float Deg2Rad = 0.01745329251;
        static constexpr float Epsilon = 2.2204460492503130808472633361816E-16;
        static constexpr float PositiveInfinity = 3.40282e+038;
        static constexpr float NegativeInfinity = 1.17549e-038;
        static constexpr float PI = 3.14159265358979;
        static constexpr float Rad2Deg = 57.2957795131;

        static float Abs(float val)
        {
            return abs(val);
        }

        static float Acos(float val)
        {
            return std::acos(val);
        }

        static bool Approximately(float val, float secondval)
        {
            if(Mathf::Abs(val - secondval) <= Mathf::Epsilon)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        static float Asin(float val)
        {
            return std::asin(val);
        }

        static float Atan(float val)
        {
            return std::atan(val);
        }

        static float Atan2(float val, float val2)
        {
            return std::atan2(val, val2);
        }

        static float Ceil(float val)
        {
            return ceil(val);
        }

        static float Clamp(float val, float min, float max)
        {
            return std::clamp(val, min, max);
        }

        static float Clamp01(float val)
        {
            return Mathf::Clamp(val, 0.0, 1.0);
        }

        static float Cos(float val)
        {
            return std::cos(val);
        }

        static float DeltaAngle(float val, float val2)
        {
            float diff = ( (int)val2 - (int)val + 180 ) % 360 - 180;
            return diff < -180 ? diff + 360 : diff;
        }

        static float Exp(float val)
        {
            return std::exp(val);
        }

        static float Floor(float val) 
        {
            return floor(val);
        }

        static float Round(float val)
        {
            return round(val);
        }

        static float Lerp(float val, float target, float interpolation)
        {
            return std::lerp(val, target, interpolation);
        }

        static float Max(float val, float val2)
        {
            return std::max(val, val2);
        }

        static float Min(float val, float val2)
        {
            return std::min(val, val2);
        }

        static float MoveTowards(float val, float target, float delta)
        {
            if(val > target)
            {
                return Mathf::Clamp(val + delta, val, target);
            }
            else
            {
                return Mathf::Clamp(val - delta, target, val);
            }
        }

        static float Pow(float val, float val2)
        {
            return std::pow(val, val2);
        }

        static float Sin(float val)
        {
            return std::sin(val);
        }

        static float Sqrt(float val)
        {
            return sqrt(val);
        }

        static float Tan(float val)
        {
            return std::tan(val);
        }
    };

    struct Vector2
    {
        float x, y;
        Vector2(float xpos, float ypos)
        {
            x = xpos;
            y = ypos;
        }

        // Move this to the Camera script
        Vector2 RelativeToOrigin(sf::RenderWindow screen)
        {
            return Vector2(screen.getSize().x/2 + x, screen.getSize().y/2 + y);
        }

        Vector2 OriginToRelative()
        {
            return Vector2(x - WIDTH/2, y - HEIGHT/2);
        }

        static sf::Vector2f SFMLRelativeToOriginal(sf::Vector2f vec)
        {
            return sf::Vector2f(WIDTH/2 + vec.x, HEIGHT/2 + vec.y);
        }

        static sf::Vector2f SFMLOriginToRelative(sf::Vector2f vec)
        {
            return sf::Vector2f(WIDTH/2 - vec.x, HEIGHT/2 - vec.y);
        }
        // this

        Vector2 operator+(Vector2 vec2)
        {
            return Vector2(x + vec2.x, y + vec2.y);
        }

        Vector2 operator-(Vector2 vec2)
        {
            return Vector2(x - vec2.x, y - vec2.y);
        }

        Vector2 operator*(float val)
        {
            return Vector2(x * val, y * val);
        }

        Vector2 operator/(float val)
        {
            return Vector2(x / val, y / val);
        }

        bool operator==(Vector2 vec)
        {
            if(Mathf::Approximately(x, vec.x) && Mathf::Approximately(y, vec.y))
            {
                return true;
            }
            return false;
        }

        static Vector2 Down()
        {
            return Vector2(0.0, -1.0);
        }

        static Vector2 Left()
        {
            return Vector2(-1.0, 0.0);
        }

        static Vector2 NegativeInfinity()
        {
            return Vector2(Mathf::NegativeInfinity, Mathf::NegativeInfinity);
        }

        static Vector2 One()
        {
            return Vector2(1.0, 1.0);
        }

        static Vector2 PositiveInfinity()
        {
            return Vector2(Mathf::PositiveInfinity, Mathf::PositiveInfinity);
        }

        static Vector2 Right()
        {
            return Vector2(1.0, 0.0);
        }

        static Vector2 Up()
        {
            return Vector2(0.0, 1.0);
        }

        static Vector2 Zero()
        {
            return Vector2(0.0, 0.0);
        }

        float Magnitude()
        {
            return Mathf::Sqrt((x * x) + (y * y));
        }

        Vector2 Normalized()
        {
            float mag = Magnitude();
            return Vector2(x/mag, y/mag);
        }

        float SqrMagnitude()
        {
            return (x * x) + (y * y);
        }

        bool Equals(Vector2 vec)
        {
            if(x == vec.x && y == vec.y)
            {
                return true;
            }
            return false;
        }

        void Normalize()
        {
            x = Normalized().x;
            y = Normalized().y;
        }

        void Set(Vector2 vec)
        {
            x = vec.x;
            y = vec.y;
        }

        std::string ToString()
        {
            return "Vector2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
        }

        static float Distance(Vector2 vec1, Vector2 vec2)
        {
            return (vec2 - vec1).Magnitude();
        }

        static Vector2 Lerp(Vector2 start, Vector2 end, float delta)
        {
            return Vector2(Mathf::Lerp(start.x, end.x, delta), Mathf::Lerp(start.y, end.y, delta));
        }

        static Vector2 Max(Vector2 vec1, Vector2 vec2)
        {
            return Vector2(Mathf::Max(vec1.x, vec2.x), Mathf::Max(vec1.y, vec2.y));
        }

        static Vector2 Min(Vector2 vec1, Vector2 vec2)
        {
            return Vector2(Mathf::Min(vec1.x, vec2.x), Mathf::Min(vec1.y, vec2.y));
        }

        static Vector2 MoveTowards(Vector2 vec1, Vector2 vec2, float delta)
        {
            return Vector2(Mathf::MoveTowards(vec1.x, vec2.x, delta), Mathf::MoveTowards(vec1.y, vec2.y, delta));
        }

        static Vector2 PerpendicularClockwise(Vector2 vec)
        {
            return Vector2(vec.y, -vec.x);
        }

        static Vector2 PerpendicularCounterClockwise(Vector2 vec)
        {
            return Vector2(-vec.y, vec.x);
        }

        // static Vector2 Reflect(Vector2 vec, Vector2 normal)
        // {
        // https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
        // }
    };

    class Debug
    {
        public:
            static void Log(std::string str)
            {
                std::cout<<"\033[0;37m"<<str<<"\033[0m\n";
            }

            static void LogError(std::string str)
            {
                std::cout<<"\033[0;31m"<<str<<"\033[0m\n";
            }

            static void LogWarning(std::string str)
            {
                std::cout<<"\033[0;33m"<<str<<"\033[0m\n";
            }

            static void LogSuccess(std::string str)
            {
                std::cout<<"\033[0;32m"<<str<<"\033[0m\n";
            }

            static void DrawLine(Vector2 start, Vector2 end, sf::Color color, sf::RenderWindow& screen)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(Vector2::SFMLOriginToRelative(sf::Vector2f(start.x, start.y)), color),
                    sf::Vertex(Vector2::SFMLOriginToRelative(sf::Vector2f(end.x, end.y)), color)
                };

                screen.draw(line, 2, sf::Lines);
            }

            static void DrawRay(Vector2 start, Vector2 dir, sf::Color color, sf::RenderWindow& screen)
            {
                Debug::DrawLine(start, dir, color, screen);
            }
    };

    class Renderer
    {
        public:
            static void DrawSprite(std::string path, sf::RenderWindow& screen)
            {
                sf::Texture texture;
                if (!texture.loadFromFile(path))
                {
                    Debug::LogError("Error loading sprite from " + path);
                    return;
                }

                sf::Image image;
                texture.update(image);
                texture.setSmooth(true);

                sf::Sprite sprite;
                sprite.setTexture(texture);

                screen.draw(sprite);
            }
    };

    class Input
    {
        public:
            static Vector2 MousePosition(sf::RenderWindow& screen)
            {
                sf::Vector2i vec = sf::Mouse::getPosition(screen);
                return Vector2(vec.x, vec.y);
            }
    };

    struct Scene
    {
    };

    class GameObject;

    class BehaviourScript
    {
        public:
            bool enabled = true;
            GameObject *gameObject;
            std::string baseClassName;
            // Transform transform;
            virtual void Start(){}
            virtual void Update(sf::RenderWindow& screen){;}
            virtual void FixedUpdate(){}
            virtual void Invoke(std::string methodName, float time)
            {
                Debug::LogWarning("Invoke not Implemented yet.");
            }

            bool operator==(BehaviourScript script)
            {
                if(enabled == script.enabled && gameObject == script.gameObject /* && transform == script.transform*/)
                {
                    return true;
                }
                return false;
            }
    };

    class GameObject
    {
        public:
            bool isActive = true;
            int layer = 0;
            Scene scene;
            std::string name = "New GameObject";
            std::string tag = "Default";
            // Transform transform;
            std::vector<BehaviourScript*> components;

            GameObject()
            {
                isActive = true;
                layer = 0;
                tag = "Default";
                name = "New GameObject";
            }

            GameObject(std::string _name)
            {
                isActive = true;
                layer = 0;
                tag = "Default";
                name = _name;
            }

            void AddComponent(BehaviourScript* script)
            {
                components.push_back(script);
            }

            BehaviourScript* GetComponent(std::string checkScript)
            {
                for(BehaviourScript* script:this->components)
                {
                    if(script->baseClassName == checkScript)
                    {
                        return script;
                    }
                }
                return nullptr;
            }
    };

    class Transform : public BehaviourScript
    {
        public:
            Vector2 position = Vector2(0.0, 0.0);
            float rotation;

            Transform(Vector2 pos, float rot)
            {
                position = pos;
                rotation = rot;
                baseClassName = "Transform";
            }
    };

    class SpriteRenderer : public BehaviourScript
    {
        public:
            std::string spritePath;

            SpriteRenderer(std::string str)
            {
                spritePath = str;
                baseClassName = "SpriteRenderer";
            }

            void Update(sf::RenderWindow& screen)
            {
                Renderer::DrawSprite(spritePath, screen);
            }
    };
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