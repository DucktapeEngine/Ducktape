#include "rigidbody.h"
using namespace DT;

void Rigidbody2D::Start()
{
    b2BodyDef bodyDef;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(entity);
    bodyDef.position.Set(entity->transform->GetPosition().x, entity->transform->GetPosition().y);

    if(type == "dynamic")
    {
        bodyDef.type = b2_dynamicBody;
    } 
    else if(type == "kinematic")
    {
        bodyDef.type = b2_kinematicBody;
    }
    else
    {
        bodyDef.type = b2_staticBody;
    }
    body = Physics::physicsWorld.CreateBody(&bodyDef);
    
    body->SetAwake(true);

    body->SetLinearDamping(linearDamping);
    body->SetAngularDamping(angularDamping);
    body->SetSleepingAllowed(allowSleep);
    body->SetBullet(continousCollision);
}

void Rigidbody2D::Update()
{
    entity->transform->SetPosition(Vector2(body->GetPosition().x, body->GetPosition().y));
    entity->transform->SetRotation(body->GetAngle());
    SetVelocity(Vector2(body->GetLinearVelocity().x, body->GetLinearVelocity().y) + Physics::globalGravity * gravityScale);
}

void Rigidbody2D::OnTransformChange()
{
    body->SetTransform(b2Vec2(entity->transform->GetPosition().x, entity->transform->GetPosition().y), entity->transform->GetRotation());
}

Vector2 Rigidbody2D::GetVelocity()
{
    return Vector2(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
}

Vector2 Rigidbody2D::SetVelocity(Vector2 _vel)
{
    body->SetLinearVelocity(b2Vec2(_vel.x, _vel.y));
    return _vel;
}

void Rigidbody2D::AddForce(Vector2 direction)
{
    body->ApplyForceToCenter(direction.ToBox2DVector(), true);
}

void Rigidbody2D::AddForceAtPoint(Vector2 direction, Vector2 point)
{
    body->ApplyForce(direction.ToBox2DVector(), point.ToBox2DVector(), true);
}

void Rigidbody2D::AddTorque(float torque)
{
    body->ApplyTorque(torque, true);
}

void Rigidbody2D::Destroy()
{
    PhysicsScript ps;
    if(body != nullptr && !destroyed)
    {
        for(BehaviourScript* bs:entity->components)
        {
            bs->OnRBDestroy();
        }

        Physics::physicsWorld.DestroyBody(body);
        destroyed = true;
        body = nullptr;
    } 
    else 
    {
        Debug::LogError("You cannot delete an already deleted body.");
    }
    delete this;
}