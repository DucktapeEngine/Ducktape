/*
MIT License

Copyright (c) 2022 Ducktape

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <Ducktape/physics/rigidbody.h>
using namespace DT;

Rigidbody2D::Rigidbody2D(Entity* _entity)
{
    entity = _entity;
    b2BodyDef bodyDef;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(entity);

    bodyDef.type = b2_dynamicBody;
    body = Physics::physicsWorld.CreateBody(&bodyDef);
}

void Rigidbody2D::Update()
{
    entity->transform->SetPosition(Vector2(body->GetPosition().x, body->GetPosition().y));
    entity->transform->SetRotation(body->GetAngle());
    SetVelocity(Vector2(body->GetLinearVelocity().x, body->GetLinearVelocity().y) + Physics::globalGravity * GetGravityScale());
}

Vector2 Rigidbody2D::GetVelocity()
{
    return Vector2(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
}

void Rigidbody2D::SetVelocity(Vector2 val)
{
    body->SetLinearVelocity(val.ToBox2DVector());
}

float Rigidbody2D::GetAngularVelocity()
{
    return body->GetAngularVelocity();
}

void Rigidbody2D::SetAngularVelocity(float val)
{
    body->SetAngularVelocity(val);
}

float Rigidbody2D::GetMass()
{
    return body->GetMass();
}

void Rigidbody2D::SetMass(float mass)
{
    b2MassData* data;
    body->GetMassData(data);
    data->mass = mass;
    body->SetMassData(data);
}

void Rigidbody2D::SetCenterOfMass(Vector2 center)
{
    b2MassData* data;
    body->GetMassData(data);
    data->center = center.ToBox2DVector();
    body->SetMassData(data);
}

float Rigidbody2D::GetInertia()
{
    return body->GetInertia();
}

float Rigidbody2D::GetDamping()
{
    return body->GetLinearDamping();
}

void Rigidbody2D::SetDamping(float damping)
{
    body->SetLinearDamping(damping);
}

float Rigidbody2D::GetAngularDamping()
{
    return body->GetAngularDamping();
}

void Rigidbody2D::SetAngularDamping(float damping)
{
    body->SetAngularDamping(damping);
}

float Rigidbody2D::GetGravityScale()
{
    return gravityScale;
}

void Rigidbody2D::SetGravityScale(float scale)
{
    gravityScale = scale;
}

BodyType Rigidbody2D::GetType()
{
    b2BodyType type = body->GetType();
    if(type == 0)
    {
        return BodyType::staticBody;
    } 
    else if(type == 1)
    {
        return BodyType::kinematicBody;
    }
    return BodyType::dynamicBody;
}

void Rigidbody2D::SetType(BodyType type)
{
    if(type == 0)
    {
        body->SetType(b2_staticBody);
    } 
    else if(type == 1)
    {
        body->SetType(b2_kinematicBody);
    }
    else
    {
        body->SetType(b2_dynamicBody);
    }
}

bool Rigidbody2D::GetContinous()
{
    return body->IsBullet();
}

void Rigidbody2D::SetContinous(bool flag)
{
    body->SetBullet(flag);
}

bool Rigidbody2D::GetSleepingAllowed()
{
    return body->IsSleepingAllowed();
}

void Rigidbody2D::SetSleepingAllowed(bool flag)
{
    body->SetSleepingAllowed(flag);
}

bool Rigidbody2D::GetAwake()
{
    return body->IsAwake();
}

void Rigidbody2D::SetAwake(bool flag)
{
    body->SetAwake(flag);
}

bool Rigidbody2D::GetFixedRotation()
{
    return body->IsFixedRotation();
}

void Rigidbody2D::SetFixedRotation(bool flag)
{
    body->SetFixedRotation(flag);
}

void Rigidbody2D::ApplyForce(Vector2 force)
{
    body->ApplyForceToCenter(force.ToBox2DVector(), true);
}

void Rigidbody2D::ApplyForceAtPoint(Vector2 force, Vector2 point)
{
    body->ApplyForce(force.ToBox2DVector(), point.ToBox2DVector(), true);
}

void Rigidbody2D::ApplyTorque(float torque)
{
    body->ApplyTorque(torque, true);
}

void Rigidbody2D::ApplyLinearImpulse(Vector2 impulse)
{
    body->ApplyLinearImpulseToCenter(impulse.ToBox2DVector(), true);
}

void Rigidbody2D::ApplyLinearImpulseAtPoint(Vector2 impulse, Vector2 point)
{
    body->ApplyLinearImpulse(impulse.ToBox2DVector(), point.ToBox2DVector(), true);
}

void Rigidbody2D::ApplyAngularImpulse(float impulse)
{
    body->ApplyAngularImpulse(impulse, true);
}

void Rigidbody2D::Destroy()
{
    Physics::physicsWorld.DestroyBody(body);
    body = nullptr;
}