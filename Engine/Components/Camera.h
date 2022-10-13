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

#include <Components/Component.h>
#include <Core/Engine.h>
#include <Components/Transform.h>

namespace DT
{
    /**
     * @brief Camera class for managing camera.
     * Extends Component class
     */
    class Camera : public Component
    {
    public:
        glm::mat4 view;               ///< @brief View matrix.
        glm::mat4 projection;         ///< @brief Projection matrix.

        bool isOrtho = false;         ///< @brief Whether it is orthographic projection or not.
        float fov = 45.0f;            ///< @brief Field of view.

        Transform *transform;         ///< @brief pointer to Transform class.
        
        /**
         * @brief function for Camera initialization inside Engine.
         */
        void Init() override;

        /**
         * @brief function for ImGui parameters input widgets.
         */
        void Inspector() override;

        /**
         * @brief function to convert a 3D world point into 2D point after projection.
         * @param worldPoint 3D vector for which projection has to be done.
         * @return 2D projected vector on the screen.
         */
        glm::vec2 WorldToScreenPoint(glm::vec3 worldPoint);

        HANDLER(Camera);
    };

    void Serialize(Serializer &serializer, Camera &object);
}