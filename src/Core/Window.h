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

#include <vector>
#include <stdexcept>
#include <iostream>

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Core/Configuration.h>
#include <Core/Macro.h>

namespace DT
{
    namespace Window
    {
        inline sf::RenderWindow window;
        inline sf::View view;

        inline const float PIXEL_PER_UNIT = 10.0f;

        glm::vec2 GetResolution();
        void SetResolution(glm::vec2 resolution);

        void Init();
        void Tick();

        void Clear();
    };
}