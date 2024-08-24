/*
MIT License

Copyright (c) 2021 - 2023 Aryan Baburajan

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


#include <Core/Context.h>
#include <Renderer/Renderer.h>
#include <ECS/SceneManager.h>
#include <Components/Transform.h>
#include <Components/SpriteRenderer.h>

namespace DT
{
    SpriteRenderer::SpriteRenderer(Context *ctx) : 
        material(Shader::Default(*ctx))
    {
        PROFILE();

        renderer = ctx->GetService<Renderer>().Fatal("SpriteRenderer::SpriteRenderer()");
    }

    void SpriteRenderer::SetSprite(const std::filesystem::path &texturePath)
    {
        PROFILE();

        material.diffuseMap = Texture::Load(texturePath).Fatal("SpriteRenderer::SetSprite()");
    }

    void SpriteRenderer::Init(Context *ctx)
    {
        PROFILE();

        transform = scene->Require<Transform>(entity).Fatal("SpriteRenderer::Init()");
    }

    void SpriteRenderer::Tick(Context *ctx, const float &dt)
    {
        PROFILE();

        if (material.diffuseMap.has_value())
            mesh.Draw(*renderer, transform->GetModelMatrix(), material);
    }

    void SpriteRenderer::EditorTick(Context *ctx, const float &dt)
    {
        PROFILE();

        Tick(ctx, dt);
    }
}