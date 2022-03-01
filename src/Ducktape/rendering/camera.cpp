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

Camera *Camera::activeCamera = nullptr;

void Camera::Constructor()
{
    if (activeCamera == nullptr)
    {
        activeCamera = this;
    }
    else
    {
        Debug::LogFatalError("Cannot create multiple Cameras.");
    }
}

void Camera::Tick()
{
    Vector2 pos = UnitToPixel(entity->transform->SetPosition());
    pos = Vector2(Application::Private::resolution.x / 2, Application::Private::resolution.y / 2);

    Application::view.setCenter(pos.x, pos.y);
    Application::view.setRotation(entity->transform->GetRotation());
}

Vector2 Camera::UnitToPixel(Vector2 pos)
{
    return Vector2(pos.x * (Application::PIXEL_PER_UNIT), pos.y * (Application::PIXEL_PER_UNIT));
}

Vector2 Camera::PixelToUnit(Vector2 pos)
{
    return Vector2(pos.x / (Application::PIXEL_PER_UNIT), pos.y / (Application::PIXEL_PER_UNIT));
}

Vector2 Camera::ScreenToWorldPos(Vector2 pos)
{
    sf::Vector2f vec = Application::renderWindow.mapPixelToCoords(sf::Vector2i(pos.x, pos.y));
    return Vector2(vec.x, vec.y);
}

Vector2 Camera::WorldToScreenPos(Vector2 pos)
{
    sf::Vector2i vec = Application::renderWindow.mapCoordsToPixel(sf::Vector2f(pos.x, pos.y));
    return Vector2(vec.x, vec.y);
}