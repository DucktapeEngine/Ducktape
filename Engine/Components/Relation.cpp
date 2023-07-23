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
#include <Scene/SceneManager.h>
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

    template <typename T>
    void ListenerForwarder(entt::registry &registry, entt::entity entity)
    {
    }

    void RelationSystem::Init(ContextPtr &ctx)
    {
        for (Entity entity : ctx.sceneManager->GetActiveScene().View<Relation>())
        {
            ctx.sceneManager->GetActiveScene().Get<Relation>(entity);
            ctx.sceneManager->GetActiveScene().registry.on_destroy<Relation>().connect<&RelationSystem::OnDestroy>(*this);
        }
    }

    void RelationSystem::Inspector(ContextPtr &ctx, Entity selectedEntity)
    {
        for (Entity entity : ctx.sceneManager->GetActiveScene().View<Relation>())
        {
            if (selectedEntity != entity)
                continue;

            Relation *relation = ctx.sceneManager->GetActiveScene().Get<Relation>(entity);

            if (ImGui::CollapsingHeader("Relation"))
            {
                ImGui::Entity("parent", &relation->parent);
            }
        }
    }

    void RelationSystem::Serialize(ContextPtr &ctx, Entity entity)
    {
        ctx.sceneManager->GetActiveScene().SerializeComponent<Relation>("Relation", entity, ctx.sceneManager->GetActiveScene());
    }

    void RelationSystem::OnDestroy(entt::registry &registry, Entity entity)
    {
        Scene *scene = Scene::GetSceneFromRegistry(registry);
        Relation *relation = scene->Get<Relation>(entity);
        relation->RemoveParent(*scene);
        for (const Entity &child : relation->children)
            relation->RemoveChild(child, *scene);
    }
}