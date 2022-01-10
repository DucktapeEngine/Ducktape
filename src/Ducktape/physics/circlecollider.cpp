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

#include <Ducktape/physics/circlecollider.h>
using namespace DT;

CircleCollider2D::CircleCollider2D(Entity* _entity)
{
    entity = _entity;
    rb = entity->GetComponent<Rigidbody2D>();
    if(rb == nullptr)
    {
        rb = entity->AddComponent<Rigidbody2D>();
    }

    b2CircleShape circleShape;

    circleShape.m_p.Set(0.0f, 0.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixture = rb->body->CreateFixture(&fixtureDef);
}

void CircleCollider2D::Update()
{
    if(rb->isDestroyed)
    {
        Destroy();
    }
}

float CircleCollider2D::GetRadius()
{
    return radius;
}

float CircleCollider2D::GetDensity()
{
    return fixture->GetDensity();
}

float CircleCollider2D::GetFriction()
{
    return fixture->GetFriction();
}

bool CircleCollider2D::GetIsTrigger()
{
    return fixture->IsSensor();
}

void CircleCollider2D::SetRadius(float val)
{
    radius = val;
    
    b2CircleShape circleShape;

    circleShape.m_p.Set(0.0f, 0.0f);
    circleShape.m_radius = GetRadius();

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = GetDensity();
    fixtureDef.friction = GetFriction();
    fixtureDef.isSensor = GetIsTrigger();

    rb->body->DestroyFixture(fixture);
    fixture = rb->body->CreateFixture(&fixtureDef);
}

void CircleCollider2D::SetDensity(float val)
{
    fixture->SetDensity(val);
}

void CircleCollider2D::SetFriction(float val)
{
    fixture->SetFriction(val);
}

void CircleCollider2D::SetIsTrigger(bool val)
{
    fixture->SetSensor(val);
}