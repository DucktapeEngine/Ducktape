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

#include <Components/Transform.h>

namespace DT
{
    glm::vec3 Transform::Forward()
    {
        FT("Transform::Forward()");
        return glm::vec3(2 * (rotation.x * rotation.z + rotation.w * rotation.y),
                         2 * (rotation.y * rotation.z - rotation.w * rotation.x),
                         1 - 2 * (rotation.x * rotation.x + rotation.y * rotation.y));
    }

    glm::vec3 Transform::Right()
    {
        FT("Transform::Right()");
        return glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), Forward()));
    }

    glm::vec3 Transform::Up()
    {
        FT("Transform::Up()");
        return glm::cross(Forward(), Right());
    }
}