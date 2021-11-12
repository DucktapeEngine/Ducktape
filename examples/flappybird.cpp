#include "ducktape.h"
using namespace DT;

class PlayerController : public BehaviourScript
{
public:
    Rigidbody* rb;

    void Start()
    {
        rb = gameObject->GetComponent<Rigidbody>();
    }

    void Update()
    {
        if(Input::GetKey(KeyCode::W))
        {
            rb->SetVelocity(Vector2(rb->GetVelocity().x, -20.0f));
        }
        rb->SetVelocity(Vector2(10.0f, rb->GetVelocity().y));
    }
};

class CameraController : public BehaviourScript
{
public:
    void Update()
    {
        gameObject->transform->SetPosition(gameObject->transform->GetPosition() + Vector2::Right() * 0.9f);
    }
};

class LevelGenerator : public BehaviourScript
{
public:
    float timeBetweenBar = 2.0f;
    float elapsedTime;
    int count = 0;

    GameObject* playerGO = nullptr;

    void Start()
    {
        playerGO = GameObject::Find("Player");
    }

    void Update()
    {
        elapsedTime += Time::deltaTime;
        if(elapsedTime >= timeBetweenBar)
        {
            elapsedTime = 1.0f;

            // Creating a new bar

            GameObject* bar = GameObject::Instantiate("Bar " + std::to_string(count));
            bar->transform->SetPosition(Vector2(playerGO->transform->GetPosition().x + 10.0f, Random::Range(20.0f, 40.0f)));
            bar->transform->SetScale(Vector2(3.0f, 10.0f));

            SpriteRenderer* barSR = bar->AddComponent<SpriteRenderer>();

            barSR->spritePath = "../examples/assets/square.png";
            barSR->pixelPerUnit = 25;
            barSR->color = Color(43, 46, 74, 255);

            Rigidbody* barRB = bar->AddComponent<Rigidbody>();

            barRB->type = "static";

            BoxCollider* barBC = bar->AddComponent<BoxCollider>();

            count++;
        }
    }
};

class ExampleScene : public Scene
{
public:

    void Initialize()
    {
        // Create player gameObject
        GameObject* player = GameObject::Instantiate("Player", Vector2(1, 0), 0.0, Vector2(2, 2));

        SpriteRenderer* playerSpriteRenderer = player->AddComponent<SpriteRenderer>();
        playerSpriteRenderer->spritePath = "../examples/assets/circle.png";
        playerSpriteRenderer->pixelPerUnit = 25;
        playerSpriteRenderer->color = Color(43, 46, 74, 255);

        Rigidbody* playerRigidBody = player->AddComponent<Rigidbody>();
        playerRigidBody->type = "dynamic";
        playerRigidBody->linearDamping = 0.0f;

        BoxCollider* playerBoxCollider = player->AddComponent<BoxCollider>();
        playerBoxCollider->isTrigger = false;
        playerBoxCollider->friction = 0.0f;

        player->AddComponent<PlayerController>();

        // Create Camera gameObject

        GameObject* camera = GameObject::Instantiate("Camera", Vector2(-10, -10), 0.0, Vector2(1, 1));
        
        camera->AddComponent<Camera>();
        camera->AddComponent<CameraController>();

        // Create levelGenerator gameObject

        GameObject* levelGenerator = GameObject::Instantiate("LevelGenerator");

        levelGenerator->AddComponent<LevelGenerator>();
    }
};

int main()
{
    // Initializing the Ducktape Engine
    DT::ProjectSettings::windowTitle = "Flappy Bird";
    DT::ProjectSettings::sceneBackgroundColor = Color(232, 69, 69);
    DT::ProjectSettings::globalGravity = Vector2(0.0f, 1.0f);

    ExampleScene exampleScene;
    DT::Scene::LoadScene(&exampleScene);

    // This will take care of the rest of the Engine.
    DT::Update();

    return 0;
}