#pragma once

// Standard includes

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <math.h>
#include <stdexcept>
#include <cstring>
#include <optional>
#include <set>
#include <fstream>
#include <assert.h>
#include <mutex>
#include <array>
#include <chrono>

// External header includes

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <entt/entt.hpp>

// Ducktape header includes

const int DUCKTAPE_VERSION_MAJOR = 1;
const int DUCKTAPE_VERSION_MINOR = 0;
const int DUCKTAPE_VERSION_PATCH = 0;

#include <Core/Assert.h>
#include <Core/Console.h>
#include <Core/AssetManager.h>
#include <Core/Scene.h>
#include <Core/Configuration.h>
#include <Rendering/Shader.h>
#include <Rendering/Vertex.h>
#include <Rendering/Window.h>
#include <Core/Engine.h>
#include <Components/Tag.h>
#include <Components/Transform.h>
#include <Core/Entity.h>