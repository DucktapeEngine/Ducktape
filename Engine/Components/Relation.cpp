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

#include <vector>

#include <Scene/Entity.h>
#include <Core/Serialization.h>
#include <Scene/Scene.h>
#include <Core/ImGui.h>
#include <Core/SerializationManager.h>

#include <Components/Relation.h>

namespace DT
{
    void Relation::SetParent(Entity parentEntity, Scene &scene)
    {
        Entity entity = Scene::From(*this, scene);

        Relation &parentRelation = scene.Assign<Relation>(parentEntity);
        Relation &childRelation = scene.Assign<Relation>(entity);

        parentRelation.children.insert(entity);
        parent = parentEntity;
        hasParent = true;
    }

    void Relation::RemoveParent(Scene &scene)
    {
        if (parent == entt::null)
            return;

        Entity entity = Scene::From(*this, scene);

        Relation &parentRelation = scene.Assign<Relation>(parent);
        Relation &childRelation = scene.Assign<Relation>(entity);

        parentRelation.children.erase(entity);
        parent = entt::null;
        hasParent = false;
    }

    void Relation::AddChild(Entity child, Scene &scene)
    {
        Entity entity = Scene::From(*this, scene);

        Relation &parentRelation = scene.Assign<Relation>(entity);
        Relation &childRelation = scene.Assign<Relation>(child);

        children.insert(child);
        childRelation.parent = entity;
        childRelation.hasParent = true;
    }

    void Relation::RemoveChild(Entity child, Scene &scene)
    {
        Entity entity = Scene::From(*this, scene);

        Relation &parentRelation = scene.Assign<Relation>(entity);
        Relation &childRelation = scene.Assign<Relation>(child);

        children.erase(child);
        childRelation.parent = entt::null;
        childRelation.hasParent = false;
    }

    void RelationSystem::Inspector(Scene *scene, const Context &ctx)
    {
        for (Entity entity : scene->View<Relation>())
        {
            if (scene->selectedEntity != entity)
                continue;

            Relation *relation = scene->Get<Relation>(entity);

            if (ImGui::CollapsingHeader("Relation"))
            {
                ImGui::Entity("parent", &relation->parent);
            }
        }
    }

    void RelationSystem::Serialize(Scene *scene, const Context &ctx, Entity entity)
    {
        ctx.serializationManager->SerializeComponent<Relation>("Relation", entity, *scene);
    }
}