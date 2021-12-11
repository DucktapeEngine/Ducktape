#ifndef BOXCOLLIDER2D_H
#define BOXCOLLIDER2D_H

#include "../engine/entity.h"
#include "../engine/scripts.h"
#include "rigidbody.h"

namespace DT
{
    class BoxCollider2D : public PhysicsScript
    {
    public:
        Rigidbody2D* rb;

        Vector2 scale = Vector2(1.0f, 1.0f);
        float density = 1.0f;
        float friction = 0.3f;
        bool isTrigger = false;
        
        void Start();
    };
}

#endif