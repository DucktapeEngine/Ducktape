#ifndef PRISMATIC_JOINT_H
#define PRISMATIC_JOINT_H

class PrismaticJoint : public PhysicsScript
{
public:
	b2PrismaticJoint* joint;
	Rigidbody* rb;

	Rigidbody* connectedRigidbody = nullptr;
	float referenceAngle;
	bool enableLimit;
	float lowerTranslation;
	float upperTranslation;
	bool enableMotor;
	float motorSpeed;
	float maxMotorForce;
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