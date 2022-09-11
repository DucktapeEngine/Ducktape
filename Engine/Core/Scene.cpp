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

#include <Core/Scene.h>

namespace DT
{
    void Scene::Init(Engine *e)
    {
        engine = engine;

        callState = CallState::EngineAssignment;
        for (System system : systems)
            system(this);

        callState = CallState::Init;
        for (System system : systems)
            system(this);
    }

    void Scene::Tick()
    {
        callState = CallState::Tick;
        for (System system : systems)
            system(this);
    }

    void Scene::SceneView()
    {
        callState = CallState::SceneView;
        for (System system : systems)
            system(this);
    }

    void Scene::Destroy()
    {
        callState = CallState::Destroy;
        for (System system : systems)
            system(this);
    }
}