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

namespace DT
{
    Scene::Scene(Engine *holderEngine, Configuration &config)
    {
        engine = holderEngine;

        if (config.gameModule != "")
            LoadModule(config.gameModule);
    }

    Scene::~Scene()
    {
        gameModule.Free();
    }

    void Scene::LoadModule(std::filesystem::path path)
    {
        gameModule.Load(path);
        if (!gameModule.module)
        {
            std::cout << "Failed to load Module: " << path << std::endl;
            return;
        }

        RegisterRuntimeFunc registerRuntimeFunc = gameModule.GetSymbolAddress<RegisterRuntimeFunc>("RegisterRuntime");
        if (registerRuntimeFunc)
            registerRuntimeFunc(*this);
    }
    
    Scene::SystemPool &Scene::GetSystems()
    {
        return systems;
    }

    Entity Scene::CreateEntity()
    {
        return sceneRegistry.create();
    }

    void Scene::DestroyEntity(Entity entity)
    {
        sceneRegistry.destroy(entity);
    }

    void Scene::Assign(Entity entity, const std::string &name)
    {
        RegisterFunc registerFunc = gameModule.GetSymbolAddress<RegisterFunc>("Register" + name);

        if (!registerFunc)
        {
            std::cout << "Failed to get REGISTER(" << name << ") function from Game Module." << std::endl;
            return;
        }

        (*registerFunc)(entity, *this, RegisterAction::Assign);
    }

    void Scene::Remove(Entity entity, const std::string &name)
    {
        RegisterFunc registerFunc = gameModule.GetSymbolAddress<RegisterFunc>("Register" + name);

        if (!registerFunc)
        {
            std::cout << "Failed to get REGISTER(" << name << ") function from Game Module." << std::endl;
            return;
        }

        (*registerFunc)(entity, *this, RegisterAction::Remove);
    }
}