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

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>
#include <box2d/box2d.h>
#include <Ducktape/engine/behaviourscript.h>
#include <Ducktape/engine/vector2.h>
#include <Ducktape/physics/rigidbody.h>

namespace DT
{
    class Transform : public BehaviourScript
    {
    private:
        Vector2 position = Vector2(0.0, 0.0);
        float rotation;
        Vector2 scale = Vector2(1.0, 1.0);

        Vector2 localPosition = Vector2(0.0, 0.0);
        float localRotation;
        Vector2 localScale = Vector2(1.0, 1.0);

        void OnTransformChange();

    public:
        Transform(Entity* _entity);

        Transform* parent = nullptr;
        std::vector<Transform*> children;    

        Vector2 SetPosition(Vector2 _pos);

        Vector2 GetPosition();

        float SetRotation(float _rot);

        float GetRotation();

        Vector2 SetScale(Vector2 _scl);

        Vector2 GetScale();

        // local versions of each method

        Vector2 SetLocalPosition(Vector2 _pos);

        Vector2 GetLocalPosition();

        float SetLocalRotation(float _rot);

        float GetLocalRotation();

        Vector2 SetLocalScale(Vector2 _scl);

        Vector2 GetLocalScale();

        void RecalculateLocalValues();

        void RecalculateWorldValues();
    };
}

#endif