#pragma once

std::vector<GameObject*> gameObjects;
BehaviourScript* mainCamera;

class TopDownController : public BehaviourScript
{
    public:
<<<<<<< Updated upstream
        TopDownController()
        {
            ;
        }

        Transform* tTransform;

        void Start(UpdateEssentials* updateEssentials)
        {
            tTransform = gameObject->GetComponent<Transform>();
=======
        Rigidbody* rb;

        void Start(UpdateEssentials* updateEssentials)
        {
            rb = gameObject->GetComponent<Rigidbody>();
>>>>>>> Stashed changes
        }

        void Update(UpdateEssentials* updateEssentials)
        {
<<<<<<< Updated upstream
            tTransform->position = Camera::ScreenToWorldPos(Input::MousePosition(updateEssentials->screen), updateEssentials->screen);
=======
            if(Input::GetMouseButton(0))
            {
                gameObject->transform->position = Camera::ScreenToWorldPos(Input::MousePosition(updateEssentials->screen), updateEssentials->screen);
                rb->body->SetLinearVelocity(b2Vec2(0.0, 0.0));
            }
>>>>>>> Stashed changes
        }
};

void ExampleScene(sf::RenderWindow& screen)
{
    gameObjects.clear();
    int n = -1;
<<<<<<< Updated upstream
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
=======

    int m = 0;
    gameObjects.push_back(new GameObject("Player", Vector2(1, 0), 0.0, Vector2(1, 1)));
    n++;
    gameObjects[n]->AddComponent<SpriteRenderer>(new SpriteRenderer());
    m++;
    dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->spritePath = "./Assets/Characters/character_0000.png";
    gameObjects[n]->AddComponent<Rigidbody>(new Rigidbody());
    m++;
    dynamic_cast<Rigidbody*>(gameObjects[n]->components[m])->type = "dynamic";
    dynamic_cast<Rigidbody*>(gameObjects[n]->components[m])->isTrigger = false;
    gameObjects[n]->AddComponent<TopDownController>(new TopDownController());
    m++;

    m = 0;
    gameObjects.push_back(new GameObject("Ground", Vector2(10, 20), 0.0, Vector2(5, 1)));
    n++;
    gameObjects[n]->AddComponent<SpriteRenderer>(new SpriteRenderer());
    m++;
    dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->spritePath = "./Assets/Tiles/tile_0022.png";
    gameObjects[n]->AddComponent<Rigidbody>(new Rigidbody());
    m++;
    dynamic_cast<Rigidbody*>(gameObjects[n]->components[m])->type = "static";
    dynamic_cast<Rigidbody*>(gameObjects[n]->components[m])->isTrigger = false;

    m = 0;
    gameObjects.push_back(new GameObject("Camera"));
    n++;
    gameObjects[n]->AddComponent<Camera>(new Camera());
>>>>>>> Stashed changes
}