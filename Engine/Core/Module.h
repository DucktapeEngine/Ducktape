/*
MIT License

Copyright (c) 2021 - 2023 Aryan Baburajan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <Core/Context.h>
#include <Core/Platform.h>
#include <Core/Error.h>

namespace DT
{
    class Module
    {
    public:
#ifdef _WIN32
        HMODULE module;
#endif
#ifdef __linux__
        void *module;
#endif

        Module(std::filesystem::path path, Error *err);
        ~Module();

        template <typename T>
        ErrorOr<T> GetSymbolAddress(const std::string &symbolName)
        {
#ifdef _WIN32
            T address = (T)GetProcAddress(module, symbolName.c_str());
#endif
#ifdef __linux__
            T address = (T)dlsym(module, symbolName.c_str());
#endif
            std::string lastError = Platform::GetLastErrorAsString();
            if (lastError.size() == 0)
                return address;
            else
                return ErrorOr<T>(lastError);
        }
    };
}