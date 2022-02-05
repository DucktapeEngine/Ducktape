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

void Transform::OnTransformChange()
{
    Rigidbody2D *rb = entity->GetComponent<Rigidbody2D>();
    if (rb != nullptr)
    {
        rb->body->SetTransform((b2Vec2)entity->transform->SetPosition(), entity->transform->GetRotation());
    }
}

Vector2 Transform::SetPosition()
{
    return position;
}

float Transform::GetRotation()
{
    return rotation;
}

Vector2 Transform::GetScale()
{
    return scale;
}

// local versions of each method

Vector2 Transform::GetLocalPosition()
{
    return localPosition;
}

float Transform::GetLocalRotation()
{
    return localRotation;
}

Vector2 Transform::GetLocalScale()
{
    return localScale;
}

void Transform::RecalculateLocalValues()
{
    Vector2 _pos;
    float _rot;
    Vector2 _scl;

    Transform *currentParent = this->parent;

    while (currentParent != nullptr)
    {
        _pos = _pos + currentParent->GetLocalPosition();
        _rot = _rot + currentParent->GetLocalRotation();
        _scl = _scl + currentParent->GetLocalScale();
        currentParent = currentParent->parent;
    }

    localPosition = position - _pos;
    localRotation = rotation - _rot;
    localScale = scale - _scl;
}

void Transform::RecalculateWorldValues()
{
    Vector2 _pos;
    float _rot;
    Vector2 _scl;

    Transform *currentParent;

    while (currentParent != nullptr)
    {
        _pos = _pos + currentParent->GetLocalPosition();
        _rot = _rot + currentParent->GetLocalRotation();
        _scl = _scl + currentParent->GetLocalScale();
        currentParent = currentParent->parent;
    }

    position = _pos;
    rotation = _rot;
    scale = _scl;
}

void Transform::SetPosition(Vector2 newPosition)
{
    position = newPosition;
    OnTransformChange();
    RecalculateLocalValues();
}

void Transform::SetRotation(float newRotation)
{
    rotation = newRotation;
    OnTransformChange();
    RecalculateLocalValues();
}

void Transform::SetScale(Vector2 newScale)
{
    scale = newScale;
    OnTransformChange();
    RecalculateLocalValues();
}

void Transform::SetLocalPosition(Vector2 newLocalPosition)
{
    position = newLocalPosition;
    OnTransformChange();
    RecalculateWorldValues();
}

void Transform::SetLocalRotation(float newLocalRotation)
{
    rotation = newLocalRotation;
    OnTransformChange();
    RecalculateWorldValues();
}

void Transform::SetLocalScale(Vector2 newLocalScale)
{
    scale = newLocalScale;
    OnTransformChange();
    RecalculateWorldValues();
}