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
        b2Body *body;

        Rigidbody2D();

        void tick();

        Vector2 getVelocity();
        void setVelocity(Vector2 val);
        float getAngularVelocity();
        void setAngularVelocity(float val);
        float getMass();
        void setMass(float mass);
        void setCenterOfMass(Vector2 center);
        float getInertia();
        float getDamping();
        void setDamping(float damping);
        float getAngularDamping();
        void setAngularDamping(float damping);
        float getGravityScale();
        void setGravityScale(float scale);
        BodyType getType();
        void setType(BodyType type);
        bool getContinous();
        void setContinous(bool flag);
        bool getSleepingAllowed();
        void setSleepingAllowed(bool flag);
        bool getAwake();
        void setAwake(bool flag);

        void OnEnable()
        {
            body->SetEnabled(true);
        }

        void OnDisable()
        {
            body->SetEnabled(false);
        }

        bool getFixedRotation();
        void setFixedRotation(bool flag);

        void applyForce(Vector2 force);
        void applyForceAtPoint(Vector2 force, Vector2 point);
        void applyTorque(float torque);
        void applyLinearImpulse(Vector2 impulse);
        void applyLinearImpulseAtPoint(Vector2 impulse, Vector2 point);
        void applyAngularImpulse(float impulse);

        void onDestroy();
    };
}

#endif