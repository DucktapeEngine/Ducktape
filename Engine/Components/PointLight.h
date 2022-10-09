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
#include <Renderer/Shader.h>
#include <Components/Transform.h>
#include <Core/Engine.h>

namespace DT
{
    /**
     * @brief PointLight class for managing point light.
     * Extends Component class
     */
    class PointLight : public Component
    {
    public:
        Shader *shader = nullptr;             ///< @brief Pointer to the Shader object.
        Transform *transform;                 ///< @brief Pointer to the Transform object.
        unsigned int lightSpot;               ///< @brief used for instantiated point light's index
        std::string propertyString;           ///< @brief property string of the point light

        float intensity = 1.f;                ///< @brief Intensity of the point light.
        glm::vec3 color = glm::vec3(1.f);     ///< @brief Color of the point light.

        /**
         * @brief initiate the point light inside the engine
         */
        void Init() override;

        /**
         * @brief function for point light tick/update inside engine
         */
        void Tick() override;

        /**
         * @brief function for ImGui parameters input widgets
         */
        void Inspector() override;

        /**
         * @brief function for handling point light in a scene view
         * @param selected boolean representing if current entity is selected
         */
        void SceneView(bool selected) override;

        /**
         * @brief function for point light destruction
         */
        void Destroy() override;

        static void System(Scene *scene);
    };
}