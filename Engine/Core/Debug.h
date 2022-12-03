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
     * @brief Debug class for collecting runtime log
     */
    class Debug
    {
    public:
        Debug()
        {
            // oldOutBuffer = std::cout.rdbuf(outStream.rdbuf());
            // oldErrBuffer = std::cerr.rdbuf(errStream.rdbuf());
        }

        ~Debug()
        {
            // std::cout.rdbuf(oldOutBuffer);
            // std::cerr.rdbuf(oldErrBuffer);
        }

        inline std::string GetOut()
        {
            return outStream.str();
        }

        inline std::string GetErr()
        {
            return errStream.str();
        }

        inline std::stringstream &Out()
        {
            return outStream;
        }

        inline std::stringstream &Err()
        {
            return errStream;
        }

        inline void ClearOut()
        {
            outStream.str("");
            errStream.clear();
        }

        inline void ClearErr()
        {
            errStream.str("");
            errStream.clear();
        }

        inline void Clear()
        {
            ClearOut();
            ClearErr();
        }

    protected:
        std::stringstream outStream;
        std::stringstream errStream;

        std::streambuf *oldOutBuffer;
        std::streambuf *oldErrBuffer;
    };
}