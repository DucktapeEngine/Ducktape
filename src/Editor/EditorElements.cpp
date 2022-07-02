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

#include <Editor/EditorElements.h>

namespace DT
{
    void EditorElements::MenuBar()
    {
        ImGui::BeginMainMenuBar();

        if (ImGui::BeginMenu("Layout"))
        {
            ImGui::InputText("Layout name", &layoutName);

            if (ImGui::Button("Save Layout"))
            {
                std::string layoutPath = "./editor/layouts/" + layoutName + ".ini";
                std::string imguiPath = "./imgui.ini";

                std::filesystem::create_directories("./editor/layouts/");
                std::filesystem::remove(layoutPath);
                std::filesystem::copy_file(imguiPath, layoutPath);

                debug << "Saved Layout at " << layoutPath << "\n";
            }

            if (ImGui::BeginMenu("Load Layout"))
            {
                std::vector<std::string> layouts;

                for (auto &p : std::filesystem::directory_iterator("./editor/layouts/"))
                {
                    layouts.push_back(p.path().filename().string());
                }

                for (auto &layout : layouts)
                {
                    if (ImGui::MenuItem(layout.c_str()))
                    {
                        std::string layoutPath = "./editor/layouts/" + layout;
                        std::string imguiPath = "./imgui.ini";

                        std::filesystem::remove(imguiPath);
                        std::filesystem::copy_file(layoutPath, imguiPath);

                        debug << "Loaded Layout from " << layoutPath << "\n";
                    }
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    void EditorElements::SceneView()
    {
        ImGui::Begin("Scene View");

        Scene::activeScene->sceneRegistry.each([](const entt::entity entity)
                                               {
            std::string label = "Entity " + std::to_string(entt::to_integral(entity));

            if (Scene::activeScene->sceneRegistry.any_of<Tag>(entity))
            {
                std::string _label = Scene::activeScene->sceneRegistry.get<Tag>(entity).name;

                if (_label != "Unnamed")
                    label = _label;
            }

            if (ImGui::Selectable(label.c_str(), selectedEntity == entity))
            {
                selectedEntity = entity;
            } });

        ImGui::End();
    }

    void EditorElements::Inspector()
    {
        ImGui::Begin("Inspector");

        Scene::activeScene->callState = CallState::OnGUI;
        Scene::activeScene->selectedEntity = selectedEntity;
        Scene::activeScene->tickFunction(*Scene::activeScene);

        ImGui::End();
    }

    void EditorElements::Console()
    {
        ImGui::Begin("Console");

        ImGui::Text(debug.log.c_str());

        ImGui::End();
    }
}