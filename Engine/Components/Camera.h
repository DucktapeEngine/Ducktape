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

#include <ECS/Component.h>
#include <Components/Transform.h>
#include <ECS/SceneManager.h>
#include <Core/Window.h>
#include <Core/InputManager.h>
#include <Renderer/BaseCamera.h>

namespace DT
{
    class Camera : public Component, public BaseCamera
    {
    public:
        Camera(Context *ctx) : BaseCamera(ctx)
        {
            activeCamera = std::shared_ptr<Camera>(this);
        }

        void Init(Context *ctx) override;
        void Tick(Context *ctx, const float &dt) override;
        void InspectorMenu(Context *ctx, const float &dt) override;

        glm::vec3 &GetPosition() override
        {
            PROFILE();

            return transform->translation;
        }

        glm::quat &GetRotation() override
        {
            PROFILE();

            return transform->rotation;
        }

        static std::shared_ptr<Camera> GetActiveCamera()
        {
            return activeCamera;
        }

    private:
        std::shared_ptr<Transform> transform;
        static inline std::shared_ptr<Camera> activeCamera;
        Window *window;
    };
}