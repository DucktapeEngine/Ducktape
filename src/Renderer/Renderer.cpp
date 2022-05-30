/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty ofT
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#include <Renderer/Renderer.h>

namespace DT
{
    int Renderer::LoadTextureFromCache(std::string path)
    {
        int idx = -1;
        for (int i = 0, n = textureCache.size(); i < n; i++)
        {
            if (textureCache[i].first == path)
            {
                idx = i;
                break;
            }
        }

        if (idx == -1)
        {
            sf::Texture texture;
            if (!texture.loadFromFile(path))
            {
                return -1;
            }
            textureCache.push_back({path, texture});
            idx = textureCache.size() - 1;
        }
        return idx;
    }

    void Renderer::DrawSprite(std::string path, glm::vec2 pos, float rot, glm::vec2 scl, int pixelPerUnit, Color color)
    {
        int idx = LoadTextureFromCache(path);
        if (idx == -1)
        {
            std::cout << "Error loading sprite from " << path << std::endl;
            return;
        }

        sf::Texture texture = textureCache[idx].second;

        texture.setSmooth(true);

        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(pos.x, pos.y));
        sprite.setRotation(rot);
        sprite.setScale(sf::Vector2f((scl / (float)pixelPerUnit).x, (scl / (float)pixelPerUnit).y));
        sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f));
        sprite.setColor((sf::Color)color);

        Window::window.draw(sprite);
    }
}