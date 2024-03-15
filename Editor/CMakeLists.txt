# MIT License

# Copyright (c) 2021 - 2023 Aryan Baburajan

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required (VERSION 3.20)

file (GLOB_RECURSE dt_source_list "${PROJECT_SOURCE_DIR}/Editor/**/*.cpp" "${PROJECT_SOURCE_DIR}/Editor/*.cpp")
add_library (DucktapeEditor SHARED ${dt_source_list})
set_target_properties (DucktapeEditor PROPERTIES PREFIX "")
target_precompile_headers(DucktapeEditor PUBLIC "${PROJECT_SOURCE_DIR}/Engine/dtpch.h")