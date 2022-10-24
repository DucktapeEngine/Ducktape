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

#include <Components/Tag.h>

namespace DT
{
    void TagSystem::Inspector(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<Tag>())
        {
            if (scene.selectedEntity != entity)
                continue;

            Tag &tag = scene.Get<Tag>(entity);

            if (ImGui::CollapsingHeader("Tag"))
            {
                ImGui::InputText("name", &tag.name);
            }
        }
    }

    void TagSystem::Serialize(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<Tag>())
        {
            Tag &tag = scene.Get<Tag>(entity);

            engine.serialization.SerializeComponent("Tag", tag, entity);
        }
    }
}