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
    void DirectionalLight::Init()
    {
        transform = &entity.Require<Transform>();

        if (shader == nullptr)
            shader = &engine->renderer.defaultShader;

        lightSpot = engine->renderer.GetFreeDirectionalLightSpot();

        if (lightSpot == NAN)
        {
            engine->debug << "DirectionalLight: No free light spots.\n";
        }

        propertyString = "directionalLights[" + std::to_string(lightSpot) + "].";
        shader->SetBool(propertyString + "enabled", true);
    }

    void DirectionalLight::Tick()
    {
        if (lightSpot == NAN) return;

        shader->Use();
        shader->SetVec3(propertyString + "direction", transform->Forward());
        shader->SetVec3(propertyString + "ambient", color * intensity);
        shader->SetVec3(propertyString + "diffuse", color * intensity);
        shader->SetVec3(propertyString + "specular", color * intensity);
    }

    void DirectionalLight::Inspector()
    {
        if (ImGui::CollapsingHeader("Directional Light"))
        {
            ImGui::InputFloat("intensity##DL", &intensity);
            ImGui::ColorPicker3("color##DL", &color.x);
        }
    }

    void DirectionalLight::Destroy()
    {
        engine->renderer.UnoccupyDirectionalLightSpot(lightSpot);
        shader->SetBool(propertyString + "enabled", true);
    }

    void DirectionalLight::System(Scene *scene)
    {
        scene->Call<DirectionalLight>();
    }
}