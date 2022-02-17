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

#ifndef DUCKTAPE_ENGINE_APPLICATION_H_
#define DUCKTAPE_ENGINE_APPLICATION_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Ducktape/engine/vector2.h>
#include <Ducktape/engine/projectsettings.h>

namespace DT
{
	/**
	 * @brief Namespace containing application-related functions and properties.
	 */
	namespace Application
	{
		/**
		 * @cond section label="No need to confuse users with this."
		 * Not really private, it's just for preventing users from
		 * having direct access to these variables.
		 */
		namespace Private
		{
			extern Vector2 resolution;
		}
		/**
		 * @endcond
		 */

		extern sf::View view;
		extern sf::RenderWindow renderWindow;

		/**
		 * @brief Set the application's resolution.
		 *
		 * @param resolution The new resolution.
		 */
		void SetResolution(Vector2 resolution);

		/**
		 * @brief Get the application's current resolution.
		 *
		 * @return The application's current resolution.
		 */
		Vector2 GetResolution();

		/**
		 * @brief Initialize the application.
		 */
		void Initialize();

		/**
		 * @brief Check if the application is still open.
		 *
		 * @return True if the application is still open, false otherwise.
		 */
		bool IsOpen();

		/**
		 * @brief Close the application.
		 */
		void Close();
	}
}

#endif