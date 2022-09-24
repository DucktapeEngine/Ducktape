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
        propertyString = "directionalLights[" + std::to_string(lightSpot) + "].";
    }

    void DirectionalLight::Tick()
    {
        shader->Use();
        shader->SetVec3(propertyString + "direction", transform->Forward());
        shader->SetVec3(propertyString + "ambient", ambientColor * ambient);
        shader->SetVec3(propertyString + "diffuse", diffuseColor * diffuse);
        shader->SetVec3(propertyString + "specular", specularColor * specular);
    }

    void DirectionalLight::Inspector()
    {
        if (ImGui::CollapsingHeader("Directional Light"))
        {
            ImGui::SliderFloat("ambient", &ambient, 0.f, 1.f);
            ImGui::ColorPicker3("ambientColor", &ambientColor.x);

            ImGui::SliderFloat("diffuse", &diffuse, 0.f, 1.f);
            ImGui::ColorPicker3("diffuseColor", &diffuseColor.x);
            
            ImGui::SliderFloat("specular", &specular, 0.f, 1.f);
            ImGui::ColorPicker3("specularColor", &specularColor.x);
        }
    }

    void DirectionalLight::Destroy()
    {
        engine->renderer.UnoccupyDirectionalLightSpot(lightSpot);
    }

    void DirectionalLight::System(Scene *scene)
    {
        scene->Call<DirectionalLight>();
    }
}