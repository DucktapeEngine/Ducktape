#include "renderer.hpp"
#include "vector2.hpp"
#include "debug.hpp"

void Renderer::DrawSprite(std::string path, Vector2 pos)
{
    sf::Texture texture;
    if (!texture.loadFromFile(path))
    {
        Debug::LogError("Error loading sprite from " + path);
        return;
    }

    sf::Image image;
    texture.update(image);
    texture.setSmooth(true);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(pos.ToSFMLVector());

    screen->draw(sprite);
}
