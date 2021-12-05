#include "debug.h"
using namespace DT;

void Debug::Log(std::string val)
{
    std::cout<<"\033[0;37m"<<val<<"\033[0m\n";
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
    std::cout<<"\033[0;33m"<<val<<"\033[0m\n";
}

void Debug::LogSuccess(std::string val)
{
    std::cout<<"\033[0;32m"<<val<<"\033[0m\n";
}

void Debug::Log(float val)
{
    std::cout<<"\033[0;37m"<<val<<"\033[0m\n";
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
    std::cout<<"\033[0;33m"<<val<<"\033[0m\n";
}

void Debug::LogSuccess(float val)
{
    std::cout<<"\033[0;32m"<<val<<"\033[0m\n";
}

void Debug::DrawLine(Vector2 start, Vector2 end, sf::Color color)
{
    // sf::Vertex line[] =
    // {
    //     sf::Vertex(Vector2::SFMLOriginToRelative(sf::Vector2f(start.x, start.y)), color),
    //     sf::Vertex(Vector2::SFMLOriginToRelative(sf::Vector2f(end.x, end.y)), color)
    // };

    // Application::renderWindow.draw(line, 2, sf::Lines);
}

void Debug::DrawRay(Vector2 start, Vector2 dir, sf::Color color)
{
    Debug::DrawLine(start, dir, color);
}