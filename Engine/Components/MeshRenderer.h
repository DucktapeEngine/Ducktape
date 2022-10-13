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
#include <Renderer/Mesh.h>
#include <Core/Engine.h>
#include <Core/Entity.h>
#include <Renderer/Material.h>
#include <Components/Transform.h>

namespace DT
{
    /**
     * @brief MeshRenderer class for mesh handling with a collection of shader, model transformation and material.
     * Extends Component class
     */
    class MeshRenderer : public Component
    {
    public:
        Mesh mesh;                          ///< @brief Mesh data and buffers for runtime drawing
        Shader *shader = nullptr;           ///< @brief Pointer to shader for model drawing
        Transform *transform;               ///< @brief Pointer to model transform
        Material material;                  ///< @brief Pointer to material for shading properties

        /**
         * @brief Initializes entity model transform, shader and mesh buffers
         */
        void Init() override;

        /**
         * @brief Sets shader, transform, material properties and mesh buffers in order to draw current mesh
         */
        void Tick() override;

        /**
         * @brief Adds value input for material shininess and color into ImGui interface
         */
        void Inspector() override;

        /**
         * @brief Draws current mesh for current scene
         * @param selected boolean representing if current entity is selected
         */
        void SceneView(bool selected) override;

        HANDLER(MeshRenderer);
    };

    void Serialize(Serializer &serializer, MeshRenderer &object);
}