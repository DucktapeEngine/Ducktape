#include "rigidbody.hpp"
#include "physics.hpp"

void Rigidbody::Start()
{
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(gameObject->transform->position.x,gameObject->transform->position.y);

    if(type == "static")
    {
        body = Physics::physicsWorld.CreateBody(&groundBodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(scale.x * gameObject->transform->scale.x, scale.y * gameObject->transform->scale.y);

        body->CreateFixture(&dynamicBox, 0.01);
        body->SetAwake(true);
    }
    else if(type == "dynamic")
    {
        b2BodyDef groundBodyDef;
        groundBodyDef.type = b2_dynamicBody;
        groundBodyDef.position.Set(gameObject->transform->position.x, gameObject->transform->position.y);
        
        body = Physics::physicsWorld.CreateBody(&groundBodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(scale.x * gameObject->transform->scale.x, scale.y * gameObject->transform->scale.y);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.isSensor = isTrigger;

        body->CreateFixture(&fixtureDef);
        body->SetAwake(true);
    }
}

void Rigidbody::Update()
{
    velocity = Vector2(body->GetLinearVelocity().x, body->GetLinearVelocity().y) + Physics::globalGravity;
}

void Rigidbody::MidUpdate()
{
    body->SetTransform(b2Vec2(gameObject->transform->position.x, gameObject->transform->position.y), gameObject->transform->rotation);
    body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

void Rigidbody::LateUpdate()
{
    gameObject->transform->position = Vector2(body->GetPosition().x, body->GetPosition().y);
    gameObject->transform->rotation = body->GetAngle();
    velocity = Vector2(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
}