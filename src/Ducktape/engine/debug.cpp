#include "debug.h"
using namespace DT;

void Debug::Log(std::string val)
{
    #ifndef PRODUCTION
    std::cout<<"\033[0;37m"<<val<<"\033[0m\n";
    #endif
}

void Debug::LogError(std::string val)
{
    std::cout<<"\033[0;31m"<<val<<"\033[0m\n";
}

void Debug::LogFatalError(std::string val)
{
    std::cout << "\033[0;31m [FATAL ERR] " << val << "\033[0m" << std::endl;
    exit(FATAL_ERROR);
}

void Debug::LogWarning(std::string val)
{
    #ifndef PRODUCTION
    std::cout<<"\033[0;33m"<<val<<"\033[0m\n";
    #endif
}

void Debug::LogSuccess(std::string val)
{
    #ifndef PRODUCTION
    std::cout<<"\033[0;32m"<<val<<"\033[0m\n";
    #endif
}

void Debug::Log(float val)
{
    #ifndef PRODUCTION
    std::cout<<"\033[0;37m"<<val<<"\033[0m\n";
    #endif
}

void Debug::LogError(float val)
{
    std::cout<<"\033[0;31m"<<val<<"\033[0m\n";
}

void Debug::LogFatalError(float val)
{
    std::cout << "\033[0;31m [FATAL ERR]" << val << "\033[0m" << std::endl;
    exit(FATAL_ERROR);
}

void Debug::LogWarning(float val)
{
    #ifndef PRODUCTION
    std::cout<<"\033[0;33m"<<val<<"\033[0m\n";
    #endif
}

void Debug::LogSuccess(float val)
{
    #ifndef PRODUCTION
    std::cout<<"\033[0;32m"<<val<<"\033[0m\n";
    #endif
}

void Debug::DrawLine(Vector2 start, Vector2 end, Color color)
{
    #ifndef PRODUCTION
    // sf::Vertex line[] =
    // {
    //     sf::Vertex(Vector2::SFMLOriginToRelative(sf::Vector2f(start.x, start.y)), color),
    //     sf::Vertex(Vector2::SFMLOriginToRelative(sf::Vector2f(end.x, end.y)), color)
    // };

    // Application::renderWindow.draw(line, 2, sf::Lines);
    #endif
}

void Debug::DrawRay(Vector2 start, Vector2 dir, Color color)
{
    #ifndef PRODUCTION
    Debug::DrawLine(start, dir, color);
    #endif
}