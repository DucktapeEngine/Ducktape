#include "distancejoint.h"
using namespace DT;

void DistanceJoint2D::Start()
{
	rb = entity->GetComponent<Rigidbody2D>();
	if(rb == nullptr)
	{
		Debug::LogError("The GameObject needs a Rigidbody component to be able to attach a Joint to.");
		return;
	}
	
	b2DistanceJointDef jointDef;
	jointDef.bodyA = rb->body;
	jointDef.bodyB = connectedRigidbody->body;
	jointDef.collideConnected = stillCollide;
	jointDef.length = length;
	jointDef.minLength = minLength;
	jointDef.maxLength = maxLength;
	jointDef.stiffness = stiffness;
	jointDef.damping = damping;
	jointDef.localAnchorA = rootAnchorPos.ToBox2DVector();
	jointDef.localAnchorB = connectedAnchorPos.ToBox2DVector();

	joint = (b2DistanceJoint*)Physics::physicsWorld.CreateJoint(&jointDef);
}

void DistanceJoint2D::Destroy()
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