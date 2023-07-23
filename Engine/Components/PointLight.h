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
     * @brief PointLight component
     */
    struct PointLight
    {
        Resource<Shader> shader;          /// @brief Shader used by the point light.
        float intensity = 1.f;            /// @brief Intensity of the point light.
        glm::vec3 color = glm::vec3(1.f); /// @brief Color of the point light.

    private:
        Transform *transform;
        unsigned int lightSpot;     /// @brief Index of this Light in the Shader's light container.
        std::string propertyString; /// @brief Shader property access code stored to avoid repetitive reconstruction.

        friend class PointLightSystem;
    };

    SERIALIZE(PointLight, intensity, color);

    class PointLightSystem : public System
    {
    public:
        /**
         * @brief Registers Point Light to rendering engine and shader on Initiation.
         */
        void Init(ContextPtr &ctx) override;

        /**
         * @brief Updates corresponding Point Light properties in shader every frame.
         */
        void Tick(ContextPtr &ctx) override;

        /**
         * @brief Serializes PointLight properties for Inspector.
         */
        void Inspector(ContextPtr &ctx, Entity selectedEntity) override;

        /**
         * @brief Handles PointLight serialization.
         */
        void Serialize(ContextPtr &ctx, Entity entity) override;

        /**
         * @brief Handles Scene View lighting.
         */
        void SceneView(ContextPtr &ctx) override;

        /**
         * @brief Unregisters Point Light from rendering engine and shader on destruction.
         */
        void Destroy(ContextPtr &ctx) override;
    };
}