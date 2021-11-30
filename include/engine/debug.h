#ifndef DEBUG_H
#define DEBUG_H

#define FATAL_ERROR 8

#include <stdlib.h>

class Debug
{
public:
    // valing
    static void Log(std::string val)
    {
        std::cout<<"\033[0;37m"<<val<<"\033[0m\n";
    }

    static void LogError(std::string val)
    {
        std::cout<<"\033[0;31m"<<val<<"\033[0m\n";
    }

    static void LogFatalError(std::string val)
    {
        std::cout << "\033[0;31m [FATAL ERR] " << val << "\033[0m" << std::endl;
        exit(FATAL_ERROR);
    }

    static void LogWarning(std::string val)
    {
        std::cout<<"\033[0;33m"<<val<<"\033[0m\n";
    }

    static void LogSuccess(std::string val)
    {
        std::cout<<"\033[0;32m"<<val<<"\033[0m\n";
    }

    // float overload

    static void Log(float val)
    {
        std::cout<<"\033[0;37m"<<val<<"\033[0m\n";
    }

    static void LogError(float val)
    {
        std::cout<<"\033[0;31m"<<val<<"\033[0m\n";
    }

    static void LogFatalError(float val)
    {
        std::cout << "\033[0;31m [FATAL ERR]" << val << "\033[0m" << std::endl;
        exit(FATAL_ERROR);
    }

    static void LogWarning(float val)
    {
        std::cout<<"\033[0;33m"<<val<<"\033[0m\n";
    }

    static void LogSuccess(float val)
    {
        std::cout<<"\033[0;32m"<<val<<"\033[0m\n";
    }

    static void DrawLine(Vector2 start, Vector2 end, sf::Color color)
    {
        // sf::Vertex line[] =
        // {
        //     sf::Vertex(Vector2::SFMLOriginToRelative(sf::Vector2f(start.x, start.y)), color),
        //     sf::Vertex(Vector2::SFMLOriginToRelative(sf::Vector2f(end.x, end.y)), color)
        // };

        // Application::renderWindow.draw(line, 2, sf::Lines);
    }

    static void DrawRay(Vector2 start, Vector2 dir, sf::Color color)
    {
        Debug::DrawLine(start, dir, color);
    }
};

#endif