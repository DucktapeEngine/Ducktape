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

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace DT
{
    // Debug casts
    std::string ToDebug(const int &object);
    std::string ToDebug(const std::string &object);
    std::string ToDebug(const char *object);
    std::string ToDebug(const float &object);
    std::string ToDebug(const glm::quat &object);
    std::string ToDebug(const bool &object);

    template <int N, typename T>
    std::string ToDebug(const glm::vec<N, T> &object)
    {
        return glm::to_string(object);
    }

    template <int N, typename T>
    std::string ToDebug(const glm::mat<N, N, T> &object)
    {
        return glm::to_string(object);
    }

    class Debug
    {
    public:
        std::string log;
    };

    template <typename T>
    Debug &operator<<(Debug &target, const T &object)
    {
        std::string _object = ToDebug(object);
        target.log += _object;
        std::cout << _object;
        return target;
    }
}