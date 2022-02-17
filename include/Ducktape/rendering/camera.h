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

#ifndef DUCKTAPE_RENDERING_CAMERA_H_
#define DUCKTAPE_RENDERING_CAMERA_H_

#include <Ducktape/engine/application.h>
#include <Ducktape/engine/behaviourscript.h>
#include <Ducktape/engine/entity.h>
#include <Ducktape/engine/transform.h>
#include <Ducktape/engine/vector2.h>

namespace DT
{
	/**
	 * @brief A Camera is a device through which the player views the world.
	 */
	class Camera : public BehaviourScript
	{
	public:
		static Camera *activeCamera;

		Color backgroundColor = Color(0, 0, 0, 255);

		void Constructor();
		void Tick();

		/**
		 * @brief Convert pixel coordinates to metre coordinates.
		 *
		 * @param pos The pixel coordinate to convert.
		 * @return Vector2 The converted metre coordinates.
		 */
		static Vector2 UnitToPixel(Vector2 pos);

		/**
		 * @brief Convert metre coordinates to pixel coordinates.
		 *
		 * @param pos The coordinate to convert.
		 * @return Vector2 The converted pixel coordinates.
		 */
		static Vector2 PixelToUnit(Vector2 pos);

		/**
		 * @brief Convert screen coordinates to world coordinates.
		 *
		 * @param pos The screen coordinate to convert.
		 * @return Vector2 The converted world coordinates.
		 */
		static Vector2 ScreenToWorldPos(Vector2 pos);

		/**
		 * @brief Convert world coordinates to screen coordinates.
		 *
		 * @param pos The world coordinate to convert.
		 * @return Vector2 The converted screen coordinates.
		 */
		static Vector2 WorldToScreenPos(Vector2 pos);

		/**
		 * @brief The pixel per unit of the camera.
		 */
		static const float PIXEL_PER_UNIT;
	};
} // namespace DT

#endif