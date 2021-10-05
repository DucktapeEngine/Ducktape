#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Vector2;

class Debug
{
    public:
        static void Log(std::string str);
        static void LogError(std::string str);
        static void LogWarning(std::string str);

        static void LogSuccess(std::string str);

        static void DrawLine(Vector2 start, Vector2 end, sf::Color color, sf::RenderWindow& screen);

        static void DrawRay(Vector2 start, Vector2 dir, sf::Color color, sf::RenderWindow& screen);
};