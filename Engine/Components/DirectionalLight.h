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

#include <Renderer/Shader.h>
#include <Components/Transform.h>
#include <Scene/System.h>
#include <Core/Serialization.h>
#include <Renderer/Renderer.h>

namespace DT
{
    /**
     * @brief DirectionalLight struct for managing directional light.
     */
    struct DirectionalLight
    {
        Shader *shader = nullptr;   ///< @brief Pointer to the Shader object.
        Transform *transform;       ///< @brief Pointer to the Transform object.
        unsigned int lightSpot;     ///< @brief used for instantiated directional light's index
        std::string propertyString; ///< @brief property string of the directional light

        float intensity = 1.f;            ///< @brief Intensity of the directional light.
        glm::vec3 color = glm::vec3(1.f); ///< @brief Color of the directional light.
    };

    SERIALIZE(DirectionalLight, intensity, color);

    class DirectionalLightSystem : System
    {
    public:
        /**
         * @brief Registers Directional Light to rendering engine and shader on Initiation.
         */
        void Init(Scene *scene, const Context &ctx) override;

        /**
         * @brief Updates corresponding Directional Light properties in shader every frame.
         */
        void Tick(Scene *scene, const Context &ctx) override;

        /**
         * @brief Serializes DirectionalLight properties for Inspector.
         */
        void Inspector(Scene *scene, const Context &ctx) override;

        /**
         * @brief Handles DirectionalLight serialization.
         */
        void Serialize(Scene *scene, const Context &ctx) override;

        /**
         * @brief Handles Scene View lighting.
         */
        void SceneView(Scene *scene, const Context &ctx) override;

        /**
         * @brief Unregisters Directional Light from rendering engine and shader on destruction.
         */
        void Destroy(Scene *scene, const Context &ctx) override;
    };
}