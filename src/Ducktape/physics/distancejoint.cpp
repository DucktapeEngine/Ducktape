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

DistanceJoint2D::DistanceJoint2D(Entity* _entity)
{
    entity = _entity;
    rb = entity->GetComponent<Rigidbody2D>();
	if(rb == nullptr)
	{
		rb = entity->AddComponent<Rigidbody2D>();
	}
	
	b2DistanceJointDef jointDef;
	jointDef.bodyA = rb->body;

	joint = (b2DistanceJoint*)Physics::physicsWorld.CreateJoint(&jointDef);
}

void DistanceJoint2D::Update()
{
	if(rb->isDestroyed)
	{
		Destroy();
	}
}

void DistanceJoint2D::OnDestroy()
{
	Physics::physicsWorld.DestroyJoint(joint);
}

Vector2 DistanceJoint2D::GetAnchorA()
{
	return Vector2(joint->GetLocalAnchorA().x, joint->GetLocalAnchorA().y);
}

Vector2 DistanceJoint2D::GetAnchorB()
{
	return Vector2(joint->GetLocalAnchorB().x, joint->GetLocalAnchorB().y);
}

Rigidbody2D* DistanceJoint2D::GetConnectedRigidbody()
{
	return connectedRigidbody;
}

void DistanceJoint2D::SetConnectedRigidbody(Rigidbody2D* rgb)
{
	connectedRigidbody = rb;
	b2DistanceJointDef jointDef;
	jointDef.bodyA = rb->body;
	jointDef.bodyB = rgb->body;

	Physics::physicsWorld.DestroyJoint(joint);
	joint = (b2DistanceJoint*)Physics::physicsWorld.CreateJoint(&jointDef);
}

float DistanceJoint2D::GetLength()
{
	return joint->GetLength();
}

void DistanceJoint2D::SetLength(float length)
{
	joint->SetLength(length);
}

float DistanceJoint2D::GetMinLength()
{
	return joint->GetMinLength();
}

void DistanceJoint2D::SetMinLength(float minLength)
{
	joint->SetMinLength(minLength);
}

float DistanceJoint2D::GetMaxLength()
{
	return joint->GetMaxLength();
}

void DistanceJoint2D::SetMaxLength(float maxLength)
{
	joint->SetMaxLength(maxLength);
}

float DistanceJoint2D::GetCurrentLength()
{
	return joint->GetCurrentLength();
}

float DistanceJoint2D::GetStiffness()
{
	return joint->GetStiffness();
}

void DistanceJoint2D::SetStiffness(float stiffness)
{
	joint->SetStiffness(stiffness);
}

float DistanceJoint2D::GetDamping()
{
	return joint->GetDamping();
}

void DistanceJoint2D::SetDamping(float damping)
{
	joint->SetDamping(damping);
}