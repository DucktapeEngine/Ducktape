#include "input.hpp"
#include "application.hpp"

bool Input::GetMouseButton(int num)
{
    if(num == 0 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        return true;
    }
    else if(num == 2 && sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        return true;
    }
    return false;
}

bool Input::GetKey(KeyCode k)
{
    return sf::Keyboard::isKeyPressed(k);
}

void Input::Update()
{
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
                break;

            // we don't process other types of events
            default:
                break;
        }
    }

    mousePosition = Vector2(sf::Mouse::getPosition(Application::renderWindow).x, sf::Mouse::getPosition(Application::renderWindow).y);
}