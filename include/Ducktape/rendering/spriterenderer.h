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

#ifndef DUCKTAPE_RENDERING_SPRITERENDERER_H_
#define DUCKTAPE_RENDERING_SPRITERENDERER_H_

#include <string>

#include <Ducktape/engine/vector2.h>
#include <Ducktape/engine/behaviourscript.h>
#include <Ducktape/engine/color.h>
#include <Ducktape/rendering/renderer.h>
#include <Ducktape/rendering/camera.h>

namespace DT
{
    /**
     * @brief Component to render sprites to the screen.
     */
    class SpriteRenderer : public BehaviourScript
    {
    private:
        /**
         * @brief Path to the sprite to be rendered.
         */
        std::string spritePath;
        /**
         * @brief The pixel per unit to be used to draw the sprite.
         */
        float pixelPerUnit = 1;

        /**
         * @brief The color of the sprite.
         */
        Color color = Color(255, 255, 255, 255);

    public:
        void SetSpritePath(std::string newSpritePath);
        void SetPixelPerUnit(float newPixelPerUnit);
        void SetColor(Color newColor);

        std::string GetSpritePath();
        float GetPixelPerUnit();
        Color GetColor();

        void Tick();
    };
}

#endif