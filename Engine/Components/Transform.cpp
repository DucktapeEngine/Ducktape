/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#include <Components/Transform.h>

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
        return rotation * glm::vec3(0.f, 0.f, 1.f);
    }

    glm::vec3 Transform::Up()
    {
        return rotation * glm::vec3(0.f, 1.f, 0.f);
    }

    void Transform::Inspector()
    {
        SCOMPONENT("Transform");

        SPROPERTY("position", &translation);

        glm::vec3 eulerAngles = GetEulerRotation();
        SPROPERTY("rotation", &eulerAngles);
        SetEulerRotation(eulerAngles);

        SPROPERTY("scale", &scale);
    }

    glm::vec3 Transform::GetEulerRotation()
    {
        return glm::degrees(glm::eulerAngles(rotation));
    }

    void Transform::SetEulerRotation(glm::vec3 eulerRotation)
    {
        rotation = glm::radians(eulerRotation);
    }

    void Transform::System(Scene *scene)
    {
        scene->Call<Transform>();
    }
}