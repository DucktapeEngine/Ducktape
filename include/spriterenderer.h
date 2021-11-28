#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

class SpriteRenderer : public RenderScript
{
    public:
        std::string spritePath;
        int pixelPerUnit = 1;
        Color color = Color(255, 255, 255, 255);
        
        void Update()
        {
            if(spritePath != "")
            {
                Renderer::DrawSprite(spritePath, Camera::WorldToScreenPos(gameObject->transform->GetPosition()), gameObject->transform->GetRotation(), gameObject->transform->GetScale(), pixelPerUnit, color);
            }
        }
};

#endif