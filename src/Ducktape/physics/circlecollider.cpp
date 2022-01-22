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

CircleCollider2D::CircleCollider2D()
{
    rb = entity->getComponent<Rigidbody2D>();
    if (rb == nullptr)
    {
        rb = entity->addComponent<Rigidbody2D>();
    }

    b2CircleShape circleShape;

    circleShape.m_p.Set(0.0f, 0.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixture = rb->body->CreateFixture(&fixtureDef);
}

void CircleCollider2D::tick()
{
    if (rb->isDestroyed)
    {
        destroy();
    }
}

float CircleCollider2D::getRadius()
{
    return radius;
}

float CircleCollider2D::getDensity()
{
    return fixture->GetDensity();
}

float CircleCollider2D::getFriction()
{
    return fixture->GetFriction();
}

bool CircleCollider2D::getIsTrigger()
{
    return fixture->IsSensor();
}

void CircleCollider2D::setRadius(float val)
{
    radius = val;

    b2CircleShape circleShape;

    circleShape.m_p.Set(0.0f, 0.0f);
    circleShape.m_radius = getRadius();

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = getDensity();
    fixtureDef.friction = getFriction();
    fixtureDef.isSensor = getIsTrigger();

    rb->body->DestroyFixture(fixture);
    fixture = rb->body->CreateFixture(&fixtureDef);
}

void CircleCollider2D::setDensity(float val)
{
    fixture->SetDensity(val);
}

void CircleCollider2D::setFriction(float val)
{
    fixture->SetFriction(val);
}

void CircleCollider2D::setIsTrigger(bool val)
{
    fixture->SetSensor(val);
}