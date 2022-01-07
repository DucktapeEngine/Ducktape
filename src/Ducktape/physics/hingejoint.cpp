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

#include <Ducktape/physics/hingejoint.h>
using namespace DT;

HingeJoint2D::HingeJoint2D()
{
   rb = entity->GetComponent<Rigidbody2D>();
	if(rb == nullptr)
	{
		rb = entity->AddComponent<Rigidbody2D>();
	}
	
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = rb->body;

	joint = (b2RevoluteJoint*)Physics::physicsWorld.CreateJoint(&jointDef);
}

void HingeJoint2D::OnDestroy()
{
	Physics::physicsWorld.DestroyJoint(joint);
}

Vector2 HingeJoint2D::GetAnchorA()
{
	return Vector2(joint->GetLocalAnchorA().x, joint->GetLocalAnchorA().y);
}

Vector2 HingeJoint2D::GetAnchorB()
{
	return Vector2(joint->GetLocalAnchorB().x, joint->GetLocalAnchorB().y);
}

Rigidbody2D* HingeJoint2D::GetConnectedRigidbody()
{
	return connectedRigidbody;
}

void HingeJoint2D::SetConnectedRigidbody(Rigidbody2D* rgb)
{
	connectedRigidbody = rb;
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = rb->body;
	jointDef.bodyB = rgb->body;

	Physics::physicsWorld.DestroyJoint(joint);
	joint = (b2RevoluteJoint*)Physics::physicsWorld.CreateJoint(&jointDef);
}

float HingeJoint2D::GetReferenceAngle()
{
	return joint->GetReferenceAngle();
}

float HingeJoint2D::GetJointAngle()
{
	return joint->GetJointAngle();
}

float HingeJoint2D::GetJointSpeed()
{
	return joint->GetJointSpeed();
}

bool HingeJoint2D::GetLimitEnabled()
{
	return joint->IsLimitEnabled();
}

void HingeJoint2D::SetLimitEnabled(bool flag)
{
	joint->EnableLimit(flag);
}

float HingeJoint2D::GetLowerLimit()
{
	return joint->GetLowerLimit();
}

float HingeJoint2D::GetUpperLimit()
{
	return joint->GetUpperLimit();
}

void HingeJoint2D::SetLowerLimit(float val)
{
	joint->SetLimits(val, GetUpperLimit());
}

void HingeJoint2D::SetHigherLimit(float val)
{
	joint->SetLimits(GetLowerLimit(), val);
}

bool HingeJoint2D::GetMotorEnabled()
{
	return joint->IsMotorEnabled();
}

void HingeJoint2D::SetMotorEnabled(bool flag)
{
	joint->EnableMotor(flag);
}

void HingeJoint2D::SetMotorSpeed(float speed)
{
	joint->SetMotorSpeed(speed);
}

float HingeJoint2D::GetMotorSpeed()
{
	return joint->GetMotorSpeed();
}

void HingeJoint2D::SetMaxMotorTorque(float torque)
{
	joint->SetMaxMotorTorque(torque);
}

float HingeJoint2D::GetMaxMotorTorque()
{
	return joint->GetMaxMotorTorque();
}