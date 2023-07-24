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

#include <Scene/Scene.h>
#include <fstream>

namespace DT
{
    Scene::Scene(RID rid, ContextPtr &ctx)
    {
        scenes.insert(this);
        from_json(json::parse(std::ifstream(ctx.resourceManager->GetPath(rid))), *this);
    }

    Scene::~Scene()
    {
        scenes.erase(scenes.find(this));
        registry.clear();
    }

    Scene *Scene::GetSceneFromRegistry(entt::registry &registry)
    {
        for (Scene *scene : scenes)
            if (&scene->registry == &registry)
                return scene;
        return nullptr;
    }

    Entity Scene::CreateEntity()
    {
        return registry.create();
    }

    void Scene::DestroyEntity(Entity entity)
    {
        registry.destroy(entity);
    }

    void Scene::Assign(Entity entity, const std::string &name, ContextPtr &ctx)
    {
        RegisterFunc registerFunc = ctx.game->gameModule.GetSymbolAddress<RegisterFunc>("Register" + name);

        if (!registerFunc)
        {
            std::cout << "[ERR] Failed to get REGISTER(" << name << ") function from Game Module.\n";
            return;
        }

        (*registerFunc)(entity, this, RegisterAction::Assign);
    }

    void Scene::Remove(Entity entity, const std::string &name, ContextPtr &ctx)
    {
        RegisterFunc registerFunc = ctx.game->gameModule.GetSymbolAddress<RegisterFunc>("Register" + name);

        if (!registerFunc)
        {
            std::cout << "[ERR] Failed to get REGISTER(" << name << ") function from Game Module.\n";
            return;
        }

        (*registerFunc)(entity, this, RegisterAction::Remove);
    }

    Scene *Scene::LoadResource(RID rid, ContextPtr &ctx)
    {
        if (factoryData.count(rid))
            return factoryData[rid];

        factoryData[rid] = new Scene(rid, ctx);

        return factoryData[rid];
    }

    void Scene::UnLoadResource(RID rid)
    {
        delete factoryData[rid];
        factoryData.erase(rid);
    }

    void to_json(json &json, Scene &scene)
    {
        scene.isSerializing = true;

        for (System *system : scene.systems)
            scene.registry.each([&](const Entity entity)
                                { system->Serialize(*scene.ctx, entity); });

        json = scene.serializedData;
    }

    void from_json(const json &j, Scene &scene)
    {
    }
}