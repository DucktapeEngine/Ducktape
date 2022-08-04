/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSe->  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#include <Core/EditorModules.h>

namespace DT
{
    void EditorModules::SceneView()
    {
        Engine *e = Engine::activeContext;

        //// Controls
        // Movement
        const float cameraSpeed = 2.5f * e->time.deltaTime;

        if (e->input.GetKey(KEY_W))
            e->camera.transform.position += cameraSpeed * e->camera.transform.Forward();
        if (e->input.GetKey(KEY_S))
            e->camera.transform.position -= cameraSpeed * e->camera.transform.Forward();
        if (e->input.GetKey(KEY_A))
            e->camera.transform.position += cameraSpeed * e->camera.transform.Right();
        if (e->input.GetKey(KEY_D))
            e->camera.transform.position -= cameraSpeed * e->camera.transform.Right();

        // Look
        static float yaw = 0.0f, pitch = 0.0f;
        float sensitivity = 25.f * e->time.deltaTime;

        yaw += -e->input.mouseDelta.x * sensitivity;
        pitch += e->input.mouseDelta.y * sensitivity;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        e->camera.transform.rotation = glm::quat({pitch * DEG2RAD, yaw * DEG2RAD, 0.0f});

        //// Render
        ImGui::Begin("Scene View");

        ImVec2 wsize = ImGui::GetWindowSize();
        ImGui::Image((ImTextureID)(uintptr_t)e->renderer.renderTexture, wsize, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
    }
}