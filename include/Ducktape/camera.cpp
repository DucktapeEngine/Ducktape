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
void Camera::Start(UpdateEssentials* updateEssentials)
{
    tTransform = gameObject->GetComponent<Transform>();
}
void Camera::Update(UpdateEssentials* updateEssentials)
{
    updateEssentials->view->setCenter((*tTransform).position.x, (*tTransform).position.y);
    updateEssentials->view->setRotation((*tTransform).rotation);
    updateEssentials->view->setSize(m_Height, m_Width);
    updateEssentials->view->zoom(size);
}

Vector2 Camera::ScreenToWorldPos(Vector2 pos, sf::RenderWindow* screen)
{
    sf::Vector2f vec = screen->mapPixelToCoords(sf::Vector2i(pos.x, pos.y));
    return Vector2(vec.x, vec.y);
}
Vector2 Camera::WorldToScreenPos(Vector2 pos, sf::RenderWindow* screen)
{
    sf::Vector2i vec = screen->mapCoordsToPixel(sf::Vector2f(pos.x, pos.y));
    return Vector2(vec.x, vec.y);
}
