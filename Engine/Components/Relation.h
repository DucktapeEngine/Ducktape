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
    /**
     * @brief Relation component for Parent-Child relationships.
     */
    struct Relation
    {
        bool hasParent = false;              /// @brief Flag indicating whether the current Entity has a parent.
        Entity parent = entt::null;          /// @brief Parent of the current Entity. Equals to `entt::null` when `hasParent` is `false`.
        std::unordered_set<Entity> children; /// @brief List of children owned by current Entity.

        /**
         * @brief Sets the parent of the current Entity.
         *
         * @param parent The Entity to set as the parent.
         * @param scene Reference to the Scene object.
         */
        void SetParent(Entity parent, Scene &scene);

        /**
         * @brief Removes the parent of the current Entity.
         *
         * @param scene Reference to the Scene object.
         */
        void RemoveParent(Scene &scene);

        /**
         * @brief Adds a child to the current Entity.
         *
         * @param child The Entity to add as a child.
         * @param scene Reference to the Scene object.
         */
        void AddChild(Entity child, Scene &scene);

        /**
         * @brief Removes a child from the current Entity.
         *
         * @param child The Entity to remove as a child.
         * @param scene Reference to the Scene object.
         */
        void RemoveChild(Entity child, Scene &scene);
    };

    SERIALIZE(Relation, hasParent, parent, children);

    class RelationSystem : public System
    {
    public:
        void Init(ContextPtr &ctx) override;
        void Inspector(ContextPtr &ctx, Entity selectedEntity) override;
        void Serialize(ContextPtr &ctx, Entity entity) override;
        void OnDestroy(entt::registry &registry, entt::entity entity) override;
    };
}