#ifndef GEARJOINT_H
#define GEARJOINT_H

class GearJoint2D : public PhysicsScript
{
public:
	b2GearJoint* joint;
	Rigidbody* rb;

	Rigidbody* connectedRigidbody = nullptr;
	float maxForce;
	float maxTorque;
	Vector2 rootAnchorPos = Vector2(0.0f, 0.0f);
	Vector2 connectedAnchorPos = Vector2(0.0f, 0.0f);

	void Start()
	{
		rb = gameObject->GetComponent<Rigidbody>();
		if(rb == nullptr)
		{
			Debug::LogError("The GameObject needs a Rigidbody component to be able to attach a Joint to.");
			return;
		}
		
		b2GearJointDef jointDef;
		jointDef.bodyA = rb->body;
		jointDef.bodyB = connectedRigidbody->body;
		jointDef.maxForce = maxForce;
		jointDef.maxTorque = maxTorque;
		jointDef.localAnchorA = rootAnchorPos.ToBox2DVector();
		jointDef.localAnchorB = connectedAnchorPos.ToBox2DVector();

		joint = (b2GearJoint*)Physics::physicsWorld.CreateJoint(&jointDef);
	}

	void Destroy()
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
};

#endif