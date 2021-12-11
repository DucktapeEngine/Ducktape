#include "spriterenderer.h"
using namespace DT;

void SpriteRenderer::Update()
{
    if(spritePath != "")
    {
        Renderer::DrawSprite(spritePath, Camera::WorldToScreenPos(entity->transform->GetPosition()), entity->transform->GetRotation(), entity->transform->GetScale(), pixelPerUnit, color);
    }
}