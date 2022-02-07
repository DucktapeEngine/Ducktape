/*
MIT License

Copyright (c) 2022 Ducktape

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef DUCKTAPE_ENGINE_PROJECTSETTINGS_H_
#define DUCKTAPE_ENGINE_PROJECTSETTINGS_H_

#include <Ducktape/engine/color.h>
#include <Ducktape/engine/vector2.h>
#include <Ducktape/engine/scene.h>

namespace DT
{
	/**
	 * @brief A namespace to hold all project related properties that can be 
	 * modified by the user.
	 */
	namespace ProjectSettings
	{
		namespace Application
		{
			/**
			 * @brief The title of the window.
			 */
			extern std::string windowTitle;

			/**
			 * @brief The initial size of the window.
			 */
			extern Vector2 initialResolution;
		}

		namespace Physics
		{
			/**
			 * @brief The gravity all Rigidbodies will be affected by.
			 */
			extern Vector2 globalGravity;
		}

		namespace SceneManagement
		{
			/**
			 * @brief The first scene of the game.
			 * @param scene The scene to be loaded.
			 */
			extern Scene *initialScene;
		}
	}
}

#endif