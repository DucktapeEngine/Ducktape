#ifndef POLYGONCOLLIDER2D_H
#define POLYGONCOLLIDER2D_H

#include "../engine/scripts.h"
#include "rigidbody.h"
#include "../engine/gameobject.h"

namespace DT
{
    class PolygonCollider2D : public PhysicsScript
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