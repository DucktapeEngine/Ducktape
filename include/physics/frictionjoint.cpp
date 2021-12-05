#include "frictionjoint.h"
using namespace DT;

void FrictionJoint2D::Start()
{
	rb = gameObject->GetComponent<Rigidbody2D>();
	if(rb == nullptr)
	{
		Debug::LogError("The GameObject needs a Rigidbody component to be able to attach a Joint to.");
		return;
	}
	
	b2FrictionJointDef jointDef;
	jointDef.bodyA = rb->body;
	jointDef.bodyB = connectedRigidbody->body;
	jointDef.maxForce = maxForce;
	jointDef.maxTorque = maxTorque;
	jointDef.localAnchorA = rootAnchorPos.ToBox2DVector();
	jointDef.localAnchorB = connectedAnchorPos.ToBox2DVector();

	joint = (b2FrictionJoint*)Physics::physicsWorld.CreateJoint(&jointDef);
}

void FrictionJoint2D::Destroy()
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