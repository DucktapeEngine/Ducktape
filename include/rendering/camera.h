#ifndef CAMERA_H
#define CAMERA_H

#include "../engine/scripts.h"
#include "../engine/vector2.h"
#include "../engine/application.h"
#include "../engine/gameobject.h"
#include "../engine/transform.h"

namespace DT
{
    class Camera : public RenderScript
    {
    public:
        float size = 1.0;
        
        void Update();

        static Vector2 UnitToPixel(Vector2 pos);

        static Vector2 ScreenToWorldPos(Vector2 pos);

        static Vector2 WorldToScreenPos(Vector2 pos);
        
        static float PixelPerUnit();
    };
}

#endif