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

#include <Ducktape/rendering/camera.h>
using namespace DT;

Camera::Camera(Entity *_entity)
{
    entity = _entity;
}

void Camera::tick()
{
    Vector2 pos = unitToPixel(entity->transform->getPosition());
    Vector2 pos2 = Vector2(Application::Private::resolution.x / 4 + pos.x, Application::Private::resolution.y / 4 + pos.y);

    Application::view.setCenter(pos2.x, pos2.y);
    Application::view.setRotation(entity->transform->getRotation());

    Application::view.zoom(size);
}

Vector2 Camera::unitToPixel(Vector2 pos)
{
    return Vector2(pos.x * (pixelPerUnit() / 2), pos.y * (pixelPerUnit() / 2));
}

Vector2 Camera::pixelToUnit(Vector2 pos)
{
    return Vector2(pos.x / (pixelPerUnit() / 2), pos.y / (pixelPerUnit() / 2));
}

Vector2 Camera::screenToWorldPos(Vector2 pos)
{
    sf::Vector2f vec = Application::renderWindow.mapPixelToCoords(sf::Vector2i(pos.x, pos.y));
    vec /= pixelPerUnit();
    vec -= sf::Vector2f(12.5f, 12.5f);
    return Vector2(vec.x, vec.y);
}

Vector2 Camera::worldToScreenPos(Vector2 pos)
{
    sf::Vector2i vec = Application::renderWindow.mapCoordsToPixel(sf::Vector2f(pos.x * pixelPerUnit(), pos.y * pixelPerUnit()));
    return Vector2(vec.x, vec.y);
}

float Camera::pixelPerUnit()
{
    return 10.0;
}