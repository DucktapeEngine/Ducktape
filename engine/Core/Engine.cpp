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

#include <Core/Engine.h>

namespace DT
{
    void Engine::Init(Scene &scene)
    {

        std::cout << "Ducktape  Copyright (C) 2022  Aryan Baburajan\n"
                     "This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"
                     "This is free software, and you are welcome to redistribute it\n"
                     "under certain conditions; type `show c' for details.\n";

        // Rendering
        Window::Init();
        Renderer::Init();
        Input::Init();

        // Logic
        Scene::activeScene = &scene;
        scene.Init();
    }

    bool Engine::IsOpen()
    {
        return !glfwWindowShouldClose(Window::window);
    }

    void Engine::StartFrame()
    {
        Time::Update();
        Input::Process();

        Window::PollEvents();
        Window::Clear(Color(0.2f, 0.3f, 0.3f, 1.0f));

        Renderer::Render();

        Scene::activeScene->Tick();
    }

    void Engine::EndFrame()
    {
        Window::SwapBuffers();
    }

    void Engine::Run(Scene &scene)
    {
        Init(scene);

        while (IsOpen())
        {
            StartFrame();
            EndFrame();
        }
    }

    void Engine::Terminate()
    {
        Window::Terminate();
        Renderer::Terminate();
    }
}