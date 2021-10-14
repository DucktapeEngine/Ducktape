#include "camera.hpp"
#include "updateessentials.hpp"
#include "vector2.hpp"
#include "transform.hpp"
#include "gameobject.hpp"
#include "ducktape.hpp"

Camera::Camera(int w,int h)
   : m_Width(w), m_Height(h)
{
    size = 1.0;
}
void Camera::Start()
{
    tTransform = gameObject->GetComponent<Transform>();
}
void Camera::Update()
{
    
}

Vector2 Camera::ScreenToWorldPos(Vector2 pos)
{
    sf::Vector2f vec = screen->mapPixelToCoords(sf::Vector2i(pos.x, pos.y));
    return Vector2(vec.x, vec.y);
}
Vector2 Camera::WorldToScreenPos(Vector2 pos)
{
    sf::Vector2i vec = screen->mapCoordsToPixel(sf::Vector2f(pos.x, pos.y));
    return Vector2(vec.x, vec.y);
}
