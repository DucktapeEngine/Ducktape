#ifndef FRICTIONJOINT2D_H
#define FRICTIONJOINT2D_H

#include "../engine/scripts.h"
#include "external/box2d/include/box2d/box2d.h"
#include "rigidbody.h"
#include "../engine/gameobject.h"
#include "physics.h"

namespace DT
{
	class FrictionJoint2D : public PhysicsScript
	{
	public:
		b2FrictionJoint* joint;
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