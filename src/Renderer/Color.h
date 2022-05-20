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

#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <Core/Macro.h>

namespace Ducktape
{
    class Color
    {
    public:
        static const Color ALICE_BLUE;
        static const Color ANTIQUE_WHITE;
        static const Color AQUA;
        static const Color AQUAMARINE;
        static const Color AZURE;
        static const Color BEIGE;
        static const Color BISQUE;
        static const Color BLACK;
        static const Color BLANCHED_ALMOND;
        static const Color BLUE;
        static const Color BLUE_VIOLET;
        static const Color BROWN;
        static const Color BURLY_WOOD;
        static const Color CADET_BLUE;
        static const Color CHARTREUSE;
        static const Color CHOCOLATE;
        static const Color CORAL;
        static const Color CORNFLOWER_BLUE;
        static const Color CORNSILK;
        static const Color CRIMSON;
        static const Color CYAN;
        static const Color DARK_BLUE;
        static const Color DARK_CYAN;
        static const Color DARK_GOLDEN_ROD;
        static const Color DARK_GRAY;
        static const Color DARK_GREEN;
        static const Color DARK_GREY;
        static const Color DARK_KHAKI;
        static const Color DARK_MAGENTA;
        static const Color DARK_OLIVE_GREEN;
        static const Color DARK_ORANGE;
        static const Color DARK_ORCHID;
        static const Color DARK_RED;
        static const Color DARK_SALMON;
        static const Color DARK_SEA_GREEN;
        static const Color DARK_SLATE_BLUE;
        static const Color DARK_SLATE_GRAY;
        static const Color DARK_SLATE_GREY;
        static const Color DARK_TURQUOISE;
        static const Color DARK_VIOLET;
        static const Color DEEP_PINK;
        static const Color DEEP_SKY_BLUE;
        static const Color DIM_GRAY;
        static const Color DIM_GREY;
        static const Color DODGER_BLUE;
        static const Color FIRE_BRICK;
        static const Color FLORAL_WHITE;
        static const Color FOREST_GREEN;
        static const Color FUCHSIA;
        static const Color GAINSBORO;
        static const Color GHOST_WHITE;
        static const Color GOLD;
        static const Color GOLDEN_ROD;
        static const Color GRAY;
        static const Color GREEN;
        static const Color GREEN_YELLOW;
        static const Color GREY;
        static const Color HONEYDEW;
        static const Color HOT_PINK;
        static const Color INDIAN_RED;
        static const Color INDIGO;
        static const Color IVORY;
        static const Color KHAKI;
        static const Color LAVENDER;
        static const Color LAVENDER_BLUSH;
        static const Color LAWN_GREEN;
        static const Color LEMON_CHIFFON;
        static const Color LIGHT_BLUE;
        static const Color LIGHT_CORAL;
        static const Color LIGHT_CYAN;
        static const Color LIGHT_GOLDEN_ROD_YELLOW;
        static const Color LIGHT_GRAY;
        static const Color LIGHT_GREEN;
        static const Color LIGHT_GREY;
        static const Color LIGHT_PINK;
        static const Color LIGHT_SALMON;
        static const Color LIGHT_SEA_GREEN;
        static const Color LIGHT_SKY_BLUE;
        static const Color LIGHT_SLATE_GRAY;
        static const Color LIGHT_SLATE_GREY;
        static const Color LIGHT_STEEL_BLUE;
        static const Color LIGHT_YELLOW;
        static const Color LIME;
        static const Color LIME_GREEN;
        static const Color LINEN;
        static const Color MAGENTA;
        static const Color MAROON;
        static const Color MEDIUM_AQUAMARINE;
        static const Color MEDIUM_BLUE;
        static const Color MEDIUM_ORCHID;
        static const Color MEDIUM_PURPLE;
        static const Color MEDIUM_SEA_GREEN;
        static const Color MEDIUM_SLATE_BLUE;
        static const Color MEDIUM_SPRING_GREEN;
        static const Color MEDIUM_TURQUOISE;
        static const Color MEDIUM_VIOLET_RED;
        static const Color MIDNIGHT_BLUE;
        static const Color Mfloat_CREAM;
        static const Color MISTY_ROSE;
        static const Color MOCCASIN;
        static const Color NAVAJO_WHITE;
        static const Color NAVY;
        static const Color OLD_LACE;
        static const Color OLIVE;
        static const Color OLIVE_DRAB;
        static const Color ORANGE;
        static const Color ORANGE_RED;
        static const Color ORCHID;
        static const Color PALE_GOLDEN_ROD;
        static const Color PALE_GREEN;
        static const Color PALE_TURQUOISE;
        static const Color PALE_VIOLET_RED;
        static const Color PAPAYA_WHIP;
        static const Color PEACH_PUFF;
        static const Color PERU;
        static const Color PINK;
        static const Color PLUM;
        static const Color POWDER_BLUE;
        static const Color PURPLE;
        static const Color RED;
        static const Color ROSY_BROWN;
        static const Color ROYAL_BLUE;
        static const Color SADDLE_BROWN;
        static const Color SALMON;
        static const Color SANDY_BROWN;
        static const Color SEA_GREEN;
        static const Color SEA_SHELL;
        static const Color SIENNA;
        static const Color SILVER;
        static const Color SKY_BLUE;
        static const Color SLATE_BLUE;
        static const Color SLATE_GRAY;
        static const Color SLATE_GREY;
        static const Color SNOW;
        static const Color SPRING_GREEN;
        static const Color STEEL_BLUE;
        static const Color TAN;
        static const Color TEAL;
        static const Color THISTLE;
        static const Color TOMATO;
        static const Color TURQUOISE;
        static const Color VIOLET;
        static const Color WHEAT;
        static const Color WHITE;
        static const Color WHITE_SMOKE;
        static const Color YELLOW;
        static const Color YELLOW_GREEN;

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
    };
}