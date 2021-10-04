#ifndef DUCKTAPE_H
#define DUCKTAPE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "behaviourscript.hpp"

class UpdateEssentials;
class Transform;
class GameObject;
namespace DT
{





class TopDownController : public BehaviourScript
{
public:
    TopDownController() = default;

    Transform* tTransform;

    void Start(UpdateEssentials* updateEssentials);

    void Update(UpdateEssentials* updateEssentials);
};

class ExampleClass{
public:
    void ExampleScene(sf::RenderWindow& screen, int w, int h);
    int iFrameRateLimit = 0;
    bool bVerticalSync = true;
    std::vector<GameObject*> gameObjects;
private:
    BehaviourScript* mainCamera;
    void SplashScreen(sf::RenderWindow& screen, std::string color, int w, int h);

};


}
#endif
