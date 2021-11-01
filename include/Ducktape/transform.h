#ifndef TRANSFORM_H
#define TRANSFORM_H

class Transform : public BehaviourScript
{
private:
    Vector2 position = Vector2(0.0, 0.0);
    float rotation;
    Vector2 scale = Vector2(1.0, 1.0);

public:

    Vector2 SetPosition(Vector2 _pos);

    Vector2 GetPosition()
    {
        return position;
    }

    float SetRotation(float _rot);

    float GetRotation()
    {
        return rotation;
    }

    Vector2 SetScale(Vector2 _scl);

    Vector2 GetScale()
    {
        return scale;
    }
};

#endif