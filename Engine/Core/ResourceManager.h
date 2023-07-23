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

#include <filesystem>

#include <Core/Serialization.h>

namespace DT
{
    /**
     * @brief Resource ID type.
     */
    typedef unsigned int RID;

    /**
     * @brief The ResourceManager class for managing resources.
     */
    class ResourceManager
    {
    public:
        ResourceManager();

        /**
         * @brief Mapping of resource IDs to file paths.
         */
        std::unordered_map<RID, std::filesystem::path> resourceMap;

        /**
         * @brief Retrieves the file path associated with a resource ID.
         *
         * @param rid The resource ID.
         * @return The file path associated with the resource ID.
         */
        std::filesystem::path GetPath(RID rid);

        /**
         * @brief Retrieves the resource ID associated with a file path.
         *
         * @param path The file path.
         * @return The resource ID associated with the file path.
         */
        RID GetRID(const std::filesystem::path &path);

        /**
         * @brief Checks if a resource ID exists.
         *
         * @param rid The resource ID to check.
         * @return True if the resource ID exists, false otherwise.
         */
        bool HasRID(RID rid);

        /**
         * @brief Serializes the resource manager.
         */
        IN_SERIALIZE(ResourceManager, resourceMap);
    };
}