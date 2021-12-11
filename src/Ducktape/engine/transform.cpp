#include "transform.h"
using namespace DT;

Vector2 Transform::GetPosition()
{
    // assert (this != NULL);
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