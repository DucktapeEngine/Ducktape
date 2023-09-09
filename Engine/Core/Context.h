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
#include <Core/ContextPtr.h>
#include <Scene/SceneManager.h>
#include <Core/Game.h>

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
        Game game;                       /// @brief The game instance.
        SceneManager sceneManager;       /// @brief The scene manager instance.

        /**
         * @brief Constructs a new Context object with the specified project path.
         *
         * @param projectPath The path to the project.
         */
        Context(const std::filesystem::path &projectPath);

    private:
        json contextData;

        json &FetchContextData();
    };

    /**
     * @brief Serializes the window and renderer components for serialization.
     */
    void to_json(nlohmann::json &nlohmann_json_j, const Context &nlohmann_json_t);
    void from_json(const nlohmann::json &nlohmann_json_j, Context &nlohmann_json_t);
}