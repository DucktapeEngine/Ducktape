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
#include <Renderer/Mesh.h>

namespace DT
{
    class Transform;

    /**
     * @brief MeshRenderer component for rendering mesh.
     */
    struct MeshRenderer
    {
        Resource<Mesh> mesh; /// @brief Resource of the Mesh object to be rendered.

    private:
        Transform *transform;

        friend class MeshRendererSystem;
    };

    SERIALIZE(MeshRenderer, mesh);

    class MeshRendererSystem : public System
    {
    public:
        void Init(ContextPtr &ctx) override;
        void Tick(ContextPtr &ctx) override;
        void SceneView(ContextPtr &ctx) override;
        void Serialize(ContextPtr &ctx, Entity entity) override;
        void Inspector(ContextPtr &ctx, Entity selectedEntity) override;
    };
}