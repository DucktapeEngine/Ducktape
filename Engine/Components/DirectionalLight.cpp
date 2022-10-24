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

#include <Components/DirectionalLight.h>

namespace DT
{
    void DirectionalLightSystem::Init(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<DirectionalLight>())
        {
            DirectionalLight &dl = scene.Get<DirectionalLight>(entity);

            dl.transform = &scene.Require<Transform>(entity);

            if (dl.shader == nullptr)
                dl.shader = &engine.renderer.defaultShader;

            if (engine.renderer.GetFreeDirectionalLightSpot(&dl.lightSpot) == false)
            {
                engine.debug.Err() << "DirectionalLight: No free light spots.\n";
                continue;
            }

            dl.propertyString = "directionalLights[" + std::to_string(dl.lightSpot) + "].";
            dl.shader->Use();
            dl.shader->SetBool(dl.propertyString + "enabled", true);
        }
    }

    void DirectionalLightSystem::Tick(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<DirectionalLight>())
        {
            DirectionalLight &dl = scene.Get<DirectionalLight>(entity);

            if (dl.lightSpot == NAN)
                continue;

            dl.shader->Use();
            dl.shader->SetVec3(dl.propertyString + "direction", dl.transform->Forward());
            dl.shader->SetVec3(dl.propertyString + "ambient", dl.color * dl.intensity);
            dl.shader->SetVec3(dl.propertyString + "diffuse", dl.color * dl.intensity);
            dl.shader->SetVec3(dl.propertyString + "specular", dl.color * dl.intensity);
        }
    }

    void DirectionalLightSystem::Destroy(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<DirectionalLight>())
        {
            DirectionalLight &dl = scene.Get<DirectionalLight>(entity);

            engine.renderer.UnoccupyDirectionalLightSpot(dl.lightSpot);
            dl.shader->SetBool(dl.propertyString + "enabled", true);
        }
    }

    void DirectionalLightSystem::SceneView(Scene &scene, Engine &engine)
    {
        Tick(scene, engine);
    }

    void DirectionalLightSystem::Serialize(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<DirectionalLight>())
        {
            DirectionalLight &dl = scene.Get<DirectionalLight>(entity);

            engine.serialization.SerializeComponent("DirectionalLight", dl, entity);
        }
    }

    void DirectionalLightSystem::Inspector(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<DirectionalLight>())
        {
            if (scene.selectedEntity != entity)
                continue;

            DirectionalLight &dl = scene.Get<DirectionalLight>(entity);

            if (ImGui::CollapsingHeader("Directional Light"))
            {
                ImGui::DragFloat("intensity", &dl.intensity);
                ImGui::ColorEdit3("color", &dl.color.x);
            }
        }
    }
}