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

namespace DT
{
    class Engine;
    class ResourceManager;
    class Window;
    class Renderer;
    class Input;
    class Time;
    class LoopManager;
    class Debug;
    class Context;
    class Scene;
    class SceneManager;
    class Game;

    /**
     * @brief A light (light on compilation time) class alternative to the Context class. Allows for access to various systems in the Engine.
     */
    class ContextPtr
    {
    public:
        Engine *engine{NULL};
        Window *window{NULL};
        Renderer *renderer{NULL};
        Input *input{NULL};
        Time *time{NULL};
        LoopManager *loopManager{NULL};
        Debug *debug{NULL};
        Context *ctx{NULL};
        SceneManager *sceneManager{NULL};
        Game *game{NULL};
        ResourceManager *resourceManager{NULL};

        friend class Context;
    };
}