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

#include <Components/Component.h>

namespace DT
{
    /**
     * @brief LoopManager class for managing/updating rendering loops
     */
    class LoopManager
    {
    public:
        bool sceneTick = true;          ///< @brief whether to update/tick current scene loop or not

        /**
         * @brief initiate loop with given Component object.
         * @param component pointer to the component object.
         */
        static void InitLoop(Component* component);

        /**
         * @brief tick/update loop with given Component object.
         * @param component pointer to the pointer object
         */
        static void TickLoop(Component* component);

        /**
         * @brief destroy the loop with given Component object.
         * @param component pointer to the component object.
         */
        static void DestroyLoop(Component* component);
    };
}