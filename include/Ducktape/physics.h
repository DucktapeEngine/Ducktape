#ifndef PHYSICS_H
#define PHYSICS_H

namespace Physics
{
	b2Vec2 b2Gravity(0.0, 0.0);
	b2World physicsWorld(b2Vec2(0.0, 0.0));
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	Vector2 globalGravity = Vector2(0.0f, 1.0f);
	ContactListener contactListener;

	void Initialize()
	{
		globalGravity = ProjectSettings::globalGravity;
		physicsWorld.SetContactListener(&contactListener);
	}
};

#endif