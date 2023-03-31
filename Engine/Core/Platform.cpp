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

#include <iostream>

#include <Core/Platform.h>

namespace DT
{
    std::string Platform::GetLastErrorAsString()
    {
#ifdef _WIN32
        DWORD errorMessageID = ::GetLastError();
        if (errorMessageID == 0)
        {
            return std::string();
        }

        LPSTR messageBuffer = nullptr;

        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

        std::string message(messageBuffer, size);

        LocalFree(messageBuffer);

        return message;
#endif
#ifdef __linux__
        // Write Linux specific code here
#endif
    }

    void Platform::Execute(const std::string command)
    {
#ifdef _WIN32
        ShellExecute(NULL, NULL, command.c_str(), NULL, NULL, SW_SHOWDEFAULT);
#endif
#ifdef __linux__
        system(command.c_str());
#endif
    }

    Platform::Module::~Module()
    {
        Free();
    }

    void Platform::Module::Load(std::filesystem::path path)
    {
#ifdef _WIN32
        module = LoadLibrary(path.string().c_str());

        if (!module)
            std::cout << GetLastErrorAsString();
#endif
#ifdef __linux__
        module = dlopen(path.string().c_str(), RTLD_LAZY);
#endif
    }

    void Platform::Module::Free()
    {
#ifdef _WIN32
        FreeLibrary(module);
#endif
#ifdef __linux__
        dlclose(module);
#endif
    }
}