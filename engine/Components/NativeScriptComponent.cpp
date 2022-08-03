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

#include <Components/NativeScriptComponent.h>

namespace DT
{
    void NativeScriptComponent::Load(const std::string &path)
    {
        HINSTANCE hInstance = LoadLibrary(path.c_str());

        if (!hInstance)
        {
            std::cout << "Failed to load DLL: " << dllPath << std::endl;
            return;
        }

        CreateModuleFunc createModule = (CreateModuleFunc)GetProcAddress(hInstance, "CreateModule");

        if (!createModule)
        {
            std::cout << "Failed to get CreateModule function from DLL: " << dllPath << std::endl;
            return;
        }

        component = createModule();
        isLoaded = true;
    }

    void NativeScriptComponent::Init(Engine &e)
    {
        if (!isLoaded)
            Load(dllPath);

        component->Init();
    }

    void NativeScriptComponent::Tick(Engine &e)
    {
        if (isLoaded)
            component->Tick();
    }

    void NativeScriptComponent::OnDestroy(Engine &e)
    {
        if (isLoaded)
            component->OnDestroy();
    }
}