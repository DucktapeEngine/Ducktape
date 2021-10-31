#ifndef RENDERER_H
#define RENDERER_H

namespace Renderer
{
    std::vector<std::pair<std::string, sf::Texture>> textureCache;

    int LoadTextureFromCache(std::string _path)
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

    void DrawSprite(std::string path, Vector2 pos, float rot, Vector2 scl, int pixelPerUnit, Color _color)
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
};

#endif