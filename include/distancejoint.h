#ifndef DISTANCEJOINT_H
#define DISTANCEJOINT_H

class DistanceJoint : public BehaviourScript
{
public:
	b2DistanceJoint* joint;
	Rigidbody* rb;

	GameObject* connectedRigidbody = nullptr;
	bool stillCollide = false;

	void Start()
	{
		rb = gameObject->GetComponent<Rigidbody>();
		if(rb == nullptr)
		{
			Debug::LogError("The GameObject needs a Rigidbody component to be able to attach a Joint to.");
			return;
		}
		
		b2DistanceJointDef jointDef;
		jointDef.bodyA = rb->body;
		jointDef.bodyB = connectedRigidbody->GetComponent<Rigidbody>()->body;
		jointDef.collideConnected = stillCollide;

		joint = (b2DistanceJoint*)Physics::physicsWorld.CreateJoint(&jointDef);
	}

	// void Destroy()
 //    {
	// 	Physics::physicsWorld.DestroyJoint(joint);
	// 	if(!destroyed)
 //        {
 //            destroyed = true;
 //        } 
 //        else 
 //        {
 //            Debug::LogError("You cannot delete an already deleted body.");
 //        }
 //        delete this;
 //    }
};

#endif