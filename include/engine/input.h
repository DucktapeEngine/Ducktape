#ifndef INPUT_H
#define INPUT_H

typedef sf::Keyboard::Key KeyCode;

namespace Input
{
    std::vector<KeyCode>keyUpList;
    std::vector<KeyCode>keyDownList;
    Vector2 mousePosition;

    bool GetMouseButton(int num)
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

    static bool GetKey(KeyCode k)
    {
        return sf::Keyboard::isKeyPressed(k);
    }

    static bool GetKeyUp(KeyCode k)
    {
        return (std::find(keyUpList.begin(), keyUpList.end(), k) != keyUpList.end());
    }

    static bool GetKeyDown(KeyCode k)
    {
        return (std::find(keyDownList.begin(), keyDownList.end(), k) != keyDownList.end());
    }

    void Update()
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

                // case sf::Event::Resized:
                //     Application::SetResolution(Vector2(Application::renderWindow.getSize().x, Application::renderWindow.getSize().y));
                //     break;

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
};


#endif
