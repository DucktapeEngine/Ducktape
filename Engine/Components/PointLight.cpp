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

#include <Components/PointLight.h>

namespace DT
{
    void PointLightSystem::Init(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<PointLight>())
        {
            PointLight &pl = scene.Get<PointLight>(entity);

            pl.transform = &scene.Require<Transform>(entity);

            if (pl.shader == nullptr)
                pl.shader = &engine.renderer.defaultShader;

            if (engine.renderer.GetFreePointLightSpot(&pl.lightSpot) == false)
            {
                engine.debug << "PointLight: No free light spots.\n";
            }

            pl.propertyString = "pointLights[" + std::to_string(pl.lightSpot) + "].";
            
            pl.shader->Use();
            pl.shader->SetFloat(pl.propertyString + "constant", 1.0f);
            pl.shader->SetFloat(pl.propertyString + "quadratic", 1.0f);
            pl.shader->SetBool(pl.propertyString + "enabled", true);
        }
    }

    void PointLightSystem::Tick(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<PointLight>())
        {
            PointLight &pl = scene.Get<PointLight>(entity);
            
            if (pl.lightSpot == NAN) return;

            pl.shader->Use();
            pl.shader->SetVec3(pl.propertyString + "position", pl.transform->translation);
        
            pl.shader->SetFloat(pl.propertyString + "linear", pl.intensity);
            pl.shader->SetVec3(pl.propertyString + "ambient", pl.color * pl.intensity);
            pl.shader->SetVec3(pl.propertyString + "diffuse", pl.color * pl.intensity);
            pl.shader->SetVec3(pl.propertyString + "specular", pl.color * pl.intensity);
        }
    }

    void PointLightSystem::Inspector(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<PointLight>())
        {
            if (scene.selectedEntity != entity)
                continue;

            PointLight &pl = scene.Get<PointLight>(entity);

            if (ImGui::CollapsingHeader("Point Light"))
            {
                ImGui::DragFloat("intensity", &pl.intensity);
                ImGui::ColorEdit3("color", &pl.color.x);
            }
        }
    }

    void PointLightSystem::SceneView(Scene &scene, Engine &engine)
    {
        Tick(scene, engine);
    }
    
    void PointLightSystem::Serialize(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<PointLight>())
        {
            PointLight &pl = scene.Get<PointLight>(entity);

            engine.serialization.SerializeComponent("PointLight", pl, entity);
        }
    }

    void PointLightSystem::Destroy(Scene &scene, Engine &engine)
    {
        for (Entity entity : scene.View<PointLight>())
        {
            PointLight &pl = scene.Get<PointLight>(entity);

            engine.renderer.UnoccupyPointLightSpot(pl.lightSpot);
            pl.shader->SetBool(pl.propertyString + "enabled", false); // TOFIX: Move this to Renderer class
        }
    }
}