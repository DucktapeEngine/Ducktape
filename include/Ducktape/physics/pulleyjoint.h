#ifndef PULLEYJOINT_H
#define PULLEYJOINT_H

#include "../engine/scripts.h"
#include <box2d/box2d.h>
#include "rigidbody.h"
#include "../engine/entity.h"
#include "physics.h"

namespace DT
{
	class PulleyJoint2D : public PhysicsScript
	{
	public:
		b2PulleyJoint* joint;
		Rigidbody2D* rb;

		Rigidbody2D* connectedRigidbody = nullptr;
		Vector2 groundAnchorA;
		Vector2 groundAnchorB;
		float lengthA;
		float lengthB;
		float ratio;
		Vector2 rootAnchorPos = Vector2(0.0f, 0.0f);
		Vector2 connectedAnchorPos = Vector2(0.0f, 0.0f);

		void Start();

		void Destroy();
	};
}

#endif