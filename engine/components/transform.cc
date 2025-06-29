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

#include <components/transform.h>
#include <utils/math.h>

namespace DT
{
    glm::mat4 Transform::GetModelMatrix()
    {
        glm::mat4 trans = glm::translate(glm::mat4(1.f), translation);
        glm::mat4 rot = glm::toMat4(rotation);
        glm::mat4 scl = glm::scale(glm::mat4(1.f), scale);

        return trans * rot * scl;
    }

    void Transform::SetModelMatrix(glm::mat4 model)
    {
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(model, scale, rotation, translation, skew, perspective);
    }

    glm::vec3 Transform::Right()
    {
        return rotation * glm::vec3(1.f, 0.f, 0.f);
    }

    glm::vec3 Transform::Forward()
    {
        return glm::rotate(rotation, glm::vec3(0.0, 0.0, 1.0));
    }

    glm::vec3 Transform::Up()
    {
        return rotation * glm::vec3(0.f, 1.f, 0.f);
    }

    glm::vec3 Transform::GetEulerRotation()
    {
        return glm::degrees(glm::eulerAngles(rotation));
    }

    void Transform::SetEulerRotation(glm::vec3 eulerRotation)
    {
        rotation = glm::radians(eulerRotation);
    }

    void Transform::LookAt(const glm::vec3 &at)
    {
        rotation = glm::quatLookAtLH(glm::normalize(at - translation), {0.f, 1.f, 0.f});
    }

    void Transform::InspectorMenu(Context *ctx, const float &dt)
    {
        if (ImGui::CollapsingHeader("Transform"))
        {
            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Reset##Transform"))
                {
                    translation = glm::vec3(0);
                    SetEulerRotation(glm::vec3(0));
                    scale = glm::vec3(1);
                }
                ImGui::EndPopup();
            }
            
            ImGui::Vec3("Position", translation);

            glm::vec3 eulerAngles = GetEulerRotation();
            ImGui::Vec3("Rotation", eulerAngles);
            SetEulerRotation(eulerAngles);

            ImGui::Vec3("Scale", scale);
        }
    }
}