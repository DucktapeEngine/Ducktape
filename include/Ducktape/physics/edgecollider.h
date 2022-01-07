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
#include <Ducktape/engine/scripts.h>
#include <Ducktape/physics/rigidbody.h>
#include <Ducktape/engine/entity.h>

namespace DT
{
    class EdgeCollider2D : public PhysicsScript
    {
    private:
        Rigidbody2D* rb;
        b2Fixture* fixture;
        std::vector<Vector2> points;

    public:
        EdgeCollider2D();

        void Update();

        std::vector<Vector2> GetPoints();
        float GetDensity();
        float GetFriction();
        bool GetIsTrigger();
        void SetPoints(std::vector<Vector2> points);
        void SetDensity(float val);
        void SetFriction(float val);
        void SetIsTrigger(bool val);
    };
}

#endif