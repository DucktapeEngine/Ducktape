#include "spriterenderer.hpp"
#include "transform.hpp"
#include "renderer.hpp"
#include "camera.hpp"
#include "application.hpp"

void SpriteRenderer::Update()
{
    if(spritePath != "")
    {
        Renderer::DrawSprite(spritePath, Camera::WorldToScreenPos(gameObject->transform->position), gameObject->transform->rotation, gameObject->transform->scale);
    }
}