#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

class BoxCollider : public BehaviourScript
{
public:
    Rigidbody* rb;

    Vector2 scale = Vector2(1.0f, 1.0f);
    float density = 1.0f;
    float friction = 0.3f;
    bool isTrigger = false;
    
    void Start()
    {
        rb = gameObject->GetComponent<Rigidbody>();

        b2PolygonShape collisionShape;
        collisionShape.SetAsBox(scale.x * gameObject->transform->GetScale().x, scale.y * gameObject->transform->GetScale().y);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &collisionShape;
        fixtureDef.density = density;
        fixtureDef.friction = friction;
        fixtureDef.isSensor = isTrigger;
        
        rb->body->CreateFixture(&fixtureDef);
    }
};

#endif