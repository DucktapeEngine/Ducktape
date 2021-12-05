#include "prismaticjoint.h"
using namespace DT;

void PrismaticJoint2D::Start()
{
	rb = gameObject->GetComponent<Rigidbody2D>();
	if(rb == nullptr)
	{
		Debug::LogError("The GameObject needs a Rigidbody component to be able to attach a Joint to.");
		return;
	}
	
	b2PrismaticJointDef jointDef;
	jointDef.bodyA = rb->body;
	jointDef.bodyB = connectedRigidbody->body;
	jointDef.referenceAngle = referenceAngle;
	jointDef.enableLimit = enableLimit;
	jointDef.lowerTranslation = lowerTranslation;
	jointDef.upperTranslation = upperTranslation;
	jointDef.enableMotor = enableMotor;
	jointDef.motorSpeed = motorSpeed;
	jointDef.maxMotorForce = maxMotorForce;
	jointDef.localAnchorA = rootAnchorPos.ToBox2DVector();
	jointDef.localAnchorB = connectedAnchorPos.ToBox2DVector();

	joint = (b2PrismaticJoint*)Physics::physicsWorld.CreateJoint(&jointDef);
}

void PrismaticJoint2D::Destroy()
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