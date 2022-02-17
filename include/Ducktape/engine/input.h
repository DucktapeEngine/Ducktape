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

#ifndef DUCKTAPE_ENGINE_INPUT_H_
#define DUCKTAPE_ENGINE_INPUT_H_

#include <vector>

#include <SFML/Window.hpp>

#include <Ducktape/engine/vector2.h>
#include <Ducktape/engine/application.h>


namespace DT
{
    typedef sf::Keyboard::Key KeyCode;
    
    /**
     * @brief A namespace to hold all input related properties and functions that 
     * can be used to detect key presses, key releases, mouse presses, mouse releases, 
     * mouse position, etc.
     * 
     * List of inputs that can be detected:
     * All (almost every) key on the keyboard using `KeyCode::A` where `A` is the key. Check documentation for enum `KeyCode` for more information.
     * Mouse buttons using `MouseButton::Left` or `MouseButton::Right`.
     */
    namespace Input
    {
        /**
         * @brief List of keys that were released this frame.
         */
        extern std::vector<KeyCode> keyUpList;

        /**
         * @brief List of keys that were pressed this frame.
         */
        extern std::vector<KeyCode> keyDownList;

        /**
         * @brief The current mouse position.
         */
        extern Vector2 mousePosition;

        /**
         * @brief Get if a mouse button is pressed. 0 = left, 1 = right.
         * 
         * @param mouseButton The mouse button to check.
         * @return true/false based on if the mouse button is pressed or not. 
         */
        bool GetMouseButton(int mouseButton);

        /**
         * @brief Get if a key is currently being held down.
         * 
         * @param key The key to check. 
         * @return true/false based on if the key is being held down or not.
         */
        bool GetKey(KeyCode key);

        /**
         * @brief Get if a key was released this frame.
         * 
         * @param key The key to check.
         * @return true/false based on if the key was released this frame or not.
         */
        bool GetKeyUp(KeyCode key);

        /**
         * @brief Get if a key was pressed this frame.
         * 
         * @param key The key to check.
         * @return true/false based on if the key was pressed this frame or not.
         */
        bool GetKeyDown(KeyCode key);

        /**
         * @brief Calculate all of the input-related properties. This function is also
         * responsible for the window being responsive (not get the error "Application
         * is not responding"). Thus, it needs to be called every frame by the engine.
         */
        void Tick();
    };
}

#endif