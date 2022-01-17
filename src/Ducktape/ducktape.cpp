/*
MIT License

Copyright (c) 2022 Ducktape

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <Ducktape/ducktape.h>

namespace DT
{
    void Update()
    {
        if(SceneManager::currentScene == nullptr)
        {
            Debug::LogSuccess("Ducktape is ready to go!");
            Debug::LogSuccess("Get Started: https://ducktapeengine.github.io/manual/intro");
            return;
        }

        for(size_t i=0;i<SceneManager::currentScene->entities.size();i++)
        {
            if(SceneManager::currentScene->entities[i]->isDestroyed == false && SceneManager::currentScene->entities[i]->isEnabled && SceneManager::currentScene->entities[i] != nullptr)
            {
                for(size_t j=0;j<SceneManager::currentScene->entities[i]->components.size();j++)
                {
                    if(SceneManager::currentScene->entities[i]->components[j]->isDestroyed == false && SceneManager::currentScene->entities[i]->components[j]->isEnabled && SceneManager::currentScene->entities[i]->components[j] != nullptr)
                    {
                        SceneManager::currentScene->entities[i]->components[j]->Start();
                    }
                }
            }
        }

        Physics::Initialize();
        Application::Initialize();

        // run the program as long as the window is open
        while (Application::IsOpen())
        {
            Input::Update();
            Time::Update();

            Application::renderWindow.clear(ProjectSettings::sceneBackgroundColor.ToSFMLColor());

            for(size_t i=0;i<SceneManager::currentScene->entities.size();i++)
            {
                if(SceneManager::currentScene->entities[i]->isDestroyed == false && SceneManager::currentScene->entities[i]->isEnabled && SceneManager::currentScene->entities[i] != nullptr)
                {
                    for(size_t j=0;j<SceneManager::currentScene->entities[i]->components.size();j++)
                    {
                        if(SceneManager::currentScene->entities[i]->components[j]->isDestroyed == false && SceneManager::currentScene->entities[i]->components[j]->isEnabled && SceneManager::currentScene->entities[i]->components[j] != nullptr)
                        {
                            SceneManager::currentScene->entities[i]->components[j]->Update();
                        }
                    }
                }
            }
            
            Physics::physicsWorld.Step(Time::deltaTime, Physics::velocityIterations, Physics::positionIterations);

            Application::renderWindow.setView(Application::view);

            Application::renderWindow.display();
        }

        for(size_t i=0;i<SceneManager::currentScene->entities.size();i++)
        {
            if(SceneManager::currentScene->entities[i]->isDestroyed == false && SceneManager::currentScene->entities[i]->isEnabled && SceneManager::currentScene->entities[i] != nullptr)
            {
                for(size_t j=0;j<SceneManager::currentScene->entities[i]->components.size();j++)
                {
                    if(SceneManager::currentScene->entities[i]->components[j]->isDestroyed == false && SceneManager::currentScene->entities[i]->components[j]->isEnabled && SceneManager::currentScene->entities[i]->components[j] != nullptr)
                    {
                        SceneManager::currentScene->entities[i]->components[j]->OnApplicationClose();
                    }
                }
            }
        }
    }
}