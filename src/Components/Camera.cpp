/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#include <Components/Camera.h>

namespace DT
{
    Camera::Camera()
    {
        FT("Camera::Camera()");
        activeCamera = this;
    }

    void Camera::Init()
    {
        transform = &Entity::FromComponent(*this).RequireComponent<Transform>();
    }

    void Camera::Tick()
    {
        glm::vec2 pos = UnitToPixel(transform->position);
        pos -= glm::vec2(Window::GetResolution().x / 2, Window::GetResolution().y / 2);

        Window::view.setCenter(pos.x, pos.y);
        Window::view.setRotation(transform->rotation);
        Window::window.setView(Window::view);
    }

    glm::vec2 Camera::UnitToPixel(glm::vec2 pos)
    {
        return glm::vec2(pos.x * (Window::PIXEL_PER_UNIT), pos.y * (Window::PIXEL_PER_UNIT));
    }

    glm::vec2 Camera::PixelToUnit(glm::vec2 pos)
    {
        return glm::vec2(pos.x / (Window::PIXEL_PER_UNIT), pos.y / (Window::PIXEL_PER_UNIT));
    }

    glm::vec2 Camera::ScreenToWorld(glm::vec2 pos)
    {
        sf::Vector2f vec = Window::window.mapPixelToCoords(sf::Vector2i(pos.x, pos.y));
        return glm::vec2(vec.x, vec.y);
    }

    glm::vec2 Camera::WorldToScreen(glm::vec2 pos)
    {
        sf::Vector2i vec = Window::window.mapCoordsToPixel(sf::Vector2f(pos.x, pos.y));
        return glm::vec2(vec.x, vec.y);
    }
}