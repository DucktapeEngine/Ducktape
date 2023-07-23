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

#include <Scene/Scene.h>
#include <Core/Window.h>
#include <Renderer/Renderer.h>
#include <Core/Time.h>
#include <Input/Input.h>
#include <Core/LoopManager.h>
#include <Core/Resource.h>
#include <Core/ContextPtr.h>
#include <Scene/SceneManager.h>

namespace DT
{
    /**
     * @brief The Engine class responsible for initializing and running the game engine.
     */
    class Engine
    {
    public:
        /**
         * @brief Destructor for the Engine class.
         */
        ~Engine();

        /**
         * @brief Initialize the game engine with the specified context.
         *
         * @param ctx The context pointer containing various engine components.
         */
        void Init(ContextPtr &ctx);

        /**
         * @brief Check if the game engine is currently running.
         *
         * @param ctx The context pointer containing various engine components.
         * @return True if the engine is running, false otherwise.
         */
        bool IsRunning(ContextPtr &ctx);

        /**
         * @brief Start a new frame in the game engine.
         *
         * @param ctx The context pointer containing various engine components.
         */
        void StartFrame(ContextPtr &ctx);

        /**
         * @brief End the current frame in the game engine.
         *
         * @param window The window object used for rendering.
         */
        void EndFrame(Window &window);

        /**
         * @brief Poll and process events from the game window.
         *
         * @param window The window object to poll events from.
         */
        void PollEvents(Window &window);
    };

}