#ifndef CIRCLECOLLIDER2D_H
#define CIRCLECOLLIDER2D_H

#include "../engine/scripts.h"
#include "rigidbody.h"
#include "../engine/gameobject.h"

namespace DT
{
    class CircleCollider2D : public PhysicsScript
    {
    public:
        Rigidbody2D* rb;

        float density = 1.0f;
        float friction = 0.3f;
        bool isTrigger = false;
        float radius = 1.0f;
        
        void Start();
    };
}

#endif