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

#include <Core/ResourceManager.h>
#include <Core/Macro.h>

namespace DT
{
    template <typename T>
    class Resource
    {
    private:
        HAS_METHOD_DECL(LoadResource);
        HAS_METHOD_DECL(SaveResource);

    public:
        RID rid;

        T *Load(RID loadRid)
        {
            rid = loadRid;
            data = nullptr;
            return Data();
        }

        T *Data()
        {
            try
            {
                if constexpr (HasLoadResource<T>::value)
                    if (data == nullptr)
                        data = T::LoadResource(rid);
            }
            catch (json::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
            return data;
        }

        void Save()
        {
            if constexpr (HasSaveResource<T>::value)
                T::SaveResource(rid);
        }

        operator T *()
        {
            return data;
        }

        void operator=(const RID &newRID)
        {
            rid = newRID;
        }

        IN_SERIALIZE(Resource, rid);

    protected:
        T *data;
    };
}