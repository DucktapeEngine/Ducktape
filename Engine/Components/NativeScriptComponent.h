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

#pragma once

#include <windows.h>
#include <iostream>

#include <Components/Component.h>

typedef DT::Component *(__stdcall *CreateModuleFunc)();

namespace DT
{
    std::string GetLastErrorAsString();

    class NativeScriptComponent : public Component
    {
    public:
        Component *component = nullptr;
        std::string path;
        HMODULE dll;

        NativeScriptComponent(const std::string &path);
        ~NativeScriptComponent();

        void Init()
        {
            if (!component)
                Load(path);
            component->Init();
        }

        void Tick()
        {
            component->Tick();
        }

        void OnSceneView()
        {
            component->OnSceneView();
        }

        void OnDestroy()
        {
            component->OnDestroy();
        }

        void Load(const std::string &path);
    };
}