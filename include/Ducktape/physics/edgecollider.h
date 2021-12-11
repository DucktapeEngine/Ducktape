#ifndef EDGECOLLIDER2D_H
#define EDGECOLLIDER2D_H

#include "../engine/scripts.h"
#include "rigidbody.h"
#include "../engine/entity.h"

namespace DT
{
    class EdgeCollider2D : public PhysicsScript
    {
    public:
        Rigidbody2D* rb;

        std::vector<Vector2> points;
        float density = 1.0f;
        float friction = 0.3f;
        bool isTrigger = false;
        
        void Start();
    };
}

#endif