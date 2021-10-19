#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "vector2.hpp"

class Debug
{
    public:
        static void Log(std::string str);

        static void LogError(std::string str);

        static void LogWarning(std::string str);

        static void LogSuccess(std::string str);

        static void DrawLine(Vector2 start, Vector2 end, sf::Color color);

        static void DrawRay(Vector2 start, Vector2 dir, sf::Color color);
};