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
#include "physics/hingejoint.h"
#include "physics/frictionjoint.h"
#include "audio/audiosource.h"

namespace DT
{
    void Update();
}

#endif