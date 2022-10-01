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
    /**
     * @brief Returns a debug string from an integer value
     * @param object int reference value
     * @return string for debug purposes
     */
    std::string ToDebug(const int &object);

    /**
     * @brief Returns a debug string from an input string
     * @param object string to parse for debugging
     * @return string for debug purposes
     */
    std::string ToDebug(const std::string &object);

    /**
     * @brief Returns a debug string from a char array
     * @param object char array pointer
     * @return string for debug purposes
     */
    std::string ToDebug(const char *object);

    /**
     * @brief Returns a debug string from a float value
     * @param object float reference value
     * @return string for debug purposes
     */
    std::string ToDebug(const float &object);

    /**
     * @brief Returns a debug string from a GLM quaternion
     * @param object GLM quaternion reference
     * @return string for debug purposes
     */
    std::string ToDebug(const glm::quat &object);

    /**
     * @brief Returns a debug string from a boolean value
     * @param object boolean reference value
     * @return string for debug purposes
     */
    std::string ToDebug(const bool &object);

    /**
     * @brief Returns a debug string from a generic GLM vector
     * @tparam N length of GLM vector
     * @tparam T type of GLM vector values
     * @param object GLM vector reference
     * @return string for debug purposes
     */
    template <int N, typename T>
    std::string ToDebug(const glm::vec<N, T> &object)
    {
        return glm::to_string(object);
    }

    /**
     * @brief Returns a debug string from a generic GLM matrix
     * @tparam N size of square GLM matrix
     * @tparam T type of GLM matrix values
     * @param object GLM matrix reference
     * @return string for debug purposes
     */
    template <int N, typename T>
    std::string ToDebug(const glm::mat<N, N, T> &object)
    {
        return glm::to_string(object);
    }

    /**
     * @brief Debug class for collecting runtime log
     */
    class Debug
    {
    public:
        std::string log;    ///< Debug run log string
    };

    /**
     * @brief Stream operator overload for debug logging
     * @tparam T input type reference
     * @param target Debug class in which append log
     * @param object generic object to log
     * @return reference to updated Debug object
     */
    template <typename T>
    Debug &operator<<(Debug &target, const T &object)
    {
        std::string _object = ToDebug(object);
        target.log += _object;
        std::cout << _object;
        return target;
    }
}