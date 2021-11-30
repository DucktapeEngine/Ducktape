#ifndef PULLEYJOINT_H
#define PULLEYJOINT_H

class PulleyJoint2D : public PhysicsScript
{
public:
	b2PulleyJoint* joint;
	Rigidbody2D* rb;

	Rigidbody2D* connectedRigidbody = nullptr;
	Vector2 groundAnchorA;
	Vector2 groundAnchorB;
	float lengthA;
	float lengthB;
	float ratio;
	Vector2 rootAnchorPos = Vector2(0.0f, 0.0f);
	Vector2 connectedAnchorPos = Vector2(0.0f, 0.0f);

	void Start()
	{
		rb = gameObject->GetComponent<Rigidbody2D>();
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