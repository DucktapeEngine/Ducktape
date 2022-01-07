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

#include <Ducktape/engine/debug.h>
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