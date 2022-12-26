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

#include <Components/Transform.h>
#include <Scene/System.h>
#include <Core/Serialization.h>
#include <Renderer/Renderer.h>
#include <Core/Debug.h>

namespace DT
{
    /**
     * @brief Camera struct for managing camera.
     */
    struct Camera
    {
        glm::mat4 view;       ///< @brief View matrix.
        glm::mat4 projection; ///< @brief Projection matrix.

        bool isOrtho = false; ///< @brief Whether it is orthographic projection or not.
        float fov = 45.0f;    ///< @brief Field of view.

        Transform *transform; ///< @brief Pointer to Transform class.

        /**
         * @brief Function to convert a 3D world point into 2D point after projection.
         * @param worldPoint 3D vector for which projection has to be done.
         * @param windowSize 2D size of game window (ctx.window.GetWindowSize()).
         * @return 2D projected vector on the screen.
         */
        glm::vec2 WorldToScreenPoint(glm::vec3 worldPoint, glm::vec2 &windowSize);
    };

    SERIALIZE(Camera, isOrtho, fov);

    class CameraSystem : System
    {
    public:
        /**
         * @brief Registers Camera in the rendering engine
         */
        void Init(Scene *scene, const Context &ctx) override;

        /**
         * @brief Serializes Camera properties for Inspector.
         */
        void Inspector(Scene *scene, const Context &ctx) override;

        /**
         * @brief Handles Camera serialization.
         */
        void Serialize(Scene *scene, const Context &ctx) override;
    };
}