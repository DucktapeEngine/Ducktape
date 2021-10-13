#pragma once

class SpriteRenderer : public BehaviourScript
{
    public:
        std::string spritePath;
<<<<<<< Updated upstream

        SpriteRenderer()
        {
        }

        SpriteRenderer(std::string _spritePath)
        {
            spritePath = _spritePath;
        }

        Transform* tTransform;

        void Start(UpdateEssentials* updateEssentials)
        {
            tTransform = gameObject->GetComponent<Transform>();
        }

=======
        
>>>>>>> Stashed changes
        void Update(UpdateEssentials* updateEssentials)
        {
            if(spritePath != "")
            {
                Renderer::DrawSprite(spritePath, Camera::WorldToScreenPos(gameObject->transform->position, updateEssentials->screen), gameObject->transform->rotation, gameObject->transform->scale, updateEssentials->screen);
            }
        }
};