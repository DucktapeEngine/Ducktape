/*
MIT License

Copyright (c) 2022 Ducktape

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <Ducktape/engine/color.h>
using namespace DT;

Color::Color(int _red, int _blue, int _green)
{
	red = _red;
	blue = _blue;
	green = _green;
	alpha = 255;
}

Color::Color(int _red, int _blue, int _green, int _alpha)
{
	red = _red;
	blue = _blue;
	green = _green;
	alpha = _alpha;
}

sf::Color Color::ToSFMLColor()
{
	return sf::Color(red, blue, green, alpha);
}

const Color Color::ALICE_BLUE = Color(240, 248, 255);
const Color Color::ANTIQUE_WHITE = Color(250, 235, 215);
const Color Color::AQUA = Color(0, 255, 255);
const Color Color::AQUAMARINE = Color(127, 255, 212);
const Color Color::AZURE = Color(240, 255, 255);
const Color Color::BEIGE = Color(245, 245, 220);
const Color Color::BISQUE = Color(255, 228, 196);
const Color Color::BLACK = Color(0, 0, 0);
const Color Color::BLANCHED_ALMOND = Color(255, 235, 205);
const Color Color::BLUE = Color(0, 0, 255);
const Color Color::BLUE_VIOLET = Color(138, 43, 226);
const Color Color::BROWN = Color(165, 42, 42);
const Color Color::BURLY_WOOD = Color(222, 184, 135);
const Color Color::CADET_BLUE = Color(95, 158, 160);
const Color Color::CHARTREUSE = Color(127, 255, 0);
const Color Color::CHOCOLATE = Color(210, 105, 30);
const Color Color::CORAL = Color(255, 127, 80);
const Color Color::CORNFLOWER_BLUE = Color(100, 149, 237);
const Color Color::CORNSILK = Color(255, 248, 220);
const Color Color::CRIMSON = Color(220, 20, 60);
const Color Color::CYAN = Color(0, 255, 255);
const Color Color::DARK_BLUE = Color(0, 0, 139);
const Color Color::DARK_CYAN = Color(0, 139, 139);
const Color Color::DARK_GOLDEN_ROD = Color(184, 134, 11);
const Color Color::DARK_GRAY = Color(169, 169, 169);
const Color Color::DARK_GREEN = Color(0, 100, 0);
const Color Color::DARK_GREY = Color::DARK_GRAY;
const Color Color::DARK_KHAKI = Color(189, 183, 107);
const Color Color::DARK_MAGENTA = Color(139, 0, 139);
const Color Color::DARK_OLIVE_GREEN = Color(85, 107, 47);
const Color Color::DARK_ORANGE = Color(255, 140, 0);
const Color Color::DARK_ORCHID = Color(153, 50, 204);
const Color Color::DARK_RED = Color(139, 0, 0);
const Color Color::DARK_SALMON = Color(233, 150, 122);
const Color Color::DARK_SEA_GREEN = Color(143, 188, 143);
const Color Color::DARK_SLATE_BLUE = Color(72, 61, 139);
const Color Color::DARK_SLATE_GRAY = Color(47, 79, 79);
const Color Color::DARK_SLATE_GREY = Color::DARK_SLATE_GRAY;
const Color Color::DARK_TURQUOISE = Color(0, 206, 209);
const Color Color::DARK_VIOLET = Color(148, 0, 211);
const Color Color::DEEP_PINK = Color(255, 20, 147);
const Color Color::DEEP_SKY_BLUE = Color(0, 191, 255);
const Color Color::DIM_GRAY = Color(105, 105, 105);
const Color Color::DIM_GREY = Color::DIM_GRAY;
const Color Color::DODGER_BLUE = Color(30, 144, 255);
const Color Color::FIRE_BRICK = Color(178, 34, 34);
const Color Color::FLORAL_WHITE = Color(255, 250, 240);
const Color Color::FOREST_GREEN = Color(34, 139, 34);
const Color Color::FUCHSIA = Color(255, 0, 255);
const Color Color::GAINSBORO = Color(220, 220, 220);
const Color Color::GHOST_WHITE = Color(248, 248, 255);
const Color Color::GOLD = Color(255, 215, 0);
const Color Color::GOLDEN_ROD = Color(218, 165, 32);
const Color Color::GRAY = Color(128, 128, 128);
const Color Color::GREEN = Color(0, 128, 0);
const Color Color::GREEN_YELLOW = Color(173, 255, 47);
const Color Color::GREY = Color::GRAY;
const Color Color::HONEYDEW = Color(240, 255, 240);
const Color Color::HOT_PINK = Color(255, 105, 180);
const Color Color::INDIAN_RED = Color(205, 92, 92);
const Color Color::INDIGO = Color(75, 0, 130);
const Color Color::IVORY = Color(255, 255, 240);
const Color Color::KHAKI = Color(240, 230, 140);
const Color Color::LAVENDER = Color(230, 230, 250);
const Color Color::LAVENDER_BLUSH = Color(255, 240, 245);
const Color Color::LAWN_GREEN = Color(124, 252, 0);
const Color Color::LEMON_CHIFFON = Color(255, 250, 205);
const Color Color::LIGHT_BLUE = Color(173, 216, 230);
const Color Color::LIGHT_CORAL = Color(240, 128, 128);
const Color Color::LIGHT_CYAN = Color(224, 255, 255);
const Color Color::LIGHT_GOLDEN_ROD_YELLOW = Color(250, 250, 210);
const Color Color::LIGHT_GRAY = Color(211, 211, 211);
const Color Color::LIGHT_GREEN = Color(144, 238, 144);
const Color Color::LIGHT_GREY = Color::LIGHT_GRAY;
const Color Color::LIGHT_PINK = Color(255, 182, 193);
const Color Color::LIGHT_SALMON = Color(255, 160, 122);
const Color Color::LIGHT_SEA_GREEN = Color(32, 178, 170);
const Color Color::LIGHT_SKY_BLUE = Color(135, 206, 250);
const Color Color::LIGHT_SLATE_GRAY = Color(119, 136, 153);
const Color Color::LIGHT_SLATE_GREY = Color::LIGHT_SLATE_GRAY;
const Color Color::LIGHT_STEEL_BLUE = Color(176, 196, 222);
const Color Color::LIGHT_YELLOW = Color(255, 255, 224);
const Color Color::LIME = Color(0, 255, 0);
const Color Color::LIME_GREEN = Color(50, 205, 50);
const Color Color::LINEN = Color(250, 240, 230);
const Color Color::MAGENTA = Color(255, 0, 255);
const Color Color::MAROON = Color(128, 0, 0);
const Color Color::MEDIUM_AQUAMARINE = Color(102, 205, 170);
const Color Color::MEDIUM_BLUE = Color(0, 0, 205);
const Color Color::MEDIUM_ORCHID = Color(186, 85, 211);
const Color Color::MEDIUM_PURPLE = Color(147, 112, 219);
const Color Color::MEDIUM_SEA_GREEN = Color(60, 179, 113);
const Color Color::MEDIUM_SLATE_BLUE = Color(123, 104, 238);
const Color Color::MEDIUM_SPRING_GREEN = Color(0, 250, 154);
const Color Color::MEDIUM_TURQUOISE = Color(72, 209, 204);
const Color Color::MEDIUM_VIOLET_RED = Color(199, 21, 133);
const Color Color::MIDNIGHT_BLUE = Color(25, 25, 112);
const Color Color::MINT_CREAM = Color(245, 255, 250);
const Color Color::MISTY_ROSE = Color(255, 228, 225);
const Color Color::MOCCASIN = Color(255, 228, 181);
const Color Color::NAVAJO_WHITE = Color(255, 222, 173);
const Color Color::NAVY = Color(0, 0, 128);
const Color Color::OLD_LACE = Color(253, 245, 230);
const Color Color::OLIVE = Color(128, 128, 0);
const Color Color::OLIVE_DRAB = Color(107, 142, 35);
const Color Color::ORANGE = Color(255, 165, 0);
const Color Color::ORANGE_RED = Color(255, 69, 0);
const Color Color::ORCHID = Color(218, 112, 214);
const Color Color::PALE_GOLDEN_ROD = Color(238, 232, 170);
const Color Color::PALE_GREEN = Color(152, 251, 152);
const Color Color::PALE_TURQUOISE = Color(175, 238, 238);
const Color Color::PALE_VIOLET_RED = Color(219, 112, 147);
const Color Color::PAPAYA_WHIP = Color(255, 239, 213);
const Color Color::PEACH_PUFF = Color(255, 218, 185);
const Color Color::PERU = Color(205, 133, 63);
const Color Color::PINK = Color(255, 192, 203);
const Color Color::PLUM = Color(221, 160, 221);
const Color Color::POWDER_BLUE = Color(176, 224, 230);
const Color Color::PURPLE = Color(128, 0, 128);
const Color Color::RED = Color(255, 0, 0);
const Color Color::ROSY_BROWN = Color(188, 143, 143);
const Color Color::ROYAL_BLUE = Color(65, 105, 225);
const Color Color::SADDLE_BROWN = Color(139, 69, 19);
const Color Color::SALMON = Color(250, 128, 114);
const Color Color::SANDY_BROWN = Color(244, 164, 96);
const Color Color::SEA_GREEN = Color(46, 139, 87);
const Color Color::SEA_SHELL = Color(255, 245, 238);
const Color Color::SIENNA = Color(160, 82, 45);
const Color Color::SILVER = Color(192, 192, 192);
const Color Color::SKY_BLUE = Color(135, 206, 235);
const Color Color::SLATE_BLUE = Color(106, 90, 205);
const Color Color::SLATE_GRAY = Color(112, 128, 144);
const Color Color::SLATE_GREY = Color::SLATE_GRAY;
const Color Color::SNOW = Color(255, 250, 250);
const Color Color::SPRING_GREEN = Color(0, 255, 127);
const Color Color::STEEL_BLUE = Color(70, 130, 180);
const Color Color::TAN = Color(210, 180, 140);
const Color Color::TEAL = Color(0, 128, 128);
const Color Color::THISTLE = Color(216, 191, 216);
const Color Color::TOMATO = Color(255, 99, 71);
const Color Color::TURQUOISE = Color(64, 224, 208);
const Color Color::VIOLET = Color(238, 130, 238);
const Color Color::WHEAT = Color(245, 222, 179);
const Color Color::WHITE = Color(255, 255, 255);
const Color Color::WHITE_SMOKE = Color(245, 245, 245);
const Color Color::YELLOW = Color(255, 255, 0);
const Color Color::YELLOW_GREEN = Color(154, 205, 50);