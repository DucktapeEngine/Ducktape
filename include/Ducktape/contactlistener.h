#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

class ContactListener : public b2ContactListener
{
private: 
    void BeginContact(b2Contact* contact)
    {
    	GameObject* bodyA = reinterpret_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	    GameObject* bodyB = reinterpret_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

	    for(BehaviourScript* bs:bodyA->components)
	    {
	    	if(bs != nullptr)
	    	{
		    	bs->OnCollisionEnter(Collision(bodyB));
	    	}
	    }

	    for(BehaviourScript* bs:bodyB->components)
	    {
	    	if(bs != nullptr)
	    	{
		    	bs->OnCollisionEnter(Collision(bodyA));
	    	}
	    }
    }

    void EndContact(b2Contact* contact)
    {

    	GameObject* bodyA = reinterpret_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	    GameObject* bodyB = reinterpret_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

	    for(BehaviourScript* bs:bodyA->components)
	    {
	    	if(bs != nullptr)
	    	{
		    	bs->OnCollisionExit(Collision(bodyB));
	    	}
	    }

	    for(BehaviourScript* bs:bodyB->components)
	    {
	    	if(bs != nullptr)
	    	{
		    	bs->OnCollisionExit(Collision(bodyA));
	    	}
	    }
    }
};

#endif