#pragma once
#include <SFML/Window.hpp>
#include "vector2.hpp"
typedef sf::Keyboard::Key KeyCode;

namespace Input
{
    Vector2 mousePosition;

    bool GetMouseButton(int num);

    static bool GetKey(KeyCode k);

    void Update();
};