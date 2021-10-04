#pragma once

class Transform : public BehaviourScript
{
    public:
        Vector2 position = Vector2(0.0, 0.0);
        float rotation;
        Vector2 scale = Vector2(1.0, 1.0);

        Transform()
        {
            position = Vector2(0.0, 0.0);
            rotation = 0.0;
            scale = Vector2(1.0, 1.0);
        }
};