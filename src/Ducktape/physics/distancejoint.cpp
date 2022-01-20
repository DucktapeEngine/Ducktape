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

#include <Ducktape/physics/distancejoint.h>
using namespace DT;

DistanceJoint2D::DistanceJoint2D(Entity *_entity)
{
	entity = _entity;
	rb = entity->getComponent<Rigidbody2D>();
	if (rb == nullptr)
	{
		rb = entity->addComponent<Rigidbody2D>();
	}

	b2DistanceJointDef jointDef;
	jointDef.bodyA = rb->body;

	joint = (b2DistanceJoint *)Physics::physicsWorld.CreateJoint(&jointDef);
}

void DistanceJoint2D::tick()
{
	if (rb->isDestroyed)
	{
		destroy();
	}
}

void DistanceJoint2D::onDestroy()
{
	Physics::physicsWorld.DestroyJoint(joint);
}

Vector2 DistanceJoint2D::getAnchorA()
{
	return Vector2(joint->GetLocalAnchorA().x, joint->GetLocalAnchorA().y);
}

Vector2 DistanceJoint2D::getAnchorB()
{
	return Vector2(joint->GetLocalAnchorB().x, joint->GetLocalAnchorB().y);
}

Rigidbody2D *DistanceJoint2D::getConnectedRigidbody()
{
	return connectedRigidbody;
}

void DistanceJoint2D::setConnectedRigidbody(Rigidbody2D *rgb)
{
	connectedRigidbody = rb;
	b2DistanceJointDef jointDef;
	jointDef.bodyA = rb->body;
	jointDef.bodyB = rgb->body;

	Physics::physicsWorld.DestroyJoint(joint);
	joint = (b2DistanceJoint *)Physics::physicsWorld.CreateJoint(&jointDef);
}

float DistanceJoint2D::getLength()
{
	return joint->GetLength();
}

void DistanceJoint2D::setLength(float length)
{
	joint->SetLength(length);
}

float DistanceJoint2D::getMinLength()
{
	return joint->GetMinLength();
}

void DistanceJoint2D::setMinLength(float minLength)
{
	joint->SetMinLength(minLength);
}

float DistanceJoint2D::getMaxLength()
{
	return joint->GetMaxLength();
}

void DistanceJoint2D::setMaxLength(float maxLength)
{
	joint->SetMaxLength(maxLength);
}

float DistanceJoint2D::getCurrentLength()
{
	return joint->GetCurrentLength();
}

float DistanceJoint2D::getStiffness()
{
	return joint->GetStiffness();
}

void DistanceJoint2D::setStiffness(float stiffness)
{
	joint->SetStiffness(stiffness);
}

float DistanceJoint2D::getDamping()
{
	return joint->GetDamping();
}

void DistanceJoint2D::setDamping(float damping)
{
	joint->SetDamping(damping);
}