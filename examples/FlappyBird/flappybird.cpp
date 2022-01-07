#include <Ducktape/ducktape.h>
using namespace DT;

class PlayerController : public GameScript
{
public:
    Rigidbody2D* rb;

    void Start()
    {
        rb = entity->GetComponent<Rigidbody2D>();
    }

    void Update()
    {   
        if(Input::GetMouseButton(0))
        {
            entity->transform->SetPosition(Camera::ScreenToWorldPos(Input::mousePosition));
            rb->SetVelocity(Vector2(0.0f, 0.0f));
        }

        if(Input::GetKeyDown(KeyCode::W))
        {
            rb->SetVelocity(Vector2(rb->GetVelocity().x, -20.0f));
        }
        rb->SetVelocity(Vector2(10.0f, rb->GetVelocity().y));
    }
};

class CameraController : public GameScript
{
public:
    Entity* playerGO;

    void Start()
    {
        playerGO = Entity::Find("Player");
    }

    void Update()
    {
        entity->transform->SetPosition(Vector2(playerGO->transform->GetPosition().x, 0.f));
    }
};

class LevelGenerator : public GameScript
{
public:
    float timeBetweenBar = 2.0f;
    float elapsedTime;
    int count = 0;

    Entity* playerGO = nullptr;

    void Start()
    {
        playerGO = Entity::Find("Player");
    }

    void Update()
    {
        elapsedTime += Time::deltaTime;
        if(elapsedTime >= timeBetweenBar)
        {
            elapsedTime = 1.0f;

            // Creating a new bar

            Entity* bar = Entity::Instantiate("Bar " + std::to_string(count));
            bar->transform->SetPosition(Vector2(playerGO->transform->GetPosition().x + 10.0f, Random::Range(20.0f, 40.0f)));
            bar->transform->SetScale(Vector2(3.0f, 10.0f));

            SpriteRenderer* barSR = bar->AddComponent<SpriteRenderer>();

            barSR->spritePath = "../assets/square.png";
            barSR->pixelPerUnit = 25;
            barSR->color = Color(43, 46, 74, 255);

            barSR->Start();

            Rigidbody2D* barRB = bar->AddComponent<Rigidbody2D>();

            barRB->SetType(BodyType::staticBody);

            barRB->Start();

            BoxCollider2D* barBC = bar->AddComponent<BoxCollider2D>();

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
        // Create player entity
        Entity* player = Entity::Instantiate("Player", Vector2(1, 0), 0.0, Vector2(2, 2));

        SpriteRenderer* playerSpriteRenderer = player->AddComponent<SpriteRenderer>();
        playerSpriteRenderer->spritePath = "../assets/circle.png";
        playerSpriteRenderer->pixelPerUnit = 25;
        playerSpriteRenderer->color = Color(43, 46, 74, 255);

        Rigidbody2D* playerRigidbody2D = player->AddComponent<Rigidbody2D>();
        playerRigidbody2D->SetType(BodyType::dynamicBody);
        playerRigidbody2D->SetDamping(0.0f);

        BoxCollider2D* playerBoxCollider2D = player->AddComponent<BoxCollider2D>();
        playerBoxCollider2D->SetIsTrigger(false);
        playerBoxCollider2D->SetFriction(0.0f);
        
        player->AddComponent<PlayerController>();

        // Create Camera entity

        Entity* camera = Entity::Instantiate("Camera", Vector2(0, 0), 0.0, Vector2(1, 1));
        
        camera->AddComponent<Camera>();
        camera->AddComponent<CameraController>();

        // Create levelGenerator entity

        Entity* levelGenerator = Entity::Instantiate("LevelGenerator");

        levelGenerator->AddComponent<LevelGenerator>();

        AudioSource* aud = levelGenerator->AddComponent<AudioSource>();
        aud->Load("../assets/sound.wav", false);
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
    SceneManager::LoadScene(&exampleScene);

    // This will take care of the rest of the Engine.
    Update();

    return 0;
}