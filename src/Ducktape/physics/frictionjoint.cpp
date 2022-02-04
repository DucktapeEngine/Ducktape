/*
MIT License

Copyright (c) 2022 Ducktape

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <Ducktape/physics/frictionjoint.h>
using namespace DT;

void FrictionJoint2D::constructor()
{
	rb = entity->getComponent<Rigidbody2D>();
	if (rb == nullptr)
	{
		rb = entity->addComponent<Rigidbody2D>();
	}

	b2FrictionJointDef jointDef;
	jointDef.bodyA = rb->body;

	joint = (b2FrictionJoint *)Physics::physicsWorld.CreateJoint(&jointDef);
}

void FrictionJoint2D::tick()
{
	if (rb->isDestroyed)
	{
		destroy();
	}
}

void FrictionJoint2D::onDestroy()
{
	Physics::physicsWorld.DestroyJoint(joint);
}

Vector2 FrictionJoint2D::getAnchorA()
{
	return Vector2(joint->GetLocalAnchorA().x, joint->GetLocalAnchorA().y);
}

Vector2 FrictionJoint2D::getAnchorB()
{
	return Vector2(joint->GetLocalAnchorB().x, joint->GetLocalAnchorB().y);
}

Rigidbody2D *FrictionJoint2D::getConnectedRigidbody()
{
	return connectedRigidbody;
}

void FrictionJoint2D::setConnectedRigidbody(Rigidbody2D *rgb)
{
	connectedRigidbody = rb;
	b2FrictionJointDef jointDef;
	jointDef.bodyA = rb->body;
	jointDef.bodyB = rgb->body;

	Physics::physicsWorld.DestroyJoint(joint);
	joint = (b2FrictionJoint *)Physics::physicsWorld.CreateJoint(&jointDef);
}

float FrictionJoint2D::getMaxForce()
{
	return joint->GetMaxForce();
}

void FrictionJoint2D::setMaxForce(float maxForce)
{
	return joint->SetMaxForce(maxForce);
}

float FrictionJoint2D::getMaxTorque()
{
	return joint->GetMaxTorque();
}

void FrictionJoint2D::setMaxTorque(float maxTorque)
{
	return joint->SetMaxTorque(maxTorque);
}