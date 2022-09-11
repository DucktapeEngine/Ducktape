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

    void Init()
    {
    }

    void Tick()
    {
        // Move
        const float cameraSpeed = 2.5f * engine->time.deltaTime;

        if (engine->input.GetKey(KEY_W))
            engine->camera.transform.position += cameraSpeed * engine->camera.transform.Forward();
        if (engine->input.GetKey(KEY_S))
            engine->camera.transform.position -= cameraSpeed * engine->camera.transform.Forward();
        if (engine->input.GetKey(KEY_A))
            engine->camera.transform.position += cameraSpeed * engine->camera.transform.Right();
        if (engine->input.GetKey(KEY_D))
            engine->camera.transform.position -= cameraSpeed * engine->camera.transform.Right();

        // Look
        float sensitivity = 25.f * engine->time.deltaTime;

        yaw += -engine->input.mouseDelta.x * sensitivity;
        pitch += engine->input.mouseDelta.y * sensitivity;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        engine->camera.transform.rotation = glm::quat({pitch * DEG2RAD, yaw * DEG2RAD, 0.0f});
    }
};

extern "C" __declspec(dllexport) Component *CreateModule()
{
    Component *module = new PlayerController();
    return module;
}