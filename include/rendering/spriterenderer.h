#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

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