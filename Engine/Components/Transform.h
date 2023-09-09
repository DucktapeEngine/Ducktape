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

#pragma once

#include <functional>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <Scene/System.h>
#include <Core/Serialization.h>

namespace DT
{
    /**
     * @brief Transfsorm struct for model transformation set (translation, rotation, scale).
     */
    struct Transform
    {
        glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);    /// Translation vector
        glm::quat rotation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f); /// Rotation in quaternion form
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);          /// Scale vector

        /**
         * @brief Returns the Translation->Rotation->Scale model matrix.
         * @return GLM 4x4 transform matrix
         */
        glm::mat4 GetModelMatrix();

        /**
         * @brief Updates all Transform members from GLM 4x4 combined transform matrix decomposition.
         * @param model GLM 4x4 combined transform matrix.
         */
        void SetModelMatrix(glm::mat4 model);

        /**
         * @brief Returns right vector of Transform rotated model.
         * @return GLM 3-vector (rotated X axis).
         */
        glm::vec3 Right();

        /**
         * @brief Returns forward vector of Transform rotated model.
         * @return GLM 3-vector (rotated Z axis).
         */
        glm::vec3 Forward();

        /**
         * @brief Returns up vector of Transform rotated model.
         * @return GLM 3-vector (rotated Y axis).
         */
        glm::vec3 Up();

        /**
         * @brief Returns the euler rotation of the transform.
         * @return GLM 3-vector Euler angles formed from the quaternion rotation.
         */
        glm::vec3 GetEulerRotation();

        /**
         * @brief Sets the quaternion rotation based on euler angles.
         * @param eulerRotation GLM 3-vector Rotation to set in eulers.
         */
        void SetEulerRotation(glm::vec3 eulerRotation);
    };

    SERIALIZE(Transform, translation, rotation, scale);

    class Scene;

    class TransformSystem : public System
    {
    public:
        void Inspector(ContextPtr &ctx, Entity selectedEntity) override;
        void Serialize(ContextPtr &ctx, Entity entity) override;
        void PopupContext(const char *label, std::function<void()> func);
    };
}