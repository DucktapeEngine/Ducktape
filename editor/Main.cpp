/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
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
        e.config.windowIconPath = "../resources/textures/logo.png";

        Scene mainScene;

        Entity player = mainScene.CreateEntity();
        player.AddComponent<Tag>().name = "Player";
        player.AddComponent<Transform>();
        player.AddComponent<NativeScriptComponent>().dllPath = "./resources/scripts/libPlayerController.dll";

        e.Init(mainScene);

        Editor::Init(e.window.window);

        while (e.IsOpen())
        {
            e.StartFrame();
            Editor::NewFrame();

            Editor::Render();

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