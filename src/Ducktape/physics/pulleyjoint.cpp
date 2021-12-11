#include "pulleyjoint.h"
using namespace DT;

void PulleyJoint2D::Start()
{
	rb = entity->GetComponent<Rigidbody2D>();
	if(rb == nullptr)
	{
		Debug::LogError("The GameObject needs a Rigidbody component to be able to attach a Joint to.");
		return;
	}
	
	b2PulleyJointDef jointDef;
	jointDef.bodyA = rb->body;
	jointDef.bodyB = connectedRigidbody->body;
	jointDef.groundAnchorA = groundAnchorA.ToBox2DVector();
	jointDef.groundAnchorB = groundAnchorB.ToBox2DVector();
	jointDef.lengthA = lengthA;
	jointDef.lengthB = lengthB;
	jointDef.ratio = ratio;
	jointDef.localAnchorA = rootAnchorPos.ToBox2DVector();
	jointDef.localAnchorB = connectedAnchorPos.ToBox2DVector();

	joint = (b2PulleyJoint*)Physics::physicsWorld.CreateJoint(&jointDef);
}

void PulleyJoint2D::Destroy()
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