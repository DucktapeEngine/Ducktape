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

// External header includes

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <entt/entt.hpp>

// Ducktape header includes

const int DUCKTAPE_VERSION_MAJOR = 1;
const int DUCKTAPE_VERSION_MINOR = 0;
const int DUCKTAPE_VERSION_PATCH = 0;

std::mutex globalMutex;

#include <Core/Assert.h>
#include <Core/Math.h>
#include <Core/Vector.h>
#include <Core/Console.h>
#include <Core/Configuration.h>
#include <Core/Application.h>
#include <Components/Transform.h>
#include <Core/Scene.h>
#include <Core/Entity.h>