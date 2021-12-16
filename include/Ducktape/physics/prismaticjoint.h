#ifndef PRISMATICJOINT_H
#define PRISMATICJOINT_H

#include "../engine/scripts.h"
#include <box2d/box2d.h>
#include "rigidbody.h"
#include "../engine/entity.h"
#include "physics.h"

namespace DT
{
	class PrismaticJoint2D : public PhysicsScript
	{
	public:
		b2PrismaticJoint* joint;
		Rigidbody2D* rb;

		Rigidbody2D* connectedRigidbody = nullptr;
		float referenceAngle;
		bool enableLimit;
		float lowerTranslation;
		float upperTranslation;
		bool enableMotor;
		float motorSpeed;
		float maxMotorForce;
		Vector2 rootAnchorPos = Vector2(0.0f, 0.0f);
		Vector2 connectedAnchorPos = Vector2(0.0f, 0.0f);

		void Start();

		void Destroy();
	};
}

#endif