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

#ifndef DUCKTAPE_PHYSICS_RIGIDBODY2D_H_
#define DUCKTAPE_PHYSICS_RIGIDBODY2D_H_

#include <box2d/box2d.h>

#include <Ducktape/engine/behaviourscript.h>
#include <Ducktape/engine/entity.h>
#include <Ducktape/physics/physics.h>
#include <Ducktape/engine/transform.h>

namespace DT
{
    /**
     * @brief Enum for specifying type of physical behaviour of the `Rigidbody2D`.
     */
    enum BodyType
    {
        /**
         * @brief Enum for static, kinematic, and dynamic bodies.
         *
         * Static bodies are bodies that are not affected by forces or
         * collisions. They are not supposed to be moved at all, and they only collide
         * with dynamic bodies.
         *
         * Kinematic bodies are not affected by gravity or applied forces. And they only
         * collide with dynamic bodies.
         *
         * Dynamic bodies react to gravity and applied forces including contacts with other dynamic or kinematic rigidbodies.
         */
        staticBody = 0,
        kinematicBody,
        dynamicBody
    };

    /**
     * @brief Control of an object's position through physics simulation.
     * 
     * Adding a Rigidbody component to an object will put its motion under the control of Ducktape's physics engine. Even without adding any code, a Rigidbody object will be pulled downward by gravity and will react to collisions with incoming objects if the right Collider component is also present.
     */
    class Rigidbody2D : public BehaviourScript
    {
    private:
        /**
         * @brief The gravity scale of the rigidbody. The gravity affected by the Rigidbody will be ProjectSettings::globalGravity * Rigidbody2D::gravityScale.
         */
        float gravityScale = 1.0f;

    public:
        b2Body *body;

        void Constructor();

        void Tick();

        /**
         * @brief Get the velocity of the rigidbody.
         *
         * @return Vector2 The velocity of the rigidbody.
         */
        Vector2 GetVelocity();

        /**
         * @brief Set the velocity of the rigidbody.
         *
         * @param val The velocity of the rigidbody.
         */
        void SetVelocity(Vector2 val);

        /**
         * @brief Get the angular velocity of the rigidbody.
         *
         * @return float The angular velocity of the rigidbody.
         */
        float GetAngularVelocity();

        /**
         * @brief Set the angular velocity of the rigidbody.
         *
         * @param val The angular velocity of the rigidbody.
         */
        void SetAngularVelocity(float val);

        /**
         * @brief Get the mass of the rigidbody.
         *
         * @return float The mass of the rigidbody.
         */
        float GetMass();

        /**
         * @brief Set the mass of the rigidbody.
         *
         * @param mass The mass of the rigidbody.
         */
        void SetMass(float mass);

        /**
         * @brief Set the Center of Mass of the rigidbody.
         *
         * @param center
         */
        void SetCenterOfMass(Vector2 center);

        /**
         * @brief Get the inertia of the rigidbody.
         *
         * @return float The inertia of the rigidbody.
         */
        float GetInertia();

        /**
         * @brief Get the damping of the rigidbody.
         *
         * @return float The damping of the rigidbody.
         */
        float GetDamping();

        /**
         * @brief Set the damping of the rigidbody.
         *
         * @param damping The damping of the rigidbody.
         */
        void SetDamping(float damping);

        /**
         * @brief Get the angular damping of the rigidbody.
         *
         * @return float The angular damping of the rigidbody.
         */
        float GetAngularDamping();

        /**
         * @brief Set the angular damping of the rigidbody.
         *
         * @param damping The angular damping of the rigidbody.
         */
        void SetAngularDamping(float damping);

        /**
         * @brief Get the gravity scale of the rigidbody.
         *
         * @return float The gravity scale of the rigidbody.
         */
        float GetGravityScale();

        /**
         * @brief Set the gravity scale of the rigidbody.
         *
         * @param scale The gravity scale of the rigidbody.
         */
        void SetGravityScale(float scale);

        /**
         * @brief Get the body type of the rigidbody.
         *
         * @return BodyType The body type of the rigidbody.
         */
        BodyType GetType();

        /**
         * @brief Set the body type of the rigidbody.
         *
         * @param type The body type of the rigidbody.
         */
        void SetType(BodyType type);

        /**
         * @brief Get if the body's collision is set to be continous.
         *
         * @return bool If the body's collision is set to be continous.
         */
        bool GetContinous();

        /**
         * @brief Set if the body's collision is set to be continous.
         *
         * @param flag If the body's collision is set to be continous.
         */
        void SetContinous(bool flag);

        /**
         * @brief Get if the body is allowed to sleep.
         *
         * @return true If the body is allowed to sleep.
         */
        bool GetSleepingAllowed();

        /**
         * @brief Set if the body is allowed to sleep.
         * it.
         *
         * @param flag If the body is allowed to sleep.
         */
        void SetSleepingAllowed(bool flag);

        /**
         * @brief Get if the body is sleeping.
         *
         * @return bool If the body is sleeping.
         */
        bool GetAwake();

        /**
         * @brief Set if the body is sleeping.
         *
         * @param flag If the body is allowed to sleep.
         */
        void SetAwake(bool flag);

        void OnEnable()
        {
            body->SetEnabled(true);
        }

        void OnDisable()
        {
            body->SetEnabled(false);
        }

        /**
         * @brief Get if the body's rotation is fixed.
         *
         * @return bool If the body's rotation is fixed.
         */
        bool GetFixedRotation();

        /**
         * @brief Set if the body's rotation is fixed.
         *
         * @param flag If the body's rotation is fixed.
         */
        void SetFixedRotation(bool flag);

        /**
         * @brief Apply a force to the rigidbody.
         *
         * @param force The force to apply.
         */
        void ApplyForce(Vector2 force);

        /**
         * @brief Apply a force to the rigidbody at a given position.
         *
         * @param force The force to apply.
         * @param point The position to apply the force at.
         */
        void ApplyForceAtPoint(Vector2 force, Vector2 point);

        /**
         * @brief Apply a torque to the rigidbody.
         *
         * @param torque
         */
        void ApplyTorque(float torque);

        /**
         * @brief Apply a impulse to the rigidbody.
         *
         * @param impulse The impulse to apply.
         */
        void ApplyImpulse(Vector2 impulse);

        /**
         * @brief Apply a impulse to the rigidbody at a given position.
         *
         * @param impulse The impulse to apply.
         * @param point The position to apply the impulse at.
         */
        void ApplyImpulseAtPoint(Vector2 impulse, Vector2 point);

        /**
         * @brief Apply an angular impulse to the rigidbody.
         *
         * @param impulse The angular impulse to apply.
         */
        void ApplyAngularImpulse(float impulse);

        void OnDestroy();
    };
}

#endif