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

#ifndef SCENE_H
#define SCENE_H

#include <Ducktape/engine/vector2.h>
#include <vector>

namespace DT
{
	class Entity;

	/**
	 * @brief Scene system for Ducktape. This class can be used to create and manage entities
	 * in different scenes.
	 */
	class Scene
	{
	public:
		/**
		 * @brief List of entities the scene contains.
		 */
		std::vector<Entity *> entities;

		/**
		 * @brief Called by the Scene Manager when the scene is loaded.
		 */
		virtual void initialize() {}

		/**
		 * @brief Called by the Scene Manager when another scene is loaded.
		 */
		void destroy();
	};
}

#endif