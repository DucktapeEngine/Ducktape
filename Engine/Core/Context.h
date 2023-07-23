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

#include <Core/Engine.h>
#include <Core/Window.h>
#include <Renderer/Renderer.h>
#include <Core/Time.h>
#include <Input/Input.h>
#include <Core/LoopManager.h>
#include <Core/Debug.h>
#include <Core/Project.h>
#include <Core/ResourceManager.h>
#include <Core/Context.h>
#include <Core/ContextPtr.h>
#include <Scene/SceneManager.h>
#include <Core/Game.h>
#include <Core/Serialization.h>

namespace DT
{
    /**
     * @brief The Context class represents the main context of the application.
     *
     * It contains various components and managers used for managing the application's state and functionality.
     */
    class Context
    {
    public:
        std::filesystem::path ctxPath; /// @brief The path to the project.

        ContextPtr pointer;              /// @brief Pointer to the current context.
        ResourceManager resourceManager; /// @brief The resource manager instance.
        Engine engine;                   /// @brief The engine instance.
        Window window;                   /// @brief The window instance.
        Renderer renderer;               /// @brief The renderer instance.
        Input input;                     /// @brief The input instance.
        Time time;                       /// @brief The time instance.
        LoopManager loopManager;         /// @brief The loop manager instance.
        Debug debug;                     /// @brief The debug instance.
        SceneManager sceneManager;       /// @brief The scene manager instance.
        Game game;                       /// @brief The game instance.

        /**
         * @brief Constructs a new Context object with the specified project path.
         *
         * @param projectPath The path to the project.
         */
        Context(const std::filesystem::path &projectPath) : resourceManager(), ctxPath(projectPath), window((InitializeContextPtr(), pointer)), renderer(pointer), input(pointer), game(pointer), sceneManager(pointer)
        {
            // Load context data from a JSON file
            from_json(json::parse(std::ifstream(ctxPath)), *this);
            std::cout << "[LOG] Context loaded from " << ctxPath.string() << "\n";
        }

        /**
         * @brief Serializes the window and renderer components for serialization.
         */
        friend void to_json(nlohmann::json &nlohmann_json_j, const Context &nlohmann_json_t)
        {
            nlohmann_json_j["window"] = nlohmann_json_t.window;
            nlohmann_json_j["renderer"] = nlohmann_json_t.renderer;
            nlohmann_json_j["sceneManager"] = nlohmann_json_t.sceneManager;
            nlohmann_json_j["resourceManager"] = nlohmann_json_t.resourceManager;
        }
        friend void from_json(const nlohmann::json &nlohmann_json_j, Context &nlohmann_json_t)
        {
            nlohmann_json_j.at("window").get_to(nlohmann_json_t.window);
            nlohmann_json_j.at("renderer").get_to(nlohmann_json_t.renderer);
            nlohmann_json_j.at("sceneManager").get_to(nlohmann_json_t.sceneManager);
            // nlohmann_json_j.at("resourceManager").get_to(nlohmann_json_t.resourceManager);
        }

    private:
        /**
         * @brief Initialize the context (including pointers).
         */
        void InitializeContextPtr();
    };
}