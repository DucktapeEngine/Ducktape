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

namespace Ducktape
{
    Camera::Camera()
    {
        activeCamera = this;
    }

    void Camera::Init()
    {
        transform = &Entity::FromComponent(*this).GetComponent<Transform>();
    }

    void Camera::Tick()
    {
        camera.SetPosition(Math::ToRaylibVector(transform->position));
        camera.SetTarget(Math::ToRaylibVector(transform->position + transform->Forward()));
        camera.SetUp(Math::ToRaylibVector(transform->Up()));
        camera.SetFovy(fieldOfView);
        if (isOrthographic)
        {
            camera.SetMode(CAMERA_ORTHOGRAPHIC);
        }
        else
        {
            camera.SetMode(CAMERA_PERSPECTIVE);
        }
    }
}