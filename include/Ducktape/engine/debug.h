#ifndef DEBUG_H
#define DEBUG_H

#define FATAL_ERROR 8

#include "vector2.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace DT
{
    namespace Debug
    {
        // valing
        void Log(std::string val);

        void LogError(std::string val);

        void LogFatalError(std::string val);

        void LogWarning(std::string val);

        void LogSuccess(std::string val);

        // float overload

        void Log(float val);

        void LogError(float val);

        void LogFatalError(float val);

        void LogWarning(float val);

        void LogSuccess(float val);

        void DrawLine(Vector2 start, Vector2 end, sf::Color color);

        void DrawRay(Vector2 start, Vector2 dir, sf::Color color);
    };
}

#endif