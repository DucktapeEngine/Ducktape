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

#pragma once

#include <ECS/SceneManager.h>
#include <Panels/Panel.h>

namespace DT
{
    class WorldOutlinerPanel : public Panel
    {
    public:
		void Init(Context &ctx) override
        {
            PROFILE();
            
            sceneManager = ctx.GetService<SceneManager>().Fatal("WorldOutlinerPanel::Init()");
        }

		void Tick(Context &ctx, const float &dt) override
        {
            PROFILE();
            
            ImGui::Begin("World Outliner", &isOpen);

            // Entity control
            if (ImGui::Button("Create Entity", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
                selectedEntity = sceneManager->activeScene.CreateEntity();
            if (ImGui::Button("Destroy Entity", ImVec2(ImGui::GetWindowSize().x, 0.0f)))
                sceneManager->activeScene.DestroyEntity(selectedEntity).Fatal("WorldOutlinerPanel::Tick()");

            // Entity list
            for (Entity entity : sceneManager->activeScene.GetEntities())
            {
                std::string label;
                if (sceneManager->activeScene.Has<Tag>(entity))
                    label = sceneManager->activeScene.Get<Tag>(entity).Fatal("GameView::Tick()")->name;
                else
                    label = "Entity " + std::to_string(entity);

                if (ImGui::Selectable((label + "##" + std::to_string(entity)).c_str(), selectedEntity == entity))
                    selectedEntity = entity;
            }

            ImGui::End();
        }

        Entity &GetSelectedEntity()
        {
            return selectedEntity;
        }
    
    private:
        SceneManager *sceneManager;
        Entity selectedEntity = 0;

        friend class InspectorPanel;
    };
}