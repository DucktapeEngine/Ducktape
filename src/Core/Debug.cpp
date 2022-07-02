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

#include <Core/Debug.h>

namespace DT
{
    std::string ToDebug(const int &object)
    {
        return std::to_string(object);
    }

    std::string ToDebug(const std::string &object)
    {
        return object;
    }

    std::string ToDebug(const char *object)
    {
        return std::string(object);
    }

    std::string ToDebug(const float &object)
    {
        return std::to_string(object);
    }

    std::string ToDebug(const glm::quat &object)
    {
        return glm::to_string(object);
    }
}