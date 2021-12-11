#ifndef DISTANCEJOINT2D_H
#define DISTANCEJOINT2D_H

#include "../engine/scripts.h"
#include "external/box2d/include/box2d/box2d.h"
#include "rigidbody.h"
#include "../engine/entity.h"
#include "physics.h"

namespace DT
{
	class DistanceJoint2D : public PhysicsScript
	{
	public:
		b2DistanceJoint* joint;
		Rigidbody2D* rb;

		Rigidbody2D* connectedRigidbody = nullptr;
		bool stillCollide = true;
		float length = 2.0f;
		float minLength = 1.0f;
		float maxLength = 3.0f;
		float stiffness = 0.0f;
		float damping = 1.0f;
		Vector2 rootAnchorPos = Vector2(0.0f, 0.0f);
		Vector2 connectedAnchorPos = Vector2(0.0f, 0.0f);

		void Start();

		void Destroy();
	};
}

#endif