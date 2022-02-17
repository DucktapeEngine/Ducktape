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

#ifndef DUCKTAPE_ENGINE_TRANSFORM_H_
#define DUCKTAPE_ENGINE_TRANSFORM_H_

#include <vector>

#include <box2d/box2d.h>

#include <Ducktape/engine/behaviourscript.h>
#include <Ducktape/engine/vector2.h>
#include <Ducktape/physics/rigidbody.h>

namespace DT
{
    /**
     * @brief Component for managing position, rotation, and scale of an entity. This component also allows parent-child system, allowing for a hierarchy of entities where each one depend on their parent.
     */
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
        /**
         * @brief Parent of the current transform.
         */
        Transform *parent = nullptr;

        /**
         * @brief Children of the current transform.
         */
        std::vector<Transform *> children;

        /**
         * @brief Set the position of the transform.
         *
         * @param newPosition New position of the transform.
         */
        void SetPosition(Vector2 newPosition);

        /**
         * @brief Get the position of the transform.
         *
         * @return Vector2 Position of the transform.
         */
        Vector2 SetPosition();

        /**
         * @brief Set the rotation of the transform.
         *
         * @param newRotation New rotation of the transform.
         */
        void SetRotation(float newRotation);

        /**
         * @brief Get the rotation of the transform.
         *
         * @return float Rotation of the transform.
         */
        float GetRotation();

        /**
         * @brief Set the scale of the transform.
         *
         * @param newScale New scale of the transform.
         */
        void SetScale(Vector2 newScale);

        /**
         * @brief Get the scale of the transform.
         *
         * @return Vector2 Scale of the transform.
         */
        Vector2 GetScale();

        /**
         * @brief Set the local position of the transform.
         *
         * @param newLocalPosition New local position of the transform.
         */
        void SetLocalPosition(Vector2 newLocalPosition);

        /**
         * @brief Get the local position of the transform.
         *
         * @return Vector2 Local position of the transform.
         */
        Vector2 GetLocalPosition();

        /**
         * @brief Set the local rotation of the transform.
         *
         * @param newLocalRotation New local rotation of the transform.
         */
        void SetLocalRotation(float newLocalRotation);

        /**
         * @brief Get the local rotation of the transform.
         *
         * @return float Local rotation of the transform.
         */
        float GetLocalRotation();

        /**
         * @brief Set the local scale of the transform.
         *
         * @param newLocalScale New local scale of the transform.
         */
        void SetLocalScale(Vector2 newLocalScale);

        /**
         * @brief Get the local scale of the transform.
         *
         * @return Vector2 Local scale of the transform.
         */
        Vector2 GetLocalScale();

        /**
         * @brief Recalculate the local position, rotation, and scale.
         */
        void RecalculateLocalValues();

        /**
         * @brief Recalculate the world position, rotation, and scale.
         */
        void RecalculateWorldValues();
    };
}

#endif