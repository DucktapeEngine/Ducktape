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

        inline void Start()
        {
            tTransform = gameObject->GetComponent<Transform>();
        }

        inline void Update()
        {
            if(spritePath != "")
            {
                Renderer::DrawSprite(spritePath, (*tTransform).position);
            }
        }
};
