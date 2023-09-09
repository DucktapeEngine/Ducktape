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

namespace DT
{
    /**
     * @brief The SceneManager class handles the management of scenes.
     */
    class SceneManager
    {
    public:
        Resource<Scene> activeScene; /// Pointer to the active scene resource.
        std::set<System *> systems;

        SceneManager(const json &data, ContextPtr &ctx);
        ~SceneManager();

        /**
         * @brief Returns the active scene.
         * @return A reference to the active scene.
         */
        inline Scene &GetActiveScene()
        {
            return *activeScene.data;
        }

        /**
         * @brief Registers a system of type T and returns a pointer to it.
         * @tparam T The type of the system to register.
         * @tparam Args The types of arguments to forward to the system's constructor.
         * @param args The arguments to forward to the system's constructor.
         * @return A pointer to the registered system.
         */
        template <typename T, typename... Args>
        T *RegisterSystem(Args &&...args)
        {
            System *system = new T(std::forward<Args>(args)...);
            systems.insert(system);
            return (T *)system;
        }

        void Save(std::filesystem::path savePath, Scene &scene, ContextPtr &ctx);
        void Load(std::filesystem::path savePath, Scene &scene, ContextPtr &ctx);

        IN_SERIALIZE(SceneManager, activeScene);
    };

}