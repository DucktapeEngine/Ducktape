#include "ducktape.h"

namespace DT
{
    Scene* currentScene = nullptr;

    void FixedUpdateThread()
    {
        while(Application::IsOpen())
        {
            ComponentExecutionHandler::FixedUpdate();
            std::this_thread::sleep_for(0.01666666666s);
        }
    }

    void Update()
    {
        ComponentExecutionHandler::Start();
        Physics::Initialize();
        Application::Initialize();

        std::thread fixedUpdateThread(FixedUpdateThread);

        // run the program as long as the window is open
        while (Application::IsOpen())
        {
            Input::Update();
            Time::Update();

            Application::renderWindow.clear(ProjectSettings::sceneBackgroundColor.ToSFMLColor());

            ComponentExecutionHandler::Update();
            
            Physics::physicsWorld.Step(Time::deltaTime, Physics::velocityIterations, Physics::positionIterations);

            Application::renderWindow.setView(Application::view);

            Application::renderWindow.display();
        }

        fixedUpdateThread.join();
    }
}