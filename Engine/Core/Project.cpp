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

#include <Core/ResourceManager.h>

#include <Core/Project.h>

namespace DT
{
    void Project::Load()
    {
        *this = json::parse(std::ifstream(directory / "DucktapeProjectSettings.json"));
    }

    void Project::Save()
    {
        std::ofstream output(directory / "DucktapeProjectSettings.json");
        json j = *this;
        output << j;
    }

    void to_json(json &j, const Project &value)
    {
        j["directory"] = value.directory;
        j["config"] = value.config;
        j["resourceManager"] = ResourceManager::Instance();
    }

    void from_json(const json &j, Project &value)
    {
        j.at("directory").get_to(value.directory);
        j.at("config").get_to(value.config);
        j.at("resourceManager").get_to(ResourceManager::Instance());
    }
}