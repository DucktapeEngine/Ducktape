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

#ifndef DUCKTAPE_H
#define DUCKTAPE_H

/**
 * @brief Including all the ducktape headers.
 */

#include <Ducktape/engine/mathf.h>
#include <Ducktape/engine/vector2.h>
#include <Ducktape/engine/dt_time.h>
#include <Ducktape/engine/color.h>
#include <Ducktape/engine/debug.h>
#include <Ducktape/engine/projectsettings.h>
#include <Ducktape/engine/application.h>

namespace DT
{
    class Entity;
}

#include <Ducktape/physics/collision.h>
#include <Ducktape/engine/behaviourscript.h>
#include <Ducktape/engine/transform.h>
#include <Ducktape/engine/scenemanager.h>
#include <Ducktape/engine/entity.h>
#include <Ducktape/engine/input.h>
#include <Ducktape/rendering/camera.h>
#include <Ducktape/physics/physics.h>
#include <Ducktape/rendering/renderer.h>
#include <Ducktape/rendering/spriterenderer.h>

namespace DT
{
    class RevoluteJoint2D;
    class DistanceJoint2D;
    class FrictionJoint2D;
}

#include <Ducktape/physics/rigidbody.h>
#include <Ducktape/physics/boxcollider.h>
#include <Ducktape/physics/circlecollider.h>
#include <Ducktape/physics/edgecollider.h>
#include <Ducktape/physics/polygoncollider.h>
#include <Ducktape/engine/scene.h>
#include <Ducktape/engine/random.h>
#include <Ducktape/physics/distancejoint.h>
#include <Ducktape/physics/hingejoint.h>
#include <Ducktape/physics/frictionjoint.h>
#include <Ducktape/audio/audiosource.h>

/**
 * @brief Namespace to hold all Ducktape namespaces, classes, functions.
 */
namespace DT
{
    void Init();
}

#endif