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
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace DT
{
    /**
     * @brief The Debug class for collecting runtime logs and errors.
     */
    class Debug
    {
    public:
        /**
         * @brief The stream for collecting log messages.
         */
        std::stringstream log;

        /**
         * @brief The stream for collecting error messages.
         */
        std::stringstream err;

        /**
         * @brief Get the collected log messages as a string.
         * @return A string containing the log messages.
         */
        inline std::string GetLog()
        {
            return log.str();
        }

        /**
         * @brief Get the collected error messages as a string.
         * @return A string containing the error messages.
         */
        inline std::string GetErr()
        {
            return err.str();
        }
    };
}