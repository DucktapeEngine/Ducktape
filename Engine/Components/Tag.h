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

#include <Components/Component.h>
#include <Core/Scene.h>
#include <Core/Engine.h>

namespace DT
{
    /**
     * @brief Tag class for assigning tags on Entity objects
     */
    class Tag : public Component
    {
    public:
        std::string name = "Unnamed";       ///< @brief Tag name

        /**
         * @brief Adds value input for tag name into ImGui interface
         */
        void Inspector() override;

        /**
         * @brief Static function for EnTT entity management on Tag objects
         * @param scene Scene object from which call entity management
         */
        static void System(Scene *scene);
    };
}