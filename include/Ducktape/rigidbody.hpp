#pragma once
#include "vector2.hpp"
#include <string>
#include "include/box2d/include/box2d/box2d.h"
#include "behaviourscript.hpp"

class Rigidbody : public BehaviourScript
{
    public:
        Vector2 velocity;
        float gravityScale = 1.0;
        std::string type;
        std::string colliderType;
        bool isTrigger = false;
        b2Body* body;

        // Box Collider
        Vector2 scale = Vector2(1.0, 1.0);

        void Start();

        void MidUpdate();

        void Update();

        void LateUpdate();
};
