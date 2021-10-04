#pragma once
#include "behaviourscript.hpp"
#include "transform.hpp"
#include "renderer.hpp"

class SpriteRenderer : public BehaviourScript
{
    public:
        std::string spritePath;

        SpriteRenderer() = default;

        SpriteRenderer(std::string path)
            : spritePath(path)
        {
        }

        Transform* tTransform;

        inline void Start(UpdateEssentials* updateEssentials)
        {
            tTransform = gameObject->GetComponent<Transform>();
        }

        inline void Update(UpdateEssentials* updateEssentials)
        {
            if(spritePath != "")
            {
                Renderer::DrawSprite(spritePath, (*tTransform).position, updateEssentials->screen);
            }
        }
};
