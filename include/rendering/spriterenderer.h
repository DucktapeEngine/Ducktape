#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "../engine/vector2.h"
#include <string>
#include "../engine/scripts.h"
#include "../engine/color.h"
#include "renderer.h"
#include "camera.h"

namespace DT
{
    class SpriteRenderer : public RenderScript
    {
    public:
        std::string spritePath;
        int pixelPerUnit = 1;
        Color color = Color(255, 255, 255, 255);
        
        void Update();
    };
}

#endif