#include "ducktape.hpp"
#include "debug.hpp"
#include "gameobject.hpp"
#include "transform.hpp"
#include "vector2.hpp"
#include "camera.hpp"
#include "input.hpp"
#include "behaviourscript.hpp"
#include "updateessentials.hpp"
#include "transform.hpp"
#include "spriterenderer.hpp"
#include "renderer.hpp"

void DT::TopDownController::Start()
{
    tTransform = gameObject->GetComponent<Transform>();
}

void DT::TopDownController::Update()
{
    tTransform->position = Camera::ScreenToWorldPos(Input::MousePosition());
}

void DT::ExampleClass::SplashScreen(sf::RenderWindow &screen, std::string color, int w, int h)
{
    sf::Clock clock;

    while (clock.getElapsedTime().asSeconds() < 5 && screen.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (screen.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                screen.close();
        }

        screen.clear(sf::Color::White);

        if(color == "light")
        {
            sf::Texture texture;
            if (!texture.loadFromFile("./Assets/Branding/pfpFillWhite.png"))
            {
                Debug::LogError("Error loading sprite from ./Assets/Branding/pfpFillWhite.png");
                return;
            }

            sf::Image image;
            texture.update(image);
            texture.setSmooth(true);

            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setScale(0.1, 0.1);
            sprite.setOrigin(2000.0, 2000.0);
            sprite.setPosition(w/2, h/2);

            screen.draw(sprite);
        }

        screen.display();
    }
}

void DT::ExampleClass::ExampleScene(sf::RenderWindow &screen, int w, int h)
{
    gameObjects.clear();
    int n = -1;
    gameObjects.push_back(new GameObject("Player"));
    n++;
    gameObjects[n]->AddComponent(new Transform());
    gameObjects[n]->AddComponent(new SpriteRenderer("./Assets/Characters/character_0000.png"));
    gameObjects[n]->AddComponent(new TopDownController());

    gameObjects.push_back(new GameObject("Camera"));
    n++;
    gameObjects[n]->AddComponent(new Camera(w,h));
    gameObjects[n]->AddComponent(new Transform(Vector2(0.0,0.0), 0.0, Vector2(1.0, 1.0)));
    // mainCamera = gameObjects[n]->GetComponent("Camera");
    mainCamera = gameObjects[n]->GetComponent<Camera>();
}
