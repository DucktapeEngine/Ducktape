/*
MIT License

Copyright (c) 2021 - 2025 Aryan Baburajan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <core/context.h>
#include <renderer/renderer.h>
#include <scene/scene_manager.h>
#include <components/transform.h>
#include <components/sprite_renderer.h>

namespace DT
{
    SpriteRenderer::SpriteRenderer(Context *ctx) : material(Shader::Default(*ctx))
    {
        renderer = ctx->GetService<Renderer>();
    }

    void SpriteRenderer::SetSprite(const std::filesystem::path &texturePath)
    {
        material.diffuseMap = Texture::Load(texturePath);
    }

    void SpriteRenderer::Init(Context *ctx)
    {
        transform = scene->Require<Transform>(entity);
    }

    void SpriteRenderer::Tick(Context *ctx, const float &dt)
    {
        if (material.diffuseMap.has_value())
            mesh.Draw(*renderer, transform->GetModelMatrix(), material);
    }

    void SpriteRenderer::EditorTick(Context *ctx, const float &dt)
    {
        Tick(ctx, dt);
    }

    void SpriteRenderer::InspectorMenu(Context *ctx, const float &dt)
    {
        if (ImGui::CollapsingHeader("SpriteRenderer"))
        {
            ImGui::Text("hey");
        }
    }
}