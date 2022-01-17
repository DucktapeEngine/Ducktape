/*
MIT License

Copyright (c) 2022 Ducktape

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef RIGIDBODY2D_H
#define RIGIDBODY2D_H

#include <box2d/box2d.h>
#include <Ducktape/engine/behaviourscript.h>
#include <Ducktape/engine/entity.h>
#include <Ducktape/physics/physics.h>
#include <Ducktape/engine/transform.h>

namespace DT
{
    enum BodyType
    {
        staticBody = 0,
        kinematicBody,
        dynamicBody
    };

    class Rigidbody2D : public BehaviourScript
    {
    private:
        float gravityScale = 1.0f;
        
    public:
        b2Body* body;

        Rigidbody2D(Entity* _entity);

        void Update();

        Vector2 GetVelocity();
        void SetVelocity(Vector2 val);
        float GetAngularVelocity();
        void SetAngularVelocity(float val);
        float GetMass();
        void SetMass(float mass);
        void SetCenterOfMass(Vector2 center);
        float GetInertia();
        float GetDamping();
        void SetDamping(float damping);
        float GetAngularDamping();
        void SetAngularDamping(float damping);
        float GetGravityScale();
        void SetGravityScale(float scale);
        BodyType GetType();
        void SetType(BodyType type);
        bool GetContinous();
        void SetContinous(bool flag);
        bool GetSleepingAllowed();
        void SetSleepingAllowed(bool flag);
        bool GetAwake();
        void SetAwake(bool flag);
        void OnEnable();
        void OnDisable();
        bool GetFixedRotation();
        void SetFixedRotation(bool flag);
        
        void ApplyForce(Vector2 force);
        void ApplyForceAtPoint(Vector2 force, Vector2 point);
        void ApplyTorque(float torque);
        void ApplyLinearImpulse(Vector2 impulse);
        void ApplyLinearImpulseAtPoint(Vector2 impulse, Vector2 point);
        void ApplyAngularImpulse(float impulse);

        void Destroy();
    };
}

#endif