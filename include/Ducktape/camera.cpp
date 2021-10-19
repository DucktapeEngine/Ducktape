#include "camera.hpp"
#include "application.hpp"
#include "vector2.hpp"
#include "transform.hpp"
#include "gameobject.hpp"

void Camera::Update()
{
    Application::view.setCenter(500/2 + gameObject->transform->position.x, 500/2 + gameObject->transform->position.y);
    Application::view.setRotation(gameObject->transform->rotation);

    Application::view.setSize(500, 500);
    Application::view.zoom(size);
}

Vector2 Camera::ScreenToWorldPos(Vector2 pos)
{
	sf::Vector2f vec = Application::renderWindow.mapPixelToCoords(sf::Vector2i(pos.x/PPU(), pos.y/PPU()));
	return Vector2(vec.x, vec.y);
}

Vector2 Camera::WorldToScreenPos(Vector2 pos)
{
	sf::Vector2i vec = Application::renderWindow.mapCoordsToPixel(sf::Vector2f(pos.x*PPU(), pos.y*PPU()));
	return Vector2(vec.x, vec.y);
}

float Camera::PPU()
{
    return 10.0;
}