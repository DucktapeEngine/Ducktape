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

#include <Panels/Panel.h>
#include <Editor.h>
#include <Panels/WorldOutliner.h>

namespace DT
{
    class InspectorPanel : public Panel
    {
    public:
        void Init(Context &ctx) override
        {
            worldOutliner = editor->GetPanel<WorldOutlinerPanel>().Fatal("InspectorPanel::Init()");
            sceneManager = ctx.GetService<SceneManager>().Fatal("InspectorPanel::Init()");
        }

		void Tick(Context &ctx, const float &dt) override
        {
            PROFILE();
            
            ImGui::Begin("Inspector", &isOpen);

            if (sceneManager->activeScene.IsValid(worldOutliner->GetSelectedEntity()))
            {
                auto components = sceneManager->activeScene.View(worldOutliner->GetSelectedEntity()).Fatal("InspectorPanel::Fatal()");
                for (auto component : components)
                    component.second->InspectorMenu(&ctx, dt);
            }

            ImGui::End();
        }

    private:
        WorldOutlinerPanel *worldOutliner;
        SceneManager *sceneManager;
    };
}