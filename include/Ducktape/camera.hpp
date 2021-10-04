#pragma once

class Camera : public BehaviourScript
{
    public:
        float size = 1.0;

        Camera()
        {
            size = 1.0;
        }

        Transform* tTransform;

        // void Start(UpdateEssentials* updateEssentials)
        // {
        //     tTransform = gameObject->GetComponent<Transform>();
        // }

        // void Update(UpdateEssentials* updateEssentials)
        // {
        //     updateEssentials->view->setCenter((*tTransform).position.x, (*tTransform).position.y);
        //     updateEssentials->view->setRotation((*tTransform).rotation);

        //     updateEssentials->view->setSize(HEIGHT, WIDTH);
        //     updateEssentials->view->zoom(size);
        // }

        static Vector2 ScreenToWorldPos(Vector2 pos, sf::RenderWindow* screen)
        {
            sf::Vector2f vec = screen->mapPixelToCoords(sf::Vector2i(pos.x, pos.y));
            return Vector2(vec.x, vec.y);
        }

        static Vector2 WorldToScreenPos(Vector2 pos, sf::RenderWindow* screen)
        {
            sf::Vector2i vec = screen->mapCoordsToPixel(sf::Vector2f(pos.x, pos.y));
            return Vector2(vec.x, vec.y);
        }
};