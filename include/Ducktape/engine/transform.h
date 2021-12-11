#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "scripts.h"
#include "vector2.h"
#include <vector>
// #include "gameobject.h"

namespace DT
{
    class Transform : public BaseScript
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

        Vector2 GetPosition();

        float SetRotation(float _rot);

        float GetRotation();

        Vector2 SetScale(Vector2 _scl);

        Vector2 GetScale();

        // local versions of each method

        Vector2 SetLocalPosition(Vector2 _pos);

        Vector2 GetLocalPosition();

        float SetLocalRotation(float _rot);

        float GetLocalRotation();

        Vector2 SetLocalScale(Vector2 _scl);

        Vector2 GetLocalScale();

        void RecalculateLocalValues();

        void RecalculateWorldValues();
    };
}

#endif