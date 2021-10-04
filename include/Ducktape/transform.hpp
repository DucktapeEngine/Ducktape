#pragma once
#include "vector2.hpp"
#include "behaviourscript.hpp"

class Transform : public BehaviourScript
{
    public:
        Vector2 position = Vector2(0.0, 0.0);
        float rotation{0.0f};
        Vector2 scale = Vector2(1.0, 1.0);

        Transform() = default;

        Transform(Vector2 pos, float rot, Vector2 scl)
            : position(pos), rotation(rot), scale(scl)
        {
        }
};
