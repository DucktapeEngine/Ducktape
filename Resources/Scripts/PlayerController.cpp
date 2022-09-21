/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSengine->  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#include <Ducktape.h>
using namespace DT;

class PlayerController : public Component
{
public:
    float yaw = 0.f, pitch = 0.f;
    float speed = 2.5f;
    float sensitivity = 25.f;

    void Tick()
    {
        // Move
        if (engine->input.GetKey(KEY_W))
            engine->camera.transform.position += speed * engine->time.deltaTime * engine->camera.transform.Forward();
        if (engine->input.GetKey(KEY_S))
            engine->camera.transform.position -= speed * engine->time.deltaTime * engine->camera.transform.Forward();
        if (engine->input.GetKey(KEY_A))
            engine->camera.transform.position += speed * engine->time.deltaTime * engine->camera.transform.Right();
        if (engine->input.GetKey(KEY_D))
            engine->camera.transform.position -= speed * engine->time.deltaTime * engine->camera.transform.Right();

        // Look
        yaw += -engine->input.mouseDelta.x * sensitivity * engine->time.deltaTime;
        pitch += engine->input.mouseDelta.y * sensitivity * engine->time.deltaTime;
        
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        engine->camera.transform.rotation = glm::quat({pitch * DEG2RAD, yaw * DEG2RAD, 0.0f});
    }

    void Inspector()
    {
        if (ImGui::CollapsingHeader("Player Controller"))
        {
            ImGui::InputFloat("speed", &speed);
            ImGui::InputFloat("sensitivity", &sensitivity);
            
            ImGui::InputFloat("yaw", &yaw);
            ImGui::InputFloat("pitch", &pitch);
        }
    }

    static void System(Scene *scene)
    {
        scene->Call<PlayerController>();
    }
};

extern "C" __declspec(dllexport) Component *AssignPlayerController(Entity entity)
{
    return &entity.Assign<PlayerController>();
}