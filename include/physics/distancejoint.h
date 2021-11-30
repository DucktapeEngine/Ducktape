#ifndef DISTANCEJOINT2D_H
#define DISTANCEJOINT2D_H

class DistanceJoint2D : public PhysicsScript
{
public:
	b2DistanceJoint* joint;
	Rigidbody2D* rb;

	Rigidbody2D* connectedRigidbody = nullptr;
	bool stillCollide = true;
	float length = 2.0f;
	float minLength = 1.0f;
	float maxLength = 3.0f;
	float stiffness = 0.0f;
	float damping = 1.0f;
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