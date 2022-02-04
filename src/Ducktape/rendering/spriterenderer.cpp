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

#include <Ducktape/rendering/spriterenderer.h>
using namespace DT;

void SpriteRenderer::setSpritePath(std::string newSpritePath)
{
    spritePath = newSpritePath;
}

void SpriteRenderer::setPixelPerUnit(float newPixelPerUnit)
{
    pixelPerUnit = newPixelPerUnit;
}

void SpriteRenderer::setColor(Color newColor)
{
    color = newColor;
}

Color SpriteRenderer::getColor()
{
    return color;
}

float SpriteRenderer::getPixelPerUnit()
{
    return pixelPerUnit;
}

std::string SpriteRenderer::getSpritePath()
{
    return spritePath;
}

void SpriteRenderer::tick()
{
    if (spritePath != "")
    {
        Renderer::drawSprite(spritePath, Camera::worldToScreenPos(entity->transform->getPosition()), entity->transform->getRotation(), entity->transform->getScale(), pixelPerUnit, color);
    }
}