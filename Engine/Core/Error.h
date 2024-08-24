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


namespace DT
{
    class [[nodiscard]] Error
    {
    public:
        Error() = default;
        Error(const std::string &_error);
        ~Error();

        bool HasError();
        std::string &GetError();
        void Log(const std::string &errorContext = "");
        void Err(const std::string &errorContext = "");
        void Fatal(const std::string &errorContext = "");

    private:
        std::optional<std::string> error;
        bool handled = true;
    };

    template <typename T>
    class [[nodiscard]] ErrorOr
    {
    public:
        ErrorOr(T _value) : value(_value)
        {
            PROFILE();            
        }
        ErrorOr(const std::string &_error) : error(_error)
        {
            PROFILE();

            handled = false;
        }

        ~ErrorOr()
        {
            PROFILE();

            if (handled) return;

            std::cout << "[FATAL] Unhandled error: " + error.value() << ".\n";
            abort();
        }
        
        T GetValue()
        {
            PROFILE();

            handled = true;
            return value.value();
        }

        bool HasError()
        {
            PROFILE();

            handled = true;
            return error.has_value();
        }

        std::string &GetError()
        {
            PROFILE();

            handled = true;
            assert(HasError());
            return error.value();
        }

        T Log(const std::string &errorContext = "")
        {
            PROFILE();

            handled = true;
            if (!HasError()) return GetValue();
            std::cout << "[LOG] " << (errorContext != "" ? errorContext + "\n      " : "") << error.value();
        }

        T Err(const std::string &errorContext = "")
        {
            PROFILE();

            handled = true;
            if (!HasError()) return GetValue();
            std::cout << "[ERR] " << (errorContext != "" ? errorContext + "\n      " : "") << error.value();
        }

        T Fatal(const std::string &errorContext = "")
        {
            PROFILE();

            handled = true;
            if (!HasError()) return GetValue();
            std::cout << "[FATAL] " << (errorContext != "" ? errorContext + "\n        " : "") << error.value();
            abort();
        }
    
    private:
        std::optional<std::string> error;
        std::optional<T> value;
        bool handled = true;
    };
}