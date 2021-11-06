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

class CameraController : public BehaviourScript
{
public:
    void Update()
    {
        gameObject->transform->SetPosition(gameObject->transform->GetPosition() + Vector2::Right() * 0.9f);
    }
};

class ExampleScene : public Scene
{
public:

    void Initialize()
    {
        int n = -1;
        int m;

        m = 0;
        GameObject::Instantiate("Player", Vector2(1, 0), 0.0, Vector2(2, 2));
        n++;

        gameObjects[n]->AddComponent<SpriteRenderer>(new SpriteRenderer());
        m++;
        dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->spritePath = "../examples/assets/circle.png";
        dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->pixelPerUnit = 25;
        dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->color = Color(43, 46, 74, 255);

        gameObjects[n]->AddComponent<Rigidbody>(new Rigidbody());
        m++;
        dynamic_cast<Rigidbody*>(gameObjects[n]->components[m])->type = "dynamic";
        dynamic_cast<Rigidbody*>(gameObjects[n]->components[m])->linearDamping = 0.0f;

        gameObjects[n]->AddComponent<BoxCollider>(new BoxCollider());
        m++;
        dynamic_cast<BoxCollider*>(gameObjects[n]->components[m])->isTrigger = false;
        dynamic_cast<BoxCollider*>(gameObjects[n]->components[m])->friction = 0.0f;

        gameObjects[n]->AddComponent<PlayerController>(new PlayerController());
        m++;

        m = 0;
        GameObject::Instantiate("Ground", Vector2(10, 20), 0.0, Vector2(2, 2));
        n++;

        gameObjects[n]->AddComponent<SpriteRenderer>(new SpriteRenderer());
        m++;
        dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->spritePath = "../examples/assets/square.png";
        dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->pixelPerUnit = 25;
        dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->color = Color(43, 46, 74, 255);

        gameObjects[n]->AddComponent<Rigidbody>(new Rigidbody());
        m++;
        dynamic_cast<Rigidbody*>(gameObjects[n]->components[m])->type = "static";

        gameObjects[n]->AddComponent<BoxCollider>(new BoxCollider());
        m++;
        dynamic_cast<BoxCollider*>(gameObjects[n]->components[m])->isTrigger = false;

        m = 0;
        GameObject::Instantiate("Camera", Vector2(-100, -100), 0.0, Vector2(1, 1));
        n++;
        gameObjects[n]->AddComponent<Camera>(new Camera());
        gameObjects[n]->AddComponent<CameraController>(new CameraController());
    }
};

int main()
{
    // Initializing the Ducktape Engine
    DT::ProjectSettings::windowTitle = "Flappy Bird";
    DT::ProjectSettings::sceneBackgroundColor = Color(232, 69, 69);
    DT::ProjectSettings::globalGravity = Vector2(0.0f, 1.0f);

    DT::Initialize();

    /* Each function is considered a scene. 
    The list below will initiate a new scene in the order of which they're called. 
    Note that it is possible to initiate a scene from another scene.
    Thus calling all of the scenes here is not important. */
    ExampleScene exampleScene;
    DT::Scene::LoadScene(&exampleScene);

    // This will take care of the rest of the Engine.
    DT::Update();

    return 0;
}