#ifndef DUCKTAPE_H
#define DUCKTAPE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
#include <utility>
#include <algorithm>

using namespace std::chrono_literals;

#include "external/box2d/include/box2d/box2d.h"

#include "engine/dt_time.h"
#include "engine/application.h"

namespace DT
{
    class GameObject;
}

#include "engine/componentexecutionhandler.h"
#include "engine/input.h"
#include "physics/physics.h"

namespace DT
{
    class RevoluteJoint2D;
    class DistanceJoint2D;
    class PrismaticJoint2D;
    class WeldJoint2D;
    class PulleyJoint2D;
    class FrictionJoint2D;
}

namespace DT
{
    void FixedUpdateThread();
    
    void Update();
}

#endif