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

#include <Core/ResourceManager.h>
#include <Core/Serialization.h>
#include <Core/ContextPtr.h>

namespace DT
{
    /**
     * @brief The Resource class template for managing resources.
     *
     * @tparam T The resource type.
     */
    template <typename T>
    class Resource
    {
    public:
        /**
         * @brief The resource ID.
         */
        RID rid;

        /**
         * @brief Pointer to the resource data.
         */
        T *data;

        /**
         * @brief Reloads the resource.
         */
        void Reload(ContextPtr &ctx)
        {
            data = nullptr;
            Load(rid, ctx);
        }

        /**
         * @brief Loads the resource with the specified resource ID.
         *
         * @param loadRid The resource ID to load.
         */
        void Load(RID loadRid, ContextPtr &ctx)
        {
            rid = loadRid;
            try
            {
                data = T::LoadResource(rid, ctx);
            }
            catch (json::exception &e)
            {
                std::cout << "[ERR] " << e.what() << std::endl;
            }
        }

        /**
         * @brief Copies the resource to the specified resource ID.
         *
         * @param copyRid The resource ID to copy to.
         */
        void Copy(RID copyRid)
        {
            T::SaveResource(copyRid);
        }

        /**
         * @brief Saves the resource.
         */
        void Save(ContextPtr &ctx)
        {
            T::SaveResource(rid, ctx);
        }

        /**
         * @brief Unloads the resource.
         */
        void Unload()
        {
            data = nullptr;
            T::UnloadResource(rid);
        }

        /**
         * @brief Conversion operator to T* for accessing the resource data.
         *
         * @return A pointer to the resource data.
         */
        operator T *()
        {
            return data;
        }

        /**
         * @brief Serializes the resource.
         */
        IN_SERIALIZE(Resource, rid);
    };
}