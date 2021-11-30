#ifndef BOXCOLLIDER2D_H
#define BOXCOLLIDER2D_H

class BoxCollider2D : public PhysicsScript
{
public:
    Rigidbody2D* rb;

    Vector2 scale = Vector2(1.0f, 1.0f);
    float density = 1.0f;
    float friction = 0.3f;
    bool isTrigger = false;
    
    void Start()
    {
        rb = gameObject->GetComponent<Rigidbody2D>();
        if(rb == nullptr)
        {
            Debug::LogError("The GameObject needs a Rigidbody component to be able to attach a Collider to.");
            return;
        }

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