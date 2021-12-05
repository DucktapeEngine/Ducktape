#ifndef RIGIDBODY2D_H
#define RIGIDBODY2D_H

#include "../engine/scripts.h"
#include "../engine/gameobject.h"
#include "physics.h"
#include "../engine/transform.h"

namespace DT
{
    class Rigidbody2D : public BaseScript
    {
    public:
        float gravityScale = 1.0;
        std::string type;
        bool isTrigger = false;
        b2Body* body;

        float linearDamping = 0.0f;
        float angularDamping = 0.01f;
        bool allowSleep = true;
        bool continousCollision = false;

        void Start();

        void Update();

        void OnTransformChange();

        Vector2 GetVelocity();

        Vector2 SetVelocity(Vector2 _vel);
        
        void AddForce(Vector2 direction);

        void AddForceAtPoint(Vector2 direction, Vector2 point);

        void AddTorque(float torque);

        template <typename T>
        void DestroyJoint();

        void Destroy();
    };
}

#endif