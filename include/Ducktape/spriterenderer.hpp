#pragma once

class SpriteRenderer : public BehaviourScript
{
    public:
        std::string spritePath;
        int pixelPerUnit = 1;
        
        void Update()
        {
            if(spritePath != "")
            {
                Renderer::DrawSprite(spritePath, Camera::WorldToScreenPos(gameObject->transform->position), gameObject->transform->rotation, gameObject->transform->scale, pixelPerUnit);
            }
        }
};