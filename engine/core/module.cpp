/*
MIT License

Copyright (c) 2021 - 2025 Aryan Baburajan

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

#include "core/module.h"
#include "core/platform.h"

namespace dt {
module::module(std::filesystem::path path) {
#ifdef _WIN32
    dll_module = load_library(path.string().c_str());
#endif
#ifdef __linux__
    dll_module = dlopen(path.string().c_str(), RTLD_LAZY);
#endif

    if (!dll_module)
        // *err = error("error loading game_module at " + path.string() + ".\n_error: " + platform::GetLastErrorAsString());
        return;
    else
        std::cout << "loaded game_module at " << path << ".\n";
}

module::~module() {
#ifdef _WIN32
    if (dll_module)
        free_library(dll_module);
#endif
#ifdef __linux__
    if (dll_module)
        dlclose(dll_module);
#endif
}
} // namespace dt