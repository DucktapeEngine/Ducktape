#pragma once

class Input
{
    public:
        static Vector2 MousePosition(sf::RenderWindow* screen)
        {
            sf::Vector2i vec = sf::Mouse::getPosition(*screen);
            return Vector2(vec.x, vec.y);
        }

        static bool GetMouseButton(int num)
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
};