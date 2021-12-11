#ifndef GEARJOINT_H
#define GEARJOINT_H

#include "../engine/scripts.h"
#include "external/box2d/include/box2d/box2d.h"
#include "rigidbody.h"
#include "../engine/entity.h"
#include "physics.h"

namespace DT
{
	class GearJoint2D : public PhysicsScript
	{
	public:
		b2GearJoint* joint;
		Rigidbody2D* rb;

		Rigidbody2D* connectedRigidbody = nullptr;
		float maxForce;
		float maxTorque;
		Vector2 rootAnchorPos = Vector2(0.0f, 0.0f);
		Vector2 connectedAnchorPos = Vector2(0.0f, 0.0f);

		void Start();
		
		void Destroy();
	};
}

#endif