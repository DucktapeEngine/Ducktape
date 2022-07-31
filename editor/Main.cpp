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

#include <Ducktape.h>

#include <Core/Application.h>
#include <Core/Editor.h>
using namespace DT;

class PlayerController : public Component
{
public:
    float yaw = 0.f, pitch = 0.f;

    void Tick()
    {
        // Move
        const float cameraSpeed = 2.5f * Time::deltaTime;

        if (Input::GetKey(KEY_W))
            Camera::transform.position += cameraSpeed * Camera::transform.Forward();
        if (Input::GetKey(KEY_S))
            Camera::transform.position -= cameraSpeed * Camera::transform.Forward();
        if (Input::GetKey(KEY_A))
            Camera::transform.position += cameraSpeed * Camera::transform.Right();
        if (Input::GetKey(KEY_D))
            Camera::transform.position -= cameraSpeed * Camera::transform.Right();

        // Look
        float sensitivity = 25.f * Time::deltaTime;

        yaw += -Input::mouseDelta.x * sensitivity;
        pitch += Input::mouseDelta.y * sensitivity;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        Camera::transform.rotation = glm::quat({pitch * DEG2RAD, yaw * DEG2RAD, 0.0f});
    }
};

int main()
{
    try
    {
        Configuration::windowSize = {800, 600};
        Configuration::windowTitle = "DucktapeTest";
        Configuration::hideWindow = true;

        Scene mainScene;

        Entity player = mainScene.CreateEntity();
        player.AddComponent<Tag>().name = "Player";
        player.AddComponent<Transform>();
        player.AddComponent<PlayerController>();

        Application::Init();
        Configuration::shareContextWith = Application::window;

        Editor::Init();

        Engine::Init(mainScene);

        while (!glfwWindowShouldClose(Application::window) && Engine::IsOpen())
        {
            Engine::StartFrame();

            glfwMakeContextCurrent(Application::window);

            Application::PollEvents();
            Application::Clear(0.f, 0.f, 0.f, 1.f);
            Editor::NewFrame();

            Editor::Render();

            Editor::EndFrame();
            Application::Display();

            Engine::EndFrame();
        }

        Application::Terminate();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cin.get();
    }
}