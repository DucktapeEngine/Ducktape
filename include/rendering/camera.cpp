#include "camera.h"
using namespace DT;

void Camera::Update()
{
    Vector2 pos = UnitToPixel(gameObject->transform->GetPosition());
    Vector2 pos2 = Vector2(Application::resolution.x/4 + pos.x, Application::resolution.y/4 + pos.y);

    Application::view.setCenter(pos2.x, pos2.y);
    Application::view.setRotation(gameObject->transform->GetRotation());

    Application::view.zoom(size);
}

Vector2 Camera::UnitToPixel(Vector2 pos)
{
    return Vector2(pos.x*(PixelPerUnit()/2), -pos.y*(PixelPerUnit()/2));
}

Vector2 Camera::ScreenToWorldPos(Vector2 pos)
{
    sf::Vector2f vec = Application::renderWindow.mapPixelToCoords(sf::Vector2i(pos.x/PixelPerUnit(), pos.y/PixelPerUnit()));
    return Vector2(vec.x, vec.y);
}

Vector2 Camera::WorldToScreenPos(Vector2 pos)
{
    sf::Vector2i vec = Application::renderWindow.mapCoordsToPixel(sf::Vector2f(pos.x*PixelPerUnit(), pos.y*PixelPerUnit()));
    return Vector2(vec.x, vec.y);
}

float Camera::PixelPerUnit()
{
    return 10.0;
}