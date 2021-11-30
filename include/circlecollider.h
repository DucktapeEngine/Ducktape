#ifndef CIRCLECOLLIDER2D_H
#define CIRCLECOLLIDER2D_H

class CircleCollider2D : public PhysicsScript
{
public:
    Rigidbody2D* rb;

    float density = 1.0f;
    float friction = 0.3f;
    bool isTrigger = false;
    float radius = 1.0f;
    
    void Start()
    {
        rb = gameObject->GetComponent<Rigidbody2D>();
        if(rb == nullptr)
        {
            Debug::LogError("The GameObject needs a Rigidbody component to be able to attach a Collider.");
            return;
        }

        b2CircleShape circleShape;

        circleShape.m_p.Set(0.0f, 0.0f);
        circleShape.m_radius = radius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;
        fixtureDef.density = density;
        fixtureDef.friction = friction;
        fixtureDef.isSensor = isTrigger;
        
        rb->body->CreateFixture(&fixtureDef);
    }
};

#endif