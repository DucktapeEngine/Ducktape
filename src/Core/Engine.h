#pragma once

namespace Ducktape
{
    namespace Engine
    {
        void MainLoop(Scene &scene)
        {
            while (!glfwWindowShouldClose(Window::window))
            {
                glfwPollEvents();
                Window::DrawFrame();
            }

            vkDeviceWaitIdle(Window::device);
        }

        void Run(Scene &scene)
        {
            try
            {
                Window::Init();
                MainLoop(scene);
                Window::Cleanup();
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
                std::cin.get();
            }
        }
    }
}