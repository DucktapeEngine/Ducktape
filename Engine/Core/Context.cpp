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

#include <functional>

#include <Core/Context.h>

namespace DT
{
    Context::Context(const std::filesystem::path &projectPath) : 
        pointer(&engine, &window, &renderer, &input, &time, &loopManager, &debug, this, &sceneManager, &game, &resourceManager),
        ctxPath(projectPath),
        resourceManager((FetchContextData(), contextData.at("resourceManager"))),
        window(contextData.at("window"), pointer), 
        renderer(contextData.at("renderer"), pointer), 
        input(pointer), 
        sceneManager(contextData.at("sceneManager"), pointer),
        game(pointer)
    {
        sceneManager.activeScene.Reload(pointer);
        sceneManager.activeScene.data->ctx = &pointer;
        std::cout << "[LOG] Context loaded from " << ctxPath.string() << "\n";
    }

    json &Context::FetchContextData()
    {
        JLOG();
        contextData = json::parse(std::ifstream(ctxPath));
        return contextData;
    }

    void to_json(nlohmann::json &nlohmann_json_j, const Context &nlohmann_json_t)
    {
        nlohmann_json_j["window"] = nlohmann_json_t.window;
        nlohmann_json_j["renderer"] = nlohmann_json_t.renderer;
        nlohmann_json_j["sceneManager"] = nlohmann_json_t.sceneManager;
        nlohmann_json_j["resourceManager"] = nlohmann_json_t.resourceManager;
    }
    
    void from_json(const nlohmann::json &nlohmann_json_j, Context &nlohmann_json_t)
    {
        nlohmann_json_j.at("window").get_to(nlohmann_json_t.window);
        nlohmann_json_j.at("renderer").get_to(nlohmann_json_t.renderer);
        nlohmann_json_j.at("sceneManager").get_to(nlohmann_json_t.sceneManager);
        nlohmann_json_j.at("resourceManager").get_to(nlohmann_json_t.resourceManager);
    }
}