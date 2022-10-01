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

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

#include <Core/Window.h>
#include <Core/Entity.h>

namespace DT
{
    class Engine;

    /**
     * @brief Base class that all Components inherit from.
     */
    class Component
    {
    public:
        /**
         * @brief Pointer to the active instance of Engine.
         */
        Engine *engine = nullptr;

        /**
         * @brief Entity that this Component belongs to.
         */
        Entity entity;

        /**
         * @brief Virtual function for Component initialization inside Engine
         */
        virtual void Init() {}

        /**
         * @brief Virtual function for Component tick/update inside Engine
         */
        virtual void Tick() {}

        /**
         * @brief Virtual function for handling Component in a scene view
         * @param selected boolean representing if current entity is selected
         */
        virtual void SceneView(bool selected) {}

        /**
         * @brief Virtual function for Component destruction
         */
        virtual void Destroy() {}

        /**
         * @brief Virtual function for ImGui parameters input widgets
         */
        virtual void Inspector() {}
    };
}