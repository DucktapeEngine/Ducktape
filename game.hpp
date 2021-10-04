#pragma once

std::vector<GameObject*> gameObjects;
BehaviourScript* mainCamera;

class TopDownController : public BehaviourScript
{
    public:
        TopDownController()
        {
            ;
        }

        Transform* tTransform;

        void Start(UpdateEssentials* updateEssentials)
        {
            tTransform = gameObject->GetComponent<Transform>();
        }

        void Update(UpdateEssentials* updateEssentials)
        {
            tTransform->position = Camera::ScreenToWorldPos(Input::MousePosition(updateEssentials->screen), updateEssentials->screen);
        }
};

void ExampleScene(sf::RenderWindow& screen)
{
    gameObjects.clear();
    int n = -1;
    gameObjects.push_back(new GameObject("Player"));
    n++;
    gameObjects[n]->AddComponent<SpriteRenderer>();
    gameObjects[n]->AddComponent<TopDownController>();
    gameObjects[n]->AddComponent<Rigidbody>();

    gameObjects.push_back(new GameObject("Camera"));
    n++;
    gameObjects[n]->AddComponent<Camera>();
    // mainCamera = gameObjects[n]->GetComponent("Camera");
    mainCamera = gameObjects[n]->GetComponent<Camera>();

    // gameObjects.push_back(new GameObject("Ground"));
    // n++;
    // gameObjects[n]->AddComponent(new Transform(Vector2(0.0,-5.0), 0.0, Vector2(1.0, 1.0))));
    // gameObjects[n]->AddComponent(new SpriteRenderer("./Assets/Characters/character_0000.png"));
}