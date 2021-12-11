#include "circlecollider.h"
using namespace DT;

void CircleCollider2D::Start()
{
    rb = entity->GetComponent<Rigidbody2D>();
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