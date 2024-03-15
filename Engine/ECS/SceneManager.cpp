/*
MIT License

Copyright (c) 2021 - 2023 Aryan Baburajan

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

#include <ECS/SceneManager.h>

namespace DT
{
    SceneManager::SceneManager(Context &ctx, const json &sceneManagerData) : activeScene(ctx)
    {
        PROFILE();

        LoadDemoScene();

        std::cout << "[LOG] SceneManager Constructed.\n";
    }

    void SceneManager::LoadDemoScene()
    {
        PROFILE();
    }

    void SceneManager::LoadScene()
    {
        PROFILE();
    }
    
    void SceneManager::Init(Context *ctx)
    {
        PROFILE();
        
        for (Entity entity : activeScene.GetEntities())
        {
            for (std::pair<const std::type_index, std::shared_ptr<DT::Component>> &component : activeScene.View(entity).Fatal("SceneManager::Init()"))
            {
                component.second.get()->Init(ctx);
            }
        }
    }

    void SceneManager::Tick(Context *ctx, const float &deltaTime)
    {
        PROFILE();

        for (Entity entity : activeScene.GetEntities())
            for (std::pair<const std::type_index, std::shared_ptr<DT::Component>> &component : activeScene.View(entity).Fatal("SceneManager::Tick()"))
                component.second->Tick(ctx, deltaTime);
    }

    void SceneManager::EditorTick(Context *ctx, const float &deltaTime)
    {
        PROFILE();

        for (Entity entity : activeScene.GetEntities())
            for (std::pair<const std::type_index, std::shared_ptr<DT::Component>> &component : activeScene.View(entity).Fatal("SceneManager::Tick()"))
                component.second->EditorTick(ctx, deltaTime);
    }
}