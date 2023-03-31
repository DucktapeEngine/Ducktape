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

#include <iostream>
#include <fstream>

#include <Core/ResourceManager.h>

namespace DT
{
    ResourceManager &ResourceManager::Instance()
    {
        static ResourceManager instance;
        return instance;
    }

    std::filesystem::path ResourceManager::GetPath(RID rid)
    {
        return Instance().resourceMap[rid];
    }

    RID ResourceManager::GetRID(const std::filesystem::path &path)
    {
        for (auto &resource : Instance().resourceMap)
            if (resource.second == path)
                return resource.first;

        RID rid = 1;
        while (HasRID(rid))
            rid++;

        Instance().resourceMap[rid] = path;
        return rid;
    }

    bool ResourceManager::HasRID(RID rid)
    {
        if (Instance().resourceMap.count(rid))
            return true;
        return false;
    }
}