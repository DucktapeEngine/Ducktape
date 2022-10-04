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

#include <Core/Editor.h>
#include <Core/EditorModules.h>

using namespace DT;

int main()
{
    try
    {
        Configuration config;
        config.windowSize = {800, 600};
        config.windowTitle = "DucktapeTest";
        config.drawToQuad = false;
        config.windowIconPath = "../Resources/textures/logo.png";
        config.skyboxCubemapPaths = {
            "../Resources/Textures/Skybox/right.jpg",
            "../Resources/Textures/Skybox/left.jpg",
            "../Resources/Textures/Skybox/top.jpg",
            "../Resources/Textures/Skybox/bottom.jpg",
            "../Resources/Textures/Skybox/front.jpg",
            "../Resources/Textures/Skybox/back.jpg"
        };

        Engine e(config);
        Scene mainScene(&e);

        mainScene.LoadModule("./Resources/Scripts/libGame.dll");

        Entity camera = mainScene.CreateEntity();
        camera.Assign<Tag>().name = "Camera";
        camera.Assign<Transform>();
        camera.Assign<Camera>();
        camera.Assign<DirectionalLight>();

        Entity model = mainScene.CreateEntity();
        model.Assign<Tag>().name = "Model";
        model.Assign<Transform>();

        std::vector<Mesh> meshes = LoadModel("../Resources/Models/backpack/backpack.obj").meshes;
        for (Mesh mesh : meshes)
        {
            mainScene.CreateEntity().Assign<MeshRenderer>().mesh = mesh;
        }

        e.loopManager.sceneTick = false;

        e.Init(mainScene);

        Editor::Init(&e);

        while (e.IsOpen())
        {
            e.StartFrame();
            Editor::NewFrame();

            e.activeScene->CallLoop(EditorModules::SceneViewLoop);

            Editor::Render();

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