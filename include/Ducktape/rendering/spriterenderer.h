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
     * 
     * The `SpriteRenderer` component allows you to render sprites to the screen. Ducktape allows the bmp, png, tga and jpg file formats.
     * To get started, add this component to an `Entity`, and then use the `SpriteRenderer::SetSpritePath()` method to set the path to the sprite to be rendered. Note that this path must be relative to the executable.
     * 
     * That's it, yep, it's as simple as that. 
     * 
     * But there's more -- Ducktape also allows you to set the sprite's color, and pixel per unit constant to use while rendering the image. The transform properties like position, rotation, and scale are controlled by the `Entity`'s `Transform` component's properties. But additionally, you may add an additional offset using the `SpriteRenderer::SetOffset()` method that accepts `(Vector2 offsetPosition, float offsetRotation, Vector2 offsetScale)`.
     * 
     * Note: The end transform result is gotten by multiplying the properties of `entity->transform` and the specified offset.
     * 
     * Example:
     * ```cpp
     * // Create a new entity
     * Entity* player = Entity::Instantiate("Player");
     * player->AddComponent<SpriteRenderer>()
     *       ->SetSpritePath("assets/player.png")
     *       ->SetOffset(Vector2(0.0f, 0.0f), 90.0f, Vector2(1.0f, 1.0f));
     * ```
     * 
     * Cheers!
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