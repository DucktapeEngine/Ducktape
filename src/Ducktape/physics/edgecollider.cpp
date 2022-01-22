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

#include <Ducktape/physics/edgecollider.h>
using namespace DT;

EdgeCollider2D::EdgeCollider2D()
{
    rb = entity->getComponent<Rigidbody2D>();
    if (rb == nullptr)
    {
        rb = entity->addComponent<Rigidbody2D>();
    }

    b2ChainShape chainShape;
    b2EdgeShape edgeShape;

    int size = points.size();

    if (size > 2)
    {
        if (size > 8)
        {
            Debug::logError("The number of vertices in a edgeCollider must be <= 8, the number of vertices chosen is " + std::to_string(size));
            return;
        }

        b2Vec2 vertices[size]; 
        for (int i = 0, n = size; i < n; i++)
        {
            vertices[i].Set(points[i].x, points[i].y);
        }
        chainShape.CreateLoop(vertices, size);
    }
    else
    {
        if (size <= 0)
        {
            Debug::logError("The number of vertices in a edgeCollider must be > 0, the number of vertices chosen is " + std::to_string(size));
            return;
        }

        b2Vec2 vertices[size];
        for (int i = 0, n = size; i < n; i++)
        {
            vertices[i].Set(points[i].x, points[i].y);
        }

        edgeShape.SetTwoSided(vertices[0], vertices[1]);
    }

    b2FixtureDef fixtureDef;
    if (points.size() > 2)
    {
        fixtureDef.shape = &chainShape;
    }
    else
    {
        fixtureDef.shape = &edgeShape;
    }

    rb->body->CreateFixture(&fixtureDef);
}

void EdgeCollider2D::tick()
{
    if (rb->isDestroyed)
    {
        destroy();
    }
}

std::vector<Vector2> EdgeCollider2D::getPoints()
{
    return points;
}

float EdgeCollider2D::getDensity()
{
    return fixture->GetDensity();
}

float EdgeCollider2D::getFriction()
{
    return fixture->GetFriction();
}

bool EdgeCollider2D::getIsTrigger()
{
    return fixture->IsSensor();
}

void EdgeCollider2D::setPoints(std::vector<Vector2> val)
{
    points = val;

    b2ChainShape chainShape;
    b2EdgeShape edgeShape;

    int size = points.size();

    if (size > 2)
    {
        if (size > 8)
        {
            Debug::logError("The number of vertices in a edgeCollider must be <= 8, the number of vertices chosen is " + std::to_string(size));
            return;
        }

        b2Vec2 vertices[size];
        for (int i = 0, n = size; i < n; i++)
        {
            vertices[i].Set(points[i].x, points[i].y);
        }
        chainShape.CreateLoop(vertices, size);
    }
    else
    {
        if (size <= 0)
        {
            Debug::logError("The number of vertices in a edgeCollider must be > 0, the number of vertices chosen is " + std::to_string(size));
            return;
        }

        b2Vec2 vertices[size];
        for (int i = 0, n = size; i < n; i++)
        {
            vertices[i].Set(points[i].x, points[i].y);
        }

        edgeShape.SetTwoSided(vertices[0], vertices[1]);
    }

    b2FixtureDef fixtureDef;
    if (points.size() > 2)
    {
        fixtureDef.shape = &chainShape;
    }
    else
    {
        fixtureDef.shape = &edgeShape;
    }

    rb->body->CreateFixture(&fixtureDef);
}

void EdgeCollider2D::setDensity(float val)
{
    fixture->SetDensity(val);
}

void EdgeCollider2D::setFriction(float val)
{
    fixture->SetFriction(val);
}

void EdgeCollider2D::setIsTrigger(bool val)
{
    fixture->SetSensor(val);
}