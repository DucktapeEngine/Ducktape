#ifndef REVOLUTEJOINT_H
#define REVOLUTEJOINT_H

class RevoluteJoint2D : public PhysicsScript
{
public:
	b2RevoluteJoint* joint;
	Rigidbody2D* rb;

	Rigidbody2D* connectedRigidbody = nullptr;
	float referenceAngle;
	bool enableLimit;
	float lowerAngle;
	float upperAngle;
	bool enableMotor;
	float motorSpeed;
	float maxMotorTorque;
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