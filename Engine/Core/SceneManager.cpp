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

#include <Core/SceneManager.h>

namespace DT
{
    void SceneManager::SaveLoop(Component* component)
    {
        serializer.SetMode(SerializeMode::S);
        component->Serialize(serializer);

        data["components"][componentIdx]["id"] = component->GetId();
        data["components"][componentIdx]["entity"] = component->entity.handle;
        data["components"][componentIdx]["properties"] = serializer.GetData();

        componentIdx++;
        serializer.ClearData();
    }

    void SceneManager::Save(Scene *scene, const std::string &savePath)
    {
        std::ofstream output(savePath);
        scene->CallLoop(SaveLoop);
        output << data.dump();
        
        data.clear();
        componentIdx = 0;
    }
}