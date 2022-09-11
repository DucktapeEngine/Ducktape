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
    std::string GetLastErrorAsString()
    {
        //Get the error message ID, if any.
        DWORD errorMessageID = ::GetLastError();
        if(errorMessageID == 0) {
            return std::string(); //No error message has been recorded
        }
        
        LPSTR messageBuffer = nullptr;

        //Ask Win32 to give us the string version of that message ID.
        //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                    NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
        
        //Copy the error message into a std::string.
        std::string message(messageBuffer, size);
        
        //Free the Win32's string's buffer.
        LocalFree(messageBuffer);
                
        return message;
    }

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
            std::cout << GetLastErrorAsString() << std::endl;
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