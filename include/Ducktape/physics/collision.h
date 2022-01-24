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

#ifndef COLLISION_H
#define COLLISION_H

#include <box2d/box2d.h>
#include <Ducktape/engine/vector2.h>

namespace DT
{
	class Entity;

	class Collision : public b2RayCastCallback
	{
	public:
		/**
		 * @brief The direction the collision is pointing towards.
		 */
		Vector2 normal;

		/**
		 * @brief The point of collision.
		 */
		Vector2 point;

		/**
		 * @brief The body that was collided with.
		 */
		Entity *body;

		float ReportFixture(b2Fixture *_fixture, const b2Vec2 &_point, const b2Vec2 &_normal, float _fraction);
	};
}

#endif