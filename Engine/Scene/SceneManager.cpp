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

#include <Core/Macro.h>
#include <Scene/SceneManager.h>

namespace DT
{
    SceneManager::SceneManager(ContextPtr &ctx)
    {
        activeScene.rid = ctx.resourceManager->GetRID(DUCKTAPE_ROOT_DIR / "Resources" / "Sandbox" / "Assets" / "DucktapeProjectSettings.json");
        activeScene.Reload(ctx);
        activeScene.data->ctx = &ctx;
    }

    // void SceneManager::Save(std::filesystem::path savePath, Scene &scene, Engine &engine)
    // {
    //     std::ofstream output(savePath);
    //     output << json(scene);
    // }

    // void SceneManager::Load(std::filesystem::path loadPath, Scene &scene, Engine &engine)
    // {
    //     std::ifstream input(loadPath);
    //     engine.serializationManager.data = json::parse(input);

    //     scene.registry.each([&](const Entity entity)
    //                         { scene.registry.destroy(entity); });
    //     scene.registry.clear();

    //     engine.serializationManager.isSerializing = false;

    //     int handle = 0;
    //     for (auto it = engine.serializationManager.data["entities"].begin(); it != engine.serializationManager.data["entities"].end(); ++it)
    //     {
    //         Entity entity = entt::null;
    //         if (scene.registry.valid(entt::entity(handle)))
    //         {
    //             entity = entt::entity(handle);
    //         }
    //         else
    //         {
    //             entity = scene.registry.create(entt::entity(handle));
    //         }

    //         for (auto ct = it.value()["components"].begin(); ct != it.value()["components"].end(); ++ct)
    //         {
    //             scene.Assign(entity, ct.key());
    //             for (System *system : scene.systems)
    //                 system->Serialize(&scene, engine.ctx, entity);
    //         }

    //         handle++;
    //     }

    //     for (System *system : scene.systems)
    //         system->Init(&scene, engine.ctx);

    //     std::cout << "Loaded scene successfully\n";
    // }
}