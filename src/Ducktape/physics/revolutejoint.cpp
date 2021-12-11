#include "revolutejoint.h"
using namespace DT;

void RevoluteJoint2D::Start()
{
	rb = entity->GetComponent<Rigidbody2D>();
	if(rb == nullptr)
	{
		Debug::LogError("The GameObject needs a Rigidbody component to be able to attach a Joint to.");
		return;
	}
	
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = rb->body;
	jointDef.bodyB = connectedRigidbody->body;
	jointDef.referenceAngle = referenceAngle;
	jointDef.enableLimit = enableLimit;
	jointDef.lowerAngle = lowerAngle;
	jointDef.upperAngle = upperAngle;
	jointDef.enableMotor = enableMotor;
	jointDef.motorSpeed = motorSpeed;
	jointDef.maxMotorTorque = maxMotorTorque;
	jointDef.localAnchorA = rootAnchorPos.ToBox2DVector();
	jointDef.localAnchorB = connectedAnchorPos.ToBox2DVector();

	joint = (b2RevoluteJoint*)Physics::physicsWorld.CreateJoint(&jointDef);
}

void RevoluteJoint2D::Destroy()
{
	Physics::physicsWorld.DestroyJoint(joint);
	if(!destroyed)
    {
        destroyed = true;
    } 
    else 
    {
        Debug::LogError("You cannot delete an already deleted body.");
    }
    delete this;
}