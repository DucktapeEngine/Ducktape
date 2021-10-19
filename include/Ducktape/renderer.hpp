#pragma once
#include <string>
#include "vector2.hpp"

class Renderer
{
    public:
        static void DrawSprite(std::string path, Vector2 pos, float rot, Vector2 scl);
};