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

#include <Input/Input.h>

namespace DT
{
    std::vector<KeyCode> Input::keyUpList;
    std::vector<KeyCode> Input::keyDownList;

    glm::vec2 Input::GetMousePosition()
    {
        return glm::vec2(sf::Mouse::getPosition(Window::window).x, sf::Mouse::getPosition(Window::window).y);
    }

    bool Input::GetMouseButton(int mouseButton)
    {
        if (mouseButton == 0 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            return true;
        }
        else if (mouseButton == 1 && sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            return true;
        }
        return false;
    }

    bool Input::GetKey(KeyCode key)
    {
        return sf::Keyboard::isKeyPressed(key);
    }

    bool Input::GetKeyUp(KeyCode key)
    {
        return (std::find(keyUpList.begin(), keyUpList.end(), key) != keyUpList.end());
    }

    bool Input::GetKeyDown(KeyCode key)
    {
        return (std::find(keyDownList.begin(), keyDownList.end(), key) != keyDownList.end());
    }

    void Input::Tick()
    {
        keyUpList.clear();
        keyDownList.clear();

        std::vector<KeyCode>::iterator position;
        sf::Event event;

        while (Window::window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                Window::window.close();
                break;

            case sf::Event::Resized:
                Window::SetResolution({event.size.width, event.size.height});
                break;

            case sf::Event::KeyPressed:
                keyDownList.push_back(event.key.code);
                break;

            case sf::Event::KeyReleased:
                keyUpList.push_back(event.key.code);
                break;

            default:
                break;
            }
        }
    }
}