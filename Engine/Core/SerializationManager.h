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

#pragma once

#include <Scene/Entity.h>
#include <Scene/Scene.h>

namespace DT
{
    class SerializationManager
    {
    public:
        json data;
        bool isSerializing = true;

        template <typename T>
        void SerializeComponent(const std::string componentName, Entity entity, Scene &scene)
        {
            try
            {
                T *component = scene.Get<T>(entity);
                if (component == nullptr)
                    return;

                if (isSerializing)
                    data["entities"][entt::to_integral(entity)]["components"][componentName] = *component;
                else
                    *component = data["entities"][entt::to_integral(entity)]["components"][componentName];
            }
            catch (json::exception &e)
            {
                std::cout << "json::exception " << e.what() << std::endl;
            }
        }
    };
}