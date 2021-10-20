#pragma once

class SpriteRenderer : public BehaviourScript
{
    public:
        std::string spritePath;
        
        void Update()
        {
            if(spritePath != "")
            {
                Renderer::DrawSprite(spritePath, Camera::WorldToScreenPos(gameObject->transform->position), gameObject->transform->rotation, gameObject->transform->scale);
            }
        }
};