/*
MIT License

Copyright (c) 2021 - 2023 Aryan Baburajan

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

#pragma once

#include <Renderer/BaseCamera.h>

namespace DT
{
    class EditorCamera : public BaseCamera
    {
    public:
        Transform transform;

        using BaseCamera::BaseCamera;

        EditorCamera(Context *ctx) : BaseCamera(ctx), transform(ctx) {}

        void Recalculate(Window *window)
        {
            PROFILE();

            view = glm::lookAtLH(transform.translation, transform.translation + transform.Forward(), transform.Up());

            glm::vec2 winSize = window->GetWindowSize();
            float aspect = (float)winSize.x / winSize.y;
            if (isOrthographic)
                projection = glm::orthoLH(-aspect, aspect, -1.0f, 1.0f, nearPlane, farPlane);
            else
                projection = glm::perspectiveLH(glm::radians(fieldOfView), window->GetWindowSize().x / window->GetWindowSize().y, nearPlane, farPlane);
        }

        glm::vec3 &GetPosition() override
        {
            PROFILE();

            return transform.translation;
        }

        glm::quat &GetRotation() override
        {
            PROFILE();

            return transform.rotation;
        }
    };
}