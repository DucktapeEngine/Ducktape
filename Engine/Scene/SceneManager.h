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

#include <Core/Resource.h>
#include <Scene/Scene.h>
#include <Core/Serialization.h>

namespace DT
{
    /**
     * @brief The SceneManager class handles the management of scenes.
     */
    class SceneManager
    {
    public:
        Resource<Scene> activeScene; /// Pointer to the active scene resource.

        SceneManager(ContextPtr &ctx);

        /**
         * @brief Returns the active scene.
         * @return A reference to the active scene.
         */
        inline Scene &GetActiveScene()
        {
            return *activeScene.data;
        }

        IN_SERIALIZE(SceneManager, activeScene);
    };

}