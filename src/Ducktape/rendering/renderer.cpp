/*
MIT License

Copyright (c) 2022 Ducktape

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

#include <Ducktape/rendering/renderer.h>
using namespace DT;

std::vector<std::pair<std::string, sf::Texture>> Renderer::textureCache;

int Renderer::LoadTextureFromCache(std::string _path)
{
    int idx = -1;
    for(int i=0,n=textureCache.size();i<n;i++)
    {
        if(textureCache[i].first == _path)
        {
            idx = i;
            break;
        }
    }

    if(idx == -1)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(_path))
        {
            return -1;
        }
        textureCache.push_back({_path, texture});
        idx = textureCache.size() - 1;
    }
    return idx;
}

void Renderer::DrawSprite(std::string path, Vector2 pos, float rot, Vector2 scl, int pixelPerUnit, Color _color)
{
    int idx = LoadTextureFromCache(path);
    if(idx == -1)
    {
        Debug::LogError("Error loading sprite from " + path);
        return;
    }

    sf::Texture texture = textureCache[idx].second;

    texture.setSmooth(true);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(pos.ToSFMLVector());
    sprite.setRotation(rot);
    sprite.setScale((scl/pixelPerUnit).ToSFMLVector());
    sprite.setOrigin(sf::Vector2f(texture.getSize().x/2, texture.getSize().y/2));

    sprite.setColor(_color.ToSFMLColor());

    Application::renderWindow.draw(sprite);
}