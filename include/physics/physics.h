#ifndef PHYSICS_H
#define PHYSICS_H

#include "contactlistener.h"
#include "../engine/projectsettings.h"

namespace DT
{
	namespace Physics
	{
		extern b2Vec2 b2Gravity;
		extern b2World physicsWorld;
		extern int32 velocityIterations;
		extern int32 positionIterations;
		extern Vector2 globalGravity;
		extern ContactListener contactListener;

		void Initialize();

		Collision Raycast(Vector2 _origin, Vector2 _direction);
	};
}

#endif