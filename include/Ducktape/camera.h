#ifndef CAMERA_H
#define CAMERA_H

class Camera : public BehaviourScript
{
    public:
        float size = 1.0;
        
        void Update()
        {
            Application::view.setCenter(500/2 + gameObject->transform->position.x, 500/2 + gameObject->transform->position.y);
            Application::view.setRotation(gameObject->transform->rotation);

            Application::view.setSize(500, 500);
            Application::view.zoom(size);
        }

        static Vector2 ScreenToWorldPos(Vector2 pos)
        {
            sf::Vector2f vec = Application::renderWindow.mapPixelToCoords(sf::Vector2i(pos.x/PPU(), pos.y/PPU()));
            return Vector2(vec.x, vec.y);
        }

        static Vector2 WorldToScreenPos(Vector2 pos)
        {
            sf::Vector2i vec = Application::renderWindow.mapCoordsToPixel(sf::Vector2f(pos.x*PPU(), pos.y*PPU()));
            return Vector2(vec.x, vec.y);
        }

        static float PPU()
        {
            return 10.0;
        }
};


#endif