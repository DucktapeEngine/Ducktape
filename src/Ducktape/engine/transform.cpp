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

#include <Ducktape/engine/transform.h>
using namespace DT;

void Transform::onTransformChange()
{
    Rigidbody2D *rb = entity->getComponent<Rigidbody2D>();
    if (rb != nullptr)
    {
        rb->body->SetTransform((b2Vec2)entity->transform->getPosition(), entity->transform->getRotation());
    }
}

Vector2 Transform::getPosition()
{
    return position;
}

float Transform::getRotation()
{
    return rotation;
}

Vector2 Transform::getScale()
{
    return scale;
}

// local versions of each method

Vector2 Transform::getLocalPosition()
{
    return localPosition;
}

float Transform::getLocalRotation()
{
    return localRotation;
}

Vector2 Transform::getLocalScale()
{
    return localScale;
}

void Transform::recalculateLocalValues()
{
    Vector2 _pos;
    float _rot;
    Vector2 _scl;

    Transform *currentParent = this->parent;

    while (currentParent != nullptr)
    {
        _pos = _pos + currentParent->getLocalPosition();
        _rot = _rot + currentParent->getLocalRotation();
        _scl = _scl + currentParent->getLocalScale();
        currentParent = currentParent->parent;
    }

    localPosition = position - _pos;
    localRotation = rotation - _rot;
    localScale = scale - _scl;
}

void Transform::recalculateWorldValues()
{
    Vector2 _pos;
    float _rot;
    Vector2 _scl;

    Transform *currentParent;

    while (currentParent != nullptr)
    {
        _pos = _pos + currentParent->getLocalPosition();
        _rot = _rot + currentParent->getLocalRotation();
        _scl = _scl + currentParent->getLocalScale();
        currentParent = currentParent->parent;
    }

    position = _pos;
    rotation = _rot;
    scale = _scl;
}

void Transform::setPosition(Vector2 newPosition)
{
    position = newPosition;
    onTransformChange();
    recalculateLocalValues();
}

void Transform::setRotation(float newRotation)
{
    rotation = newRotation;
    onTransformChange();
    recalculateLocalValues();
}

void Transform::setScale(Vector2 newScale)
{
    scale = newScale;
    onTransformChange();
    recalculateLocalValues();
}

void Transform::setLocalPosition(Vector2 newLocalPosition)
{
    position = newLocalPosition;
    onTransformChange();
    recalculateWorldValues();
}

void Transform::setLocalRotation(float newLocalRotation)
{
    rotation = newLocalRotation;
    onTransformChange();
    recalculateWorldValues();
}

void Transform::setLocalScale(Vector2 newLocalScale)
{
    scale = newLocalScale;
    onTransformChange();
    recalculateWorldValues();
}