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
#include <algorithm>

using namespace std::chrono_literals;

#include <box2d/box2d.h>

#include "engine/mathf.h"
#include "engine/vector2.h"
#include "engine/dt_time.h"
#include "engine/color.h"
#include "engine/debug.h"
#include "engine/projectsettings.h"
#include "engine/application.h"

namespace DT
{
    class Entity;
}

#include "physics/collision.h"
#include "engine/behaviourscript.h"
#include "engine/componentexecutionhandler.h"
#include "engine/transform.h"
#include "engine/scenemanager.h"
#include "engine/entity.h"
#include "engine/input.h"
#include "rendering/camera.h"
#include "physics/contactlistener.h"
#include "physics/physics.h"
#include "rendering/renderer.h"
#include "rendering/spriterenderer.h"

namespace DT
{
    class RevoluteJoint2D;
    class DistanceJoint2D;
    class PrismaticJoint2D;
    class WeldJoint2D;
    class PulleyJoint2D;
    class FrictionJoint2D;
}

#include "physics/rigidbody.h"
#include "physics/boxcollider.h"
#include "physics/circlecollider.h"
#include "physics/edgecollider.h"
#include "physics/polygoncollider.h"
#include "engine/scene.h"
#include "engine/random.h"
#include "physics/distancejoint.h"
#include "physics/revolutejoint.h"
#include "physics/prismaticjoint.h"
#include "physics/weldjoint.h"
#include "physics/pulleyjoint.h"
#include "physics/frictionjoint.h"
#include "audio/audioeffects.h"
#include "audio/audiosource.h"

namespace DT
{
    void FixedUpdateThread();

    void Update();
}

#endif