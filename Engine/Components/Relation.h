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
    struct Relation
    {
        bool hasParent = false; // Serialization of entt::null has issues, using this as flag instead for now
        Entity parent = entt::null;
        std::unordered_set<Entity> children;

        void SetParent(Entity parent, Scene &scene);
        void RemoveParent(Scene &scene);
        void AddChild(Entity child, Scene &scene);
        void RemoveChild(Entity child, Scene &scene);
    };

    SERIALIZE(Relation, hasParent, parent, children);

    class RelationSystem : System
    {
    public:
        void Init(Scene *scene, const Context &ctx) override;

        /**
         * @brief Serializes Camera properties for Inspector.
         */
        void Inspector(Scene *scene, const Context &ctx) override;

        /**
         * @brief Handles Camera serialization.
         */
        void Serialize(Scene *scene, const Context &ctx, Entity entity) override;

        void OnDestroy(entt::registry &registry, entt::entity entity);
    };
}