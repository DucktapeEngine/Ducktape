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

Rigidbody2D::Rigidbody2D()
{
    b2BodyDef bodyDef;
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(entity);

    bodyDef.type = b2_dynamicBody;
    body = Physics::physicsWorld.CreateBody(&bodyDef);
}

void Rigidbody2D::tick()
{
    entity->transform->setPosition(Vector2(body->GetPosition().x, body->GetPosition().y));
    entity->transform->setRotation(body->GetAngle());
    setVelocity(Vector2(body->GetLinearVelocity().x, body->GetLinearVelocity().y) + Physics::globalGravity * getGravityScale());
}

Vector2 Rigidbody2D::getVelocity()
{
    return Vector2(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
}

void Rigidbody2D::setVelocity(Vector2 val)
{
    body->SetLinearVelocity((b2Vec2)val);
}

float Rigidbody2D::getAngularVelocity()
{
    return body->GetAngularVelocity();
}

void Rigidbody2D::setAngularVelocity(float val)
{
    body->SetAngularVelocity(val);
}

float Rigidbody2D::getMass()
{
    return body->GetMass();
}

void Rigidbody2D::setMass(float mass)
{
    b2MassData *data;
    body->GetMassData(data);
    data->mass = mass;
    body->SetMassData(data);
}

void Rigidbody2D::setCenterOfMass(Vector2 center)
{
    b2MassData *data;
    body->GetMassData(data);
    data->center = (b2Vec2)center;
    body->SetMassData(data);
}

float Rigidbody2D::getInertia()
{
    return body->GetInertia();
}

float Rigidbody2D::getDamping()
{
    return body->GetLinearDamping();
}

void Rigidbody2D::setDamping(float damping)
{
    body->SetLinearDamping(damping);
}

float Rigidbody2D::getAngularDamping()
{
    return body->GetAngularDamping();
}

void Rigidbody2D::setAngularDamping(float damping)
{
    body->SetAngularDamping(damping);
}

float Rigidbody2D::getGravityScale()
{
    return gravityScale;
}

void Rigidbody2D::setGravityScale(float scale)
{
    gravityScale = scale;
}

BodyType Rigidbody2D::getType()
{
    b2BodyType type = body->GetType();
    if (type == 0)
    {
        return BodyType::staticBody;
    }
    else if (type == 1)
    {
        return BodyType::kinematicBody;
    }
    return BodyType::dynamicBody;
}

void Rigidbody2D::setType(BodyType type)
{
    if (type == 0)
    {
        body->SetType(b2_staticBody);
    }
    else if (type == 1)
    {
        body->SetType(b2_kinematicBody);
    }
    else
    {
        body->SetType(b2_dynamicBody);
    }
}

bool Rigidbody2D::getContinous()
{
    return body->IsBullet();
}

void Rigidbody2D::setContinous(bool flag)
{
    body->SetBullet(flag);
}

bool Rigidbody2D::getSleepingAllowed()
{
    return body->IsSleepingAllowed();
}

void Rigidbody2D::setSleepingAllowed(bool flag)
{
    body->SetSleepingAllowed(flag);
}

bool Rigidbody2D::getAwake()
{
    return body->IsAwake();
}

void Rigidbody2D::setAwake(bool flag)
{
    body->SetAwake(flag);
}

bool Rigidbody2D::getFixedRotation()
{
    return body->IsFixedRotation();
}

void Rigidbody2D::setFixedRotation(bool flag)
{
    body->SetFixedRotation(flag);
}

void Rigidbody2D::applyForce(Vector2 force)
{
    body->ApplyForceToCenter((b2Vec2)force, true);
}

void Rigidbody2D::applyForceAtPoint(Vector2 force, Vector2 point)
{
    body->ApplyForce((b2Vec2)force, (b2Vec2)point, true);
}

void Rigidbody2D::applyTorque(float torque)
{
    body->ApplyTorque(torque, true);
}

void Rigidbody2D::applyLinearImpulse(Vector2 impulse)
{
    body->ApplyLinearImpulseToCenter((b2Vec2)impulse, true);
}

void Rigidbody2D::applyLinearImpulseAtPoint(Vector2 impulse, Vector2 point)
{
    body->ApplyLinearImpulse((b2Vec2)impulse, (b2Vec2)point, true);
}

void Rigidbody2D::applyAngularImpulse(float impulse)
{
    body->ApplyAngularImpulse(impulse, true);
}

void Rigidbody2D::onDestroy()
{
    Physics::physicsWorld.DestroyBody(body);
    body = nullptr;
}