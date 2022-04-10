/*
MIT License

Copyright (c) 2022 Ducktape

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

// Ducktape includes

const int DUCKTAPE_VERSION_MAJOR = 1;
const int DUCKTAPE_VERSION_MINOR = 0;
const int DUCKTAPE_VERSION_PATCH = 0;

#define STB_IMAGE_IMPLEMENTATION
#include <stbimage/stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#include <Core/Assert.h>
#include <Core/Console.h>
#include <Core/AssetManager.h>
#include <Core/Scene.h>
#include <Core/Configuration.h>
#include <Rendering/Vertex.h>
#include <Rendering/Window.h>
#include <Core/Engine.h>
#include <Components/Tag.h>
#include <Components/Transform.h>
#include <Core/Entity.h>
