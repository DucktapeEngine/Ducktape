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

#include <Ducktape/physics/physics.h>
using namespace DT;

b2Vec2 Physics::b2Gravity(0.0, 0.0);
b2World Physics::physicsWorld(b2Vec2(0.0, 0.0));
int32 Physics::velocityIterations = 6;
int32 Physics::positionIterations = 2;
Vector2 Physics::globalGravity = Vector2(0.0f, 1.0f);
// ContactListener Physics::contactListener;

void Physics::initialize()
{
	globalGravity = ProjectSettings::globalGravity;
	// physicsWorld.SetContactListener(&contactListener);
}

Collision Physics::raycast(Vector2 _origin, Vector2 _direction)
{
	Collision raycastCallback;
	physicsWorld.RayCast(&raycastCallback, (b2Vec2)_origin, (b2Vec2)_direction);
	return raycastCallback;
}