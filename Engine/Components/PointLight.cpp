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
    void PointLight::Init()
    {
        transform = &entity.Require<Transform>();

        if (shader == nullptr)
            shader = &engine->renderer.defaultShader;

        if (engine->renderer.GetFreePointLightSpot(&lightSpot) == false)
        {
            engine->debug << "PointLight: No free light spots.\n";
        }

        propertyString = "pointLights[" + std::to_string(lightSpot) + "].";
        
        shader->Use();
        shader->SetFloat(propertyString + "constant", 1.0f);
        shader->SetFloat(propertyString + "quadratic", 1.0f);
        shader->SetBool(propertyString + "enabled", true);
    }

    void PointLight::Tick()
    {
        if (lightSpot == NAN) return;

        shader->Use();
        shader->SetVec3(propertyString + "position", transform->position);
    
        shader->SetFloat(propertyString + "linear", intensity);
        shader->SetVec3(propertyString + "ambient", color * intensity);
        shader->SetVec3(propertyString + "diffuse", color * intensity);
        shader->SetVec3(propertyString + "specular", color * intensity);
    }

    void PointLight::Inspector()
    {
        if (ImGui::CollapsingHeader("Point Light"))
        {
            ImGui::Text(std::to_string(lightSpot).c_str());
            ImGui::InputFloat("intensity##PL", &intensity);
            ImGui::ColorPicker3("color##PL", &color.x);
        }
    }

    void PointLight::SceneView(bool selected)
    {
        Tick();
    }

    void PointLight::Destroy()
    {
        engine->renderer.UnoccupyPointLightSpot(lightSpot);
        shader->SetBool(propertyString + "enabled", false);
    }

    void PointLight::System(Scene *scene)
    {
        scene->Call<PointLight>();
    }
}