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

#include <Core/Resource.h>
#include <Renderer/Shader.h>

namespace DT
{
    class Transform;

    /**
     * @brief DirectionalLight component for casting direction based lighting.
     */
    struct DirectionalLight
    {
        Resource<Shader> shader;          /// @brief Shader used by the directional light.
        float intensity = 1.f;            /// @brief Intensity of the directional light.
        glm::vec3 color = glm::vec3(1.f); /// @brief Color of the directional light.

    private:
        Transform *transform;
        unsigned int lightSpot;     /// @brief Index of this Light in the Shader's light container.
        std::string propertyString; /// @brief Shader property access code stored to avoid repetitive reconstruction.

        friend class DirectionalLightSystem;
    };

    SERIALIZE(DirectionalLight, intensity, color);

    class DirectionalLightSystem : public System
    {
    public:
        void Init(ContextPtr &ctx) override;
        void Tick(ContextPtr &ctx) override;
        void Inspector(ContextPtr &ctx, Entity selectedEntity) override;
        void Serialize(ContextPtr &ctx, Entity entity) override;
        void SceneView(ContextPtr &ctx) override;
        void Destroy(ContextPtr &ctx) override;
    };
}