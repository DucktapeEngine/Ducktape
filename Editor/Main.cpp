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

#include <Ducktape.h>

#include <Core/Editor.h>

using namespace DT;

int main()
{
    try
    {
        Engine e;
        e.config.windowSize = {800, 600};
        e.config.windowTitle = "DucktapeTest";
        e.config.drawToQuad = false;
        e.config.windowIconPath = "../Resources/textures/logo.png";
        e.config.skyboxCubemapPaths = {
            "../Resources/Textures/Skybox/right.jpg",
            "../Resources/Textures/Skybox/left.jpg",
            "../Resources/Textures/Skybox/top.jpg",
            "../Resources/Textures/Skybox/bottom.jpg",
            "../Resources/Textures/Skybox/front.jpg",
            "../Resources/Textures/Skybox/back.jpg"
        };

        Scene mainScene(&e);

        mainScene.LoadModule("./Resources/Scripts/libGame.dll");

        Entity camera = mainScene.CreateEntity();
        camera.Assign<Tag>().name = "Camera";
        camera.Assign<Transform>();
        // camera.Assign("PlayerController");
        camera.Assign<DirectionalLight>();
        camera.Assign<PointLight>();

        Entity model = mainScene.CreateEntity();
        model.Assign<Tag>().name = "Model";
        model.Assign<Transform>();
        // model.Assign<ModelExtractor>().path = "../Resources/Models/cube.obj";
        model.Assign<ModelExtractor>().path = "../Resources/Models/backpack/backpack.obj";

        e.Init(mainScene);

        Editor::Init(e.window.window);

        while (e.IsOpen())
        {
            e.StartFrame();
            Editor::NewFrame();

            e.activeScene->CallLoop(CallState::SceneView);

            Editor::Render(&e);

            Editor::EndFrame(e.renderer);
            e.EndFrame();
        }

        Editor::Terminate();
        e.Terminate();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cin.get();
    }
}