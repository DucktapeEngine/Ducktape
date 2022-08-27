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

#include <Components/NativeScriptComponent.h>

namespace DT
{
    NativeScriptComponent::NativeScriptComponent(const std::string &path)
    {
        this->path = path;
    }

    NativeScriptComponent::~NativeScriptComponent()
    {
        if (component)
        {
            delete component;
            FreeLibrary(dll);
        }
    }

    void NativeScriptComponent::Load(const std::string &path)
    {
        this->path = path;

        if (component)
        {
            delete component;
            FreeLibrary(dll);
        }

        HMODULE dll = LoadLibrary(path.c_str());

        if (!dll)
        {
            std::cout << "Failed to load DLL: " << path << std::endl;
            return;
        }

        CreateModuleFunc createModule = (CreateModuleFunc)GetProcAddress(dll, "CreateModule");

        if (!createModule)
        {
            std::cout << "Failed to get CreateModule function from DLL: " << path << std::endl;
            FreeLibrary(dll);
            return;
        }

        component = (*createModule)();
        component->holderComponent = this;
        component->engine = engine;
    }
}