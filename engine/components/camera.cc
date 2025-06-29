/*
MIT License

Copyright (c) 2021 - 2025 Aryan Baburajan

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

#include <components/camera.h>

namespace DT
{
    void Camera::Init(Context *ctx)
    {
        transform = scene->Require<Transform>(entity);
        window = ctx->GetService<Window>();
    }

    void Camera::Tick(Context *ctx, const float &dt)
    {
        view = glm::lookAtLH(transform->translation, transform->translation + transform->Forward(), transform->Up());

        glm::vec2 winSize = window->GetWindowSize();
        float aspect = (float)winSize.x / winSize.y;
        if (isOrthographic)
            projection = glm::orthoLH(-aspect, aspect, -1.0f, 1.0f, nearPlane, farPlane);
        else
            projection = glm::perspectiveLH(glm::radians(fieldOfView), winSize.x / winSize.y, nearPlane, farPlane);
    }

    void Camera::InspectorMenu(Context *ctx, const float &dt)
    {
        if (ImGui::CollapsingHeader("Camera"))
        {
            ImGui::ColorEdit4("Background", &backgroundColor.x);
            ImGui::Checkbox("Is Orthographic", &isOrthographic);
            ImGui::DragFloat("Field Of View", &fieldOfView);
            ImGui::DragFloat("Near Plane", &nearPlane);
            ImGui::DragFloat("Far Plane", &farPlane);
        }
    }
}