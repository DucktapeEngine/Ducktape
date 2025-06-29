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

#pragma once

#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__MINGW32__) || defined(__MINGW64__) || defined(__clang__) || defined(__APPLE_CC__)
#define __FUNCTION_NAME__ __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define __FUNCTION_NAME__ __FUNCSIG__
#else
#ifdef WIN32
#define __FUNCTION_NAME__ __FUNCTION__
#else
#define __FUNCTION_NAME__ __func__
#endif
#endif

namespace DT
{
    class Profiler
    {
    public:
        Profiler(const Profiler &) = delete;
        Profiler &operator=(const Profiler &) = delete;
        Profiler(Profiler &&) = delete;
        Profiler &operator=(Profiler &&) = delete;

        void Profile(const std::string &name)
        {
            log += "" + name + "\n";
        }

        static Profiler &Instance()
        {
            static Profiler instance;
            return instance;
        }

    private:
        std::string log;

        Profiler() {}

        ~Profiler()
        {
            std::ofstream logFile(std::filesystem::current_path() / "Ducktape.log");
            logFile << log;
        }
    };
}

// TODO: Better RAII-based profiling
#if defined(DT_PROFILE) && !defined(DT_EXPORT)
#define PROFILE() DT::Profiler::Instance().Profile(__FUNCTION_NAME__);
#else
#define PROFILE() ;
#endif