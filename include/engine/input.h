#ifndef INPUT_H
#define INPUT_H

#include <SFML/Window.hpp>
#include <vector>
#include "vector2.h"
#include "application.h"

typedef sf::Keyboard::Key KeyCode;

namespace DT
{
    namespace Input
    {
        extern std::vector<KeyCode>keyUpList;
        extern std::vector<KeyCode>keyDownList;
        extern Vector2 mousePosition;

        bool GetMouseButton(int num);

        bool GetKey(KeyCode k);

        bool GetKeyUp(KeyCode k);

        bool GetKeyDown(KeyCode k);

        void Update();
    };
}

#endif