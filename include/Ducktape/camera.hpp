#pragma once
#include "behaviourscript.hpp"

class Camera : public BehaviourScript
{
    public:
        float size = 1.0;
        
        void Update();

        static Vector2 ScreenToWorldPos(Vector2 pos);

        static Vector2 WorldToScreenPos(Vector2 pos);

        static float PPU();
};