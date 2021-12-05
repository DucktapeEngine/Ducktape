#include "spriterenderer.h"
using namespace DT;

void SpriteRenderer::Update()
{
    if(spritePath != "")
    {
        Renderer::DrawSprite(spritePath, Camera::WorldToScreenPos(gameObject->transform->GetPosition()), gameObject->transform->GetRotation(), gameObject->transform->GetScale(), pixelPerUnit, color);
    }
}