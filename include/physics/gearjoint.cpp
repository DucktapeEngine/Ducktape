#include "gearjoint.h"
using namespace DT;

void GearJoint2D::Start()
{
	rb = gameObject->GetComponent<Rigidbody2D>();
	if(rb == nullptr)
	{
		Debug::LogError("The GameObject needs a Rigidbody component to be able to attach a Joint to.");
		return;
	}
	
	b2GearJointDef jointDef; // TOFIX 
	// jointDef.bodyA = rb->body;
	// jointDef.bodyB = connectedRigidbody->body;
	// jointDef.maxForce = maxForce;
	// jointDef.maxTorque = maxTorque;
	// jointDef.localAnchorA = rootAnchorPos.ToBox2DVector();
	// jointDef.localAnchorB = connectedAnchorPos.ToBox2DVector();

	joint = (b2GearJoint*)Physics::physicsWorld.CreateJoint(&jointDef);
}

void GearJoint2D::Destroy()
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