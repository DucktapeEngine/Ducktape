/*
Ducktape | An open source C++ 2D & 3D game Engine that focuses on being fast, and powerful.
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

#define DT_DEBUG

#include <Core/Context.h>
#include <Components/RegisterComponentSystems.h>
#include <Editor.h>
#include <Panels/ConsolePanel.h>
#include <Panels/ScenePanel.h>
#include <Panels/PropertiesPanel.h>
#include <Panels/MenuBarPanel.h>
#include <Panels/ProjectPanel.h>
#include <Panels/ResourceBrowserPanel.h>
#include <Panels/ResourceInspectorPanel.h>
#include <Panels/ResourceInterface.h>
#include <Panels/SceneViewPanel.h>
#include <Panels/DucktapeEditorPanel.h>
#include <Panels/ComponentMenuPanel.h>
using namespace DT;

int main()
{
    try
    {
        Context ctx(DUCKTAPE_ROOT_DIR / "Resources" / "Sandbox" / "Assets" / "DucktapeProjectSettings.json");

        // RegisterComponentSystems(mainScene);

        // SceneManager::Load(DUCKTAPE_ROOT_DIR / "Resources" / "Sandbox" / "Assets" / "Scenes" / "MainScenctx.engine.json", mainScene, e);

        // Entity camera = mainScenctx.engine.CreateEntity();
        // mainScenctx.engine.Assign<Tag>(camera).name = "Camera";
        // mainScenctx.engine.Assign<Transform>(camera);
        // mainScenctx.engine.Assign<Camera>(camera);
        // mainScenctx.engine.Assign<DirectionalLight>(camera);

        // Entity bag = mainScenctx.engine.CreateEntity();
        // mainScenctx.engine.Assign<Tag>(bag).name = "Bag";
        // mainScenctx.engine.Assign<Relation>(bag).SetParent(camera, mainScene);
        // mainScenctx.engine.Assign(bag, "PlayerController");

        // for (const auto &meshAsset : std::filesystem::directory_iterator(ctx.engine.project.directory / "Assets" / "Models" / "backpack" / "backpack"))
        // {
        //     if (!meshAsset.is_directory())
        //     {
        //         Entity mesh = mainScenctx.engine.CreateEntity();
        //         mainScenctx.engine.Assign<Relation>(mesh).SetParent(bag, mainScene);
        //         mainScenctx.engine.Assign<MeshRenderer>(mesh).mesh = ctx.resourceManager->GetRID(meshAsset);
        //         break;
        //     }
        // }

        ctx.engine.Init(ctx.pointer);

        Editor::AddPanel<SceneViewPanel>();
        Editor::AddPanel<ScenePanel>();
        Editor::AddPanel<ResourceBrowserPanel>();
        Editor::AddPanel<ResourceInspectorPanel>();
        Editor::AddPanel<ConsolePanel>();
        Editor::AddPanel<PropertiesPanel>();
        Editor::AddPanel<MenuBarPanel>();
        Editor::AddPanel<ProjectPanel>();
        Editor::AddPanel<DucktapeEditorPanel>();
        Editor::AddPanel<ComponentMenuPanel>();
        ResourceInterface::AddDefault(ctx.pointer);

        Editor::Init(ctx.pointer);

        ctx.loopManager.sceneTick = true;

        while (ctx.engine.IsRunning(ctx.pointer))
        {
            ctx.engine.PollEvents(ctx.window);

            if (!ctx.engine.IsRunning(ctx.pointer))
                break;

            ctx.engine.StartFrame(ctx.pointer);

            Editor::NewFrame();

            if (ctx.loopManager.sceneTick)
                for (System *system : ctx.sceneManager.GetActiveScene().systems)
                    system->SceneView(ctx.pointer);

            Editor::Render();

            Editor::EndFrame();
            ctx.engine.EndFrame(ctx.window);
        }

        // ctx.project.Save(); Implement ctx.Save();
        Editor::Terminate();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cin.get();
    }
}