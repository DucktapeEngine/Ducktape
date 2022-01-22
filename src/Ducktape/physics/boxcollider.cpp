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

#include <Ducktape/physics/boxcollider.h>
using namespace DT;

BoxCollider2D::BoxCollider2D()
{
    rb = entity->getComponent<Rigidbody2D>();
    if (rb == nullptr)
    {
        rb = entity->addComponent<Rigidbody2D>();
    }

    b2PolygonShape collisionShape;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &collisionShape;
    fixture = rb->body->CreateFixture(&fixtureDef);
}

void BoxCollider2D::tick()
{
    if (rb->isDestroyed)
    {
        destroy();
    }
}

Vector2 BoxCollider2D::getScale()
{
    return scale;
}

float BoxCollider2D::getDensity()
{
    return fixture->GetDensity();
}

float BoxCollider2D::getFriction()
{
    return fixture->GetFriction();
}

bool BoxCollider2D::getIsTrigger()
{
    return fixture->IsSensor();
}

void BoxCollider2D::setScale(Vector2 val)
{
    scale = val;

    b2PolygonShape collisionShape;
    collisionShape.SetAsBox(getScale().x * entity->transform->getScale().x, getScale().y * entity->transform->getScale().y);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &collisionShape;
    fixtureDef.density = getDensity();
    fixtureDef.friction = getFriction();
    fixtureDef.isSensor = getIsTrigger();

    rb->body->DestroyFixture(fixture);
    fixture = rb->body->CreateFixture(&fixtureDef);
}

void BoxCollider2D::setDensity(float val)
{
    fixture->SetDensity(val);
}

void BoxCollider2D::setFriction(float val)
{
    fixture->SetFriction(val);
}

void BoxCollider2D::setIsTrigger(bool val)
{
    fixture->SetSensor(val);
}