#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "../engine/vector2.h"
#include <SFML/Graphics.hpp>
#include "../engine/color.h"
#include "../engine/debug.h"
#include "../engine/application.h"

namespace DT
{
    namespace Renderer
    {
        extern std::vector<std::pair<std::string, sf::Texture>> textureCache;

        int LoadTextureFromCache(std::string _path);

        void DrawSprite(std::string path, Vector2 pos, float rot, Vector2 scl, int pixelPerUnit, Color _color);
    };
}

#endif