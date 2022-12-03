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

#include <Renderer/Mesh.h>
#include <Core/ImGui.h>
#include <Scene/Entity.h>
#include <Renderer/Material.h>
#include <Components/Transform.h>
#include <Core/Serialization.h>
#include <Core/Resource.h>

namespace DT
{
    /**
     * @brief MeshRenderer struct for mesh handling with a collection of shader, model transformation and material.
     */
    struct MeshRenderer
    {
        Resource<Mesh> mesh;  ///< @brief Mesh data and buffers for runtime drawing
        Transform *transform; ///< @brief Pointer to model transform

        IN_SERIALIZE(MeshRenderer, mesh);
    };

    class MeshRendererSystem : System
    {
    public:
        /**
         * @brief Initializes entity model transform, shader and mesh buffers.
         */
        void Init(Scene *scene, const Context &ctx) override;

        /**
         * @brief Draws current mesh for current scene->
         */
        void Tick(Scene *scene, const Context &ctx) override;

        /**
         * @brief Handles Scene View rendering.
         */
        void SceneView(Scene *scene, const Context &ctx) override;

        /**
         * @brief Handles MeshRenderer serialization.
         */
        void Serialize(Scene *scene, const Context &ctx) override;

        /**
         * @brief Serializes MeshRenderer properties for Inspector.
         */
        void Inspector(Scene *scene, const Context &ctx) override;
    };
}