/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSengine.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#include <Ducktape.h>
using namespace DT;

struct PlayerController
{
    float yaw = 0.f, pitch = 0.f;
    float speed = 2.5f;
    float sensitivity = 25.f;

    void Inspector(Entity entity, Scene *scene, const Context &ctx)
    {
        if (entity != scene->selectedEntity)
            return;

        if (ImGui::CollapsingHeader("Player Controller"))
        {
            ImGui::DragFloat("speed", &speed);
            ImGui::DragFloat("sensitivity", &sensitivity);
        }
    }
};

DT_EXPORT void RegisterRuntime(Scene &scene)
{
    scene.Register<GenericSystem<PlayerController>>();
}

REGISTER(PlayerController);