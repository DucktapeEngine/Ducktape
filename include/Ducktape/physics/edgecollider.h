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

#ifndef EDGECOLLIDER2D_H
#define EDGECOLLIDER2D_H

#include <box2d/box2d.h>
#include <Ducktape/engine/behaviourscript.h>
#include <Ducktape/physics/rigidbody.h>
#include <Ducktape/engine/entity.h>

namespace DT
{
    class EdgeCollider2D : public BehaviourScript
    {
    private:
        Rigidbody2D *rb;
        b2Fixture *fixture;
        std::vector<Vector2> points;

    public:
        EdgeCollider2D();

        void tick();

        /**
         * @brief Get the points of the collider.
         * @return std::vector<Vector2> The points of the collider.
         */
        std::vector<Vector2> getPoints();

        /**
         * @brief Get the density of the collider.
         * @return float The density of the collider.
         */
        float getDensity();

        /**
         * @brief Get the friction of the collider.
         * @return Vector2 The friction of the collider.
         */
        float getFriction();

        /**
         * @brief Get if the collider is a trigger or not.
         * 
         * @return bool If the collider is a trigger or not.
         */
        bool getIsTrigger();

        /**
         * @brief Set the points of the collider.
         * @param points The points of the collider.
         */
        void setPoints(std::vector<Vector2> points);
        
        /**
         * @brief Set the density of the collider.
         * @param float The density of the collider.
         */
        void setDensity(float val);

        /**
         * @brief Set the friction of the collider.
         * @param float The friction of the collider.
         */
        void setFriction(float val);

        /**
         * @brief Set if the collider is a trigger or not.
         * @param bool If the collider is a trigger or not.
         */
        void setIsTrigger(bool val);
    };
}

#endif