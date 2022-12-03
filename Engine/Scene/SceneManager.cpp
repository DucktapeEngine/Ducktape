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

#include <Scene/SceneManager.h>

namespace DT
{
    void SceneManager::Save(std::filesystem::path savePath, Scene &scene, Engine &engine)
    {
        std::ofstream output(savePath);
        engine.serialization.data.clear();
        engine.serialization.isSerializing = true;

        for (System *system : scene.GetSystems())
            system->Serialize(&scene, engine.ctx);

        output << engine.serialization.data.dump(4);
    }

    void SceneManager::Load(std::filesystem::path loadPath, Scene &scene, Engine &engine)
    {
        std::ifstream input(loadPath);
        std::stringstream inputBuffer;
        inputBuffer << input.rdbuf();
        engine.serialization.data = json::parse(inputBuffer.str());

        // Create EC-like Scene Data for easy scene construction
        json sceneData;
        for (json &component : engine.serialization.data["components"])
        {
            json editedComponent = component;
            editedComponent.erase("entity");

            sceneData["entities"][(int)component["entity"]]["components"].push_back(editedComponent);
        }

        scene.sceneRegistry.clear();

        // Create the scene structure
        for (json &entityData : sceneData["entities"])
        {
            Entity entity = scene.CreateEntity();

            for (json &componentData : entityData["components"])
                scene.Assign(entity, componentData["id"]);
        }

        // Deserialize
        engine.serialization.isSerializing = false;

        for (System *system : scene.GetSystems())
            system->Serialize(&scene, engine.ctx);

        for (System *system : scene.GetSystems())
            system->Init(&scene, engine.ctx);

        std::cout << "Loaded scene successfully\n";
    }
}