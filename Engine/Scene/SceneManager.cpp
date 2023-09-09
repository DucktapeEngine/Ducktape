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
#include <fstream>
#include <sstream>

namespace DT
{
    SceneManager::SceneManager(const json &data, ContextPtr &ctx) : activeScene(data["activeScene"]) {}

    SceneManager::~SceneManager()
    {
        for (System *system : systems)
            delete system;
    }

    void SceneManager::Save(std::filesystem::path savePath, Scene &scene, ContextPtr &ctx)
    {
        std::ofstream output(savePath);
        json j;
        // to_json(j, scene);
        output << j.dump();

        std::cout << "[LOG] Saved scene at " << savePath.string() << "\n";
    }

    void SceneManager::Load(std::filesystem::path loadPath, Scene &scene, ContextPtr &ctx)
    {
        std::ifstream input(loadPath);
        JLOG();
        // from_json(json::parse(input), *activeScene.data);

        std::cout << "[LOG] Loaded scene at " << loadPath.string() << "\n";
    }
}