#ifndef TRANSFORM_H
#define TRANSFORM_H

class Transform : public BehaviourScript
{
private:
    Vector2 position = Vector2(0.0, 0.0);
    float rotation;
    Vector2 scale = Vector2(1.0, 1.0);

    Vector2 localPosition = Vector2(0.0, 0.0);
    float localRotation;
    Vector2 localScale = Vector2(1.0, 1.0);

public:
    Transform* parent = nullptr;
    std::vector<Transform*> children;    

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

    // local versions of each method

    Vector2 SetLocalPosition(Vector2 _pos);

    Vector2 GetLocalPosition()
    {
        return localPosition;
    }

    float SetLocalRotation(float _rot);

    float GetLocalRotation()
    {
        return localRotation;
    }

    Vector2 SetLocalScale(Vector2 _scl);

    Vector2 GetLocalScale()
    {
        return localScale;
    }

    void RecalculateLocalValues()
    {
        Vector2 _pos;
        float _rot;
        Vector2 _scl;

        Transform* currentParent = this->parent;

        while(currentParent != nullptr)
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

    void RecalculateWorldValues()
    {
        Vector2 _pos;
        float _rot;
        Vector2 _scl;

        Transform* currentParent;

        while(currentParent != nullptr)
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
};

#endif