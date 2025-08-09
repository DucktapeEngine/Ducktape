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

#include <filesystem>
#include <memory>
#include <variant>

#include "core/log.h"

namespace dt {
template <typename T>
class asset {
  public:
    std::string path;

    asset(const std::string &path) {
        load(path);
    }

    void load(const std::string &path) {
        const std::filesystem::path absolute_path = get_absolute_path(path);

        auto it = cache.find(path);

        if (it == cache.end())
            LOG("loading asset from {}", path);

        if (it != cache.end())
            data = it->second;
        else {
            data = T::load(absolute_path);
            cache[path] = data;
        }
    }

    void make_local_copy() {
        data = T::load(path);
        stray.insert(data);
    }

    T *operator->() {
        return data.get();
    }

    const T *operator->() const {
        return data.get();
    }

    std::shared_ptr<T> get() {
        return data;
    }

    const std::shared_ptr<T> get() const {
        return data;
    }

    const bool has() const {
        return data != nullptr;
    }

    static std::filesystem::path get_absolute_path(const std::string &path) {
        return std::filesystem::current_path() / "assets" / path;
    }

    static void cleanup() {
        cache.clear();
        stray.clear();
    }

  protected:
    std::shared_ptr<T> data = nullptr;

    static inline std::unordered_map<std::string, std::shared_ptr<T>> cache;
    static inline std::unordered_set<std::shared_ptr<T>> stray;
};
} // namespace dt