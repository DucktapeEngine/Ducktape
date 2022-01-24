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

#include <Ducktape/engine/input.h>
using namespace DT;

std::vector<KeyCode> Input::keyUpList;
std::vector<KeyCode> Input::keyDownList;
Vector2 Input::mousePosition;

bool Input::getMouseButton(int mouseButton)
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

bool Input::getKey(KeyCode key)
{
    return sf::Keyboard::isKeyPressed(key);
}

bool Input::getKeyUp(KeyCode key)
{
    return (std::find(keyUpList.begin(), keyUpList.end(), key) != keyUpList.end());
}

bool Input::getKeyDown(KeyCode key)
{
    return (std::find(keyDownList.begin(), keyDownList.end(), key) != keyDownList.end());
}

void Input::update()
{
    keyUpList.clear();
    keyDownList.clear();

    std::vector<KeyCode>::iterator position;
    sf::Event event;
    while (Application::renderWindow.pollEvent(event))
    {
        switch (event.type)
        {
        // window closed
        case sf::Event::Closed:
            Application::renderWindow.close();
            break;

        case sf::Event::Resized:
            Application::setResolution(Vector2(Application::renderWindow.getSize().x, Application::renderWindow.getSize().y));
            break;

        case sf::Event::KeyPressed:
            keyDownList.push_back(event.key.code);
            break;

        case sf::Event::KeyReleased:
            keyUpList.push_back(event.key.code);
            break;

        // we don't process other types of events
        default:
            break;
        }
    }

    mousePosition = Vector2(sf::Mouse::getPosition(Application::renderWindow).x, sf::Mouse::getPosition(Application::renderWindow).y);
}