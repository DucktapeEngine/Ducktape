#include "../include/ducktape.h"
using namespace DT;

class PlayerController : public GameScript
{
public:
    Rigidbody* rb;

    void Start()
    {
        rb = gameObject->GetComponent<Rigidbody>();
    }

    void Update()
    {   
        if(Input::GetMouseButton(0))
        {
            gameObject->transform->SetPosition(Camera::ScreenToWorldPos(Input::mousePosition));
            rb->SetVelocity(Vector2(0.0f, 0.0f));
        }

        if(Input::GetKey(KeyCode::W))
        {
            rb->SetVelocity(Vector2(rb->GetVelocity().x, -20.0f));
        }
        rb->SetVelocity(Vector2(10.0f, rb->GetVelocity().y));
    }
};

class CameraController : public GameScript
{
public:
    GameObject* playerGO;

    void Start()
    {
        playerGO = GameObject::Find("Player");
    }

    void Update()
    {
        gameObject->transform->SetPosition(Vector2(playerGO->transform->GetPosition().x, 0.0f));
    }
};

class LevelGenerator : public GameScript
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

            barSR->Start();

            Rigidbody* barRB = bar->AddComponent<Rigidbody>();

            barRB->type = "static";

            barRB->Start();

            BoxCollider* barBC = bar->AddComponent<BoxCollider>();

            barBC->Start();

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

        DistanceJoint* playerDistanceJoint = player->AddComponent<DistanceJoint>();
        
        player->AddComponent<PlayerController>();

        // Create Camera gameObject

        GameObject* camera = GameObject::Instantiate("Camera", Vector2(0, 0), 0.0, Vector2(1, 1));
        
        camera->AddComponent<Camera>();
        camera->AddComponent<CameraController>();

        // Create levelGenerator gameObject

        GameObject* levelGenerator = GameObject::Instantiate("LevelGenerator");

        levelGenerator->AddComponent<LevelGenerator>();

        // create test object

        GameObject* anchor = GameObject::Instantiate("Anchor", Vector2(5, 0), 0.0, Vector2(2, 2));

        SpriteRenderer* anchorSpriteRenderer = anchor->AddComponent<SpriteRenderer>();
        anchorSpriteRenderer->spritePath = "../examples/assets/circle.png";
        anchorSpriteRenderer->pixelPerUnit = 25;
        anchorSpriteRenderer->color = Color(0, 0, 0, 255);

        Rigidbody* anchorRigidBody = anchor->AddComponent<Rigidbody>();
        anchorRigidBody->type = "dynamic";
        anchorRigidBody->linearDamping = 0.0f;
        anchorRigidBody->gravityScale = 1.0f;

        playerDistanceJoint->connectedRigidbody = anchorRigidBody;
    }
};

int main()
{
    // Initializing the Ducktape Engine
    ProjectSettings::windowTitle = "Flappy Bird";
    // ProjectSettings::resolution = Vector2(800.0f, 500.0f);
    ProjectSettings::sceneBackgroundColor = Color(232, 69, 69);
    ProjectSettings::globalGravity = Vector2(0.0f, 1.0f);

    ExampleScene exampleScene;
    Scene::LoadScene(&exampleScene);

    // This will take care of the rest of the Engine.
    DT::Update();

    return 0;
}