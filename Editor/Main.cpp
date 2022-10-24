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
#include <Ducktape.h>

#include <Editor.h>

using namespace DT;

int main()
{
    try
    {
        Configuration config;
        config.windowSize = {800, 600};
        config.windowTitle = "DucktapeTest";
        config.drawToQuad = false;
        config.projectDirectory = DUCKTAPE_ROOT_DIR / "Resources" / "Sandbox";
        config.windowIconPath = DUCKTAPE_ROOT_DIR / "Resources" / "Editor" / "Textures" / "logo.png";
        config.skyboxCubemapPaths = {
            config.projectDirectory / "Assets" / "Textures" / "Skybox" / "right.jpg",
            config.projectDirectory / "Assets" / "Textures" / "Skybox" / "left.jpg",
            config.projectDirectory / "Assets" / "Textures" / "Skybox" / "top.jpg",
            config.projectDirectory / "Assets" / "Textures" / "Skybox" / "bottom.jpg",
            config.projectDirectory / "Assets" / "Textures" / "Skybox" / "front.jpg",
            config.projectDirectory / "Assets" / "Textures" / "Skybox" / "back.jpg"};
        config.gameModule = DUCKTAPE_ROOT_DIR / "Build" / "Resources" / "Sandbox" / "Assets" / "Scripts" / "libGame.dll";

        Engine e(config);

        // Engine e(DUCKTAPE_ROOT_DIR / "Resources" / "Sandbox");

        Scene mainScene(&e, e.config);

        RegisterComponentSystems(mainScene);

        // SceneManager::Load(e.config.projectDirectory / "Assets" / "Scenes" / "MainScene.json", mainScene, e);

        Entity camera = mainScene.CreateEntity();
        mainScene.Assign<Tag>(camera).name = "Camera";
        mainScene.Assign<Transform>(camera);
        mainScene.Assign<Camera>(camera);
        mainScene.Assign<DirectionalLight>(camera);

        std::vector<Mesh> meshes = LoadModel(e.config.projectDirectory / "Assets" / "Models" / "backpack" / "backpack.obj").meshes;
        for (Mesh mesh : meshes)
            mainScene.Assign<MeshRenderer>(mainScene.CreateEntity()).mesh = mesh;

        e.loopManager.sceneTick = false;

        e.Init(mainScene);

        Editor::Init(e);

        while (e.IsOpen())
        {
            e.StartFrame();
            Editor::NewFrame();

            for (System *system : mainScene.GetSystems())
                system->SceneView(mainScene, e);

            Editor::Render(e);

            Editor::EndFrame(e.renderer);
            e.EndFrame();
        }

        Editor::Terminate();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cin.get();
    }
}