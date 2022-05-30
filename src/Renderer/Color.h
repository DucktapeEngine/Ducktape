/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty ofT
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#pragma once

#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

#include <Core/Macro.h>

namespace DT
{
    class Color
    {
    public:
        float r = 0, g = 0, b = 0, a = 1.0f;

        Color(float r, float g, float b);

        Color(float r, float g, float b, float a);

        /**
         * @brief Lerp between two colors
         *
         * @param initialColor
         * @param targetColor
         * @param delta
         * @return Color The lerped color between the two
         */
        static Color Lerp(const Color initialColor, const Color targetColor, float delta);

        operator glm::vec4() const
        {
            return glm::vec4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
        }

        operator sf::Color() const
        {
            return sf::Color(r, g, b, a);
        }
    };
}