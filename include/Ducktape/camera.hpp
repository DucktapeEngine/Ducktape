#pragma once
#include "behaviourscript.hpp"
#include <SFML/Graphics.hpp>

class Transform;
class Vector2;

class Camera : public BehaviourScript
{
public:
    float size = 1.0;

    Camera(int w, int h);

    Transform* tTransform;

    void Start();

    void Update();

    static Vector2 ScreenToWorldPos(Vector2 pos, sf::RenderWindow* screen);

    static Vector2 WorldToScreenPos(Vector2 pos, sf::RenderWindow* screen);
private:
    int m_Width;
    int m_Height;
};
