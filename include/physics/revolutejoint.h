#ifndef REVOLUTEJOINT_H
#define REVOLUTEJOINT_H

#include "../engine/scripts.h"
#include "external/box2d/include/box2d/box2d.h"
#include "rigidbody.h"
#include "../engine/gameobject.h"
#include "physics.h"

namespace DT
{
	class RevoluteJoint2D : public PhysicsScript
	{
	public:
		b2RevoluteJoint* joint;
		Rigidbody2D* rb;

		Rigidbody2D* connectedRigidbody = nullptr;
		float referenceAngle;
		bool enableLimit;
		float lowerAngle;
		float upperAngle;
		bool enableMotor;
		float motorSpeed;
		float maxMotorTorque;
		Vector2 rootAnchorPos = Vector2(0.0f, 0.0f);
		Vector2 connectedAnchorPos = Vector2(0.0f, 0.0f);

		void Start();

		void Destroy();
	};
}

#endif