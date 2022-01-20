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

#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <Ducktape/engine/vector2.h>
#include <Ducktape/engine/color.h>
#include <Ducktape/engine/debug.h>
#include <Ducktape/engine/application.h>

namespace DT
{
    namespace Renderer
    {
        extern std::vector<std::pair<std::string, sf::Texture>> textureCache;

        int loadTextureFromCache(std::string _path);

        void drawSprite(std::string path, Vector2 pos, float rot, Vector2 scl, int pixelPerUnit, Color _color);
    };
}

#endif