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

#include <vector>
#include <unordered_map>
#include <functional>

namespace DT
{
    /**
     * @brief The EventHandler class for managing event handlers.
     */
    class EventHandler
    {
    protected:
        /**
         * @brief A map that associates event IDs with a vector of event handler functions.
         */
        std::unordered_map<int, std::vector<std::function<void(EventHandler *)>>> eventHandlers;

    public:
        /**
         * @brief Register an event handler for a specific event ID.
         *
         * @param event The event ID to register the handler for.
         * @param eventHandler The event handler function.
         */
        void OnEvent(int event, std::function<void(EventHandler *)> eventHandler);

        /**
         * @brief Invoke all event handlers associated with a specific event ID.
         *
         * @param event The event ID to invoke the handlers for.
         */
        void Invoke(int event);
    };
}