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

namespace Ducktape
{
    Engine::Engine()
    {
        FT("Engine::Engine()");

        engine = this;
    }

    void Engine::Run(Scene &scene)
    {
        try
        {
            // Rendering
            window.Init(configuration);
            Editor::Init(window);
            renderer.Init(window);

            // Input
            input.Init(window);

            // Logic
            Scene::activeScene = &scene;
            scene.Init();

            while (!glfwWindowShouldClose(window.window))
            {
                window.Tick();

                renderer.Clear();

                input.Tick(window);

                scene.Tick();

                Editor::Tick();

                renderer.Flush();
            }

            window.Cleanup();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            std::cin.get();
        }

        FT("Engine::Run()");
    }
}