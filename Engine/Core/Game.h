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

#include <Core/Platform.h>
#include <Core/ContextPtr.h>

typedef void (*RegisterRuntimeFunc)(DT::ContextPtr &);

namespace DT
{
    /**
     * @brief The Game class representing the game module.
     */
    class Game
    {
    public:
        /**
         * @brief The platform module for the game.
         */
        Platform::Module gameModule;

        /**
         * @brief Constructs a Game object and loads the game module.
         *
         * @param ctx The context pointer containing various engine components.
         */
        Game(ContextPtr &ctx)
        {
            // Load the game module from the current directory
            gameModule.Load(std::filesystem::current_path() / "Game.dll");

            // Get the symbol address of the "RegisterRuntime" function from the game module
            RegisterRuntimeFunc runtimeRegisterer = gameModule.GetSymbolAddress<void (*)(ContextPtr &)>("RegisterRuntime");

            if (!runtimeRegisterer)
            {
                std::cout << "[ERR] Failed to get symbol address of RegisterRuntime function\n";
                return;
            }

            runtimeRegisterer(ctx);

            std::cout << "[LOG] Runtime Registered\n";
        }
        
        /**
         * @brief Destructor for the Game class. Frees the game module.
         */
        ~Game()
        {
            gameModule.Free();
        }
    };

}