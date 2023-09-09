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

namespace DT
{
    class Transform;

    /**
     * @brief Camera component for handling Camera related properties.
     */
    struct Camera
    {
        glm::mat4 view;       /// @brief View matrix.
        glm::mat4 projection; /// @brief Projection matrix.

        bool isOrtho = false; /// @brief Flag for orthographic projection.
        float fov = 45.0f;    /// @brief Field of view.

        Transform *transform;

        /**
         * @brief Function to convert a 3D world point into a 2D point on the screen after projection.
         * @param worldPoint 3D vector for which projection has to be done.
         * @param windowSize 2D size of game window (ctx.window.GetWindowSize()).
         * @return 2D projected vector on the screen.
         */
        glm::vec2 WorldToScreenPoint(glm::vec3 worldPoint, glm::vec2 &windowSize);

        // TODO: ScreenToWorldPoint();
    };

    SERIALIZE(Camera, isOrtho, fov);

    class CameraSystem : public System
    {
    public:
        void Init(ContextPtr &ctx) override;
        void Inspector(ContextPtr &ctx, Entity selectedEntity) override;
        void Serialize(ContextPtr &ctx, Entity entity) override;
    };
}