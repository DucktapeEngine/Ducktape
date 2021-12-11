#include "physics.h"
using namespace DT;

b2Vec2 Physics::b2Gravity(0.0, 0.0);
b2World Physics::physicsWorld(b2Vec2(0.0, 0.0));
int32 Physics::velocityIterations = 6;
int32 Physics::positionIterations = 2;
Vector2 Physics::globalGravity = Vector2(0.0f, 1.0f);
ContactListener Physics::contactListener;

void Physics::Initialize()
{
	globalGravity = ProjectSettings::globalGravity;
	physicsWorld.SetContactListener(&contactListener);
}

Collision Physics::Raycast(Vector2 _origin, Vector2 _direction)
{
	Collision raycastCallback;
	physicsWorld.RayCast(&raycastCallback, _origin.ToBox2DVector(), _direction.ToBox2DVector());
	return raycastCallback;
}