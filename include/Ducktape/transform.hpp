#pragma once
#include "vector2.hpp"
#include "behaviourscript.hpp"

class Transform : public BehaviourScript
{
    public:
        Vector2 position = Vector2(0.0, 0.0);
        float rotation;
        Vector2 scale = Vector2(1.0, 1.0);
};