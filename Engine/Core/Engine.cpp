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

#include <string>
#include <iostream>

#include <Core/Engine.h>

namespace DT
{
    Engine::~Engine()
    {
        // for (System *system : systems)
        //     free(system); // TOFIX: Commented out to avoid Segfault
    }

    void Engine::Init(ContextPtr &ctx)
    {
        for (System *system : ctx.sceneManager->GetActiveScene().systems)
            system->Init(ctx);
    }

    bool Engine::IsRunning(ContextPtr &ctx)
    {
        return !glfwWindowShouldClose(ctx.window->window);
    }

    void Engine::StartFrame(ContextPtr &ctx)
    {
        ctx.window->PollEvents();

        if (!IsRunning(ctx))
            return;

        if (ctx.window->GetMinimized())
            return;

        ctx.time->Update();
        ctx.input->Process();

        ctx.window->Clear({0.2f, 0.3f, 0.3f, 1.0f});

        ctx.renderer->Render(ctx);

        if (ctx.loopManager->gameTick)
            for (System *system : ctx.sceneManager->GetActiveScene().systems)
                system->Tick(ctx);
    }

    void Engine::EndFrame(Window &window)
    {
        window.SwapBuffers();
    }

    void Engine::PollEvents(Window &window)
    {
        window.PollEvents();
    }
}