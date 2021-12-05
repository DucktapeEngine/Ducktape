#ifndef COLLISION_H
#define COLLISION_H

#include "external/box2d/include/box2d/box2d.h"
#include "../engine/vector2.h"

namespace DT
{
	class GameObject;

	class Collision : public b2RayCastCallback
	{
	public:
		Vector2 normal;
		GameObject* body;
		Vector2 point;
		float distance;

		float ReportFixture(b2Fixture *_fixture, const b2Vec2 &_point, const b2Vec2 &_normal, float _fraction);
	};
}

#endif