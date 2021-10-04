#pragma once

class SpriteRenderer : public BehaviourScript
{
    public:
        std::string spritePath;

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

        void Update(UpdateEssentials* updateEssentials)
        {
            if(spritePath != "")
            {
                Renderer::DrawSprite(spritePath, (*tTransform).position, updateEssentials->screen);
            }
        }
};