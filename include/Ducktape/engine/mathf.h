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

#ifndef MATHF_H
#define MATHF_H

#include <cmath>
#include <algorithm>

namespace DT
{
    /**
     * @brief A namespace to hold all math related properties and functions that 
     * can be used to perform math operations.
     */
    namespace Mathf
    {
        extern float Deg2Rad;
        extern float Epsilon;
        extern float PositiveInfinity;
        extern float NegativeInfinity;
        extern float PI;
        extern float Rad2Deg;
        extern float GoldenRatio;

        /**
         * @brief Returns the absolute valueue of the given number.
         * @param value The number to get the absolute valueue of.
         * @return The absolute valueue of the given number.
         */
        float abs(float value);

        /**
         * @brief Returns the arc cosine of the given number.
         * @param value The number to get the arc cosine of.
         * @return The arc cosine of the given number.
         */
        float acos(float value);

        /**
         * @brief Returns true if the given valueues are approximately equal.
         * @param value The first valueue to compare.
         * @param value2 The second valueue to compare.
         * @return True if the given valueues are approximately equal.
         */
        bool approximately(float value, float value2);

        /**
         * @brief Returns the arc sine of the given number.
         * @param value The number to get the arc sine of.
         * @return The arc sine of the given number.
         */
        float asin(float value);

        /**
         * @brief Returns the arc tangent of the given number.
         * @param value The number to get the arc tangent of.
         * @return The arc tangent of the given number.
         */
        float atan(float value);

        /**
         * @brief Returns the arc tangent of the given number.
         * @param value The numerator of the arc tangent.
         * @param value2 The denominator of the arc tangent.
         * @return The arc tangent of the given number.
         */
        float atan2(float value, float value2);

        /**
         * @brief Returns the ceiling of the given number.
         * @param value The number to get the ceiling of.
         * @return The ceiling of the given number.
         */
        float ceil(float value);

        /**
         * @brief Returns an integer that is value clamped between the given min and max.
         * 
         * @param value The value to clamp.
         * @param min The minimum value to clamp to.
         * @param max The maximum value to clamp to.
         * @return The clamped value.
         */
        float clamp(float value, float min, float max);

        /**
         * @brief Returns the cosine of the given number.
         * @param value The number to get the cosine of.
         * @return The cosine of the given number.
         */
        float cos(float value);

        /**
         * @brief Returns the shortest difference between two given angles given in degrees.
         * @param value The first angle in degrees.
         * @param value2 The second angle in degrees.
         * @return The shortest difference between two given angles given in degrees.
         */
        float deltaAngle(float value, float value2);

        /**
         * @brief Returns the hyperbolic cosine of the given number.
         * @param value The number to get the hyperbolic cosine of.
         * @return The hyperbolic cosine of the given number.
         */
        float exp(float value);

        /**
         * @brief Returns the floor of the given number.
         * @param value The number to get the floor of.
         * @return The floor of the given number.
         */
        float floor(float value);

        /**
         * @brief Returns the round of the given number.
         * @param value The number to get the hyperbolic cosine of.
         * @return The round of the given number.
         */
        float round(float value);

        /**
         * @brief Get the interpolated float result between the two float values.
         * 
         * @param value Initial value.
         * @param target Target value.
         * @param interpolation Interpolation value.
         * @return The interpolated float result between the two float values. 
         */
        float lerp(float value, float target, float interpolation);

        /**
         * @brief Get the maximum of the two float values.
         * 
         * @param value The first float value.
         * @param value2 The second float value.
         * @return float The maximum of the two float values.
         */
        float max(float value, float value2);

        /**
         * @brief Get the minimum of the two float values.
         * 
         * @param value The first float value.
         * @param value2 The second float value.
         * @return float The minimum of the two float values.
         */
        float min(float value, float value2);

        /**
         * @brief Moves value towards target.
         * 
         * @param value The current value.
         * @param target The target value.
         * @param delta The amount to move.
         * @return float The moved value.
         */
        float moveTowards(float value, float target, float delta);

        /**
         * @brief Returns value raised to the power of value2.
         * 
         * @param value The base value.
         * @param value2 The exponent value.
         * @return float The value raised to the power of value2.
         */
        float pow(float value, float value2);

        /**
         * @brief Returns the sine of the given number.
         * @param value The number to get the sine of.
         * @return The sine of the given number.
         */
        float sin(float value);

        /**
         * @brief Returns the square root of the given number.
         * @param value The number to get the square root of.
         * @return The square root of the given number.
         */
        float sqrt(float value);

        /**
         * @brief Returns the tangent of the given number.
         * 
         * @param value The number to get the tangent of.
         * @return float The tangent of the given number.
         */
        float tan(float value);
    };
}

#endif