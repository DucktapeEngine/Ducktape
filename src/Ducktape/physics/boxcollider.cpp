#include "boxcollider.h"
using namespace DT;

void BoxCollider2D::Start()
{
    rb = entity->GetComponent<Rigidbody2D>();
    if(rb == nullptr)
    {
        Debug::LogError("The GameObject needs a Rigidbody component to be able to attach a Collider to.");
        return;
    }

    b2PolygonShape collisionShape;
    collisionShape.SetAsBox(scale.x * entity->transform->GetScale().x, scale.y * entity->transform->GetScale().y);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &collisionShape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.isSensor = isTrigger;
    
    rb->body->CreateFixture(&fixtureDef);
}