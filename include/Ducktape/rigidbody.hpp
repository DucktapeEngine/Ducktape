#pragma once

class Rigidbody : public BehaviourScript
{
    public:
        Rigidbody()
        {
            ;
            gravityScale = 1.0;
        }

        Vector2 velocity;
        float gravityScale;

        b2Body* groundBody;

        void Start(UpdateEssentials* updateEssentials)
        {
            b2BodyDef groundBodyDef;
            groundBodyDef.position.Set(gameObject->transform->position.x,gameObject->transform->position.y);
            groundBody = updateEssentials->physicsWorld->world->CreateBody(&groundBodyDef);
        }

        void Update(UpdateEssentials* updateEssentials)
        {
            
        }
};
