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

#include <string>
#include <iostream>
#include <functional>

#include <entt/entt.hpp>

#include <Scene/Scene.h>
#include <Core/Window.h>
#include <Renderer/Renderer.h>
#include <Core/Time.h>
#include <Input/Input.h>
#include <Core/LoopManager.h>
#include <Core/Debug.h>
#include <Core/UserPointer.h>
#include <Core/Serialization.h>

namespace DT
{
    class Engine
    {
    public:
        Configuration config;    ///< @brief The engine configuration.
        Window window;           ///< @brief The application window.
        Renderer renderer;       ///< @brief The application renderer.
        Input input;             ///< @brief .
        Time time;               ///< @brief The time object to track time fields.
        LoopManager loopManager; ///< @brief The loop manager.
        Debug debug;             ///< @brief Debugger to output debug messages.
        Scene *activeScene;      ///< @brief The current scene the application is using.
        UserPointer userPointer; ///< @brief Points to multiple systems stored as a user pointer in GLFW.
        Serialization serialization;

        Engine(Configuration configuration);

        void Init(Scene &scene);
        bool IsOpen();
        void StartFrame();
        void EndFrame();
        void Run(Scene &scene);
    };
}