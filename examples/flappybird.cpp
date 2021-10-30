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
            gameObject->transform->position = Camera::ScreenToWorldPos(Input::mousePosition);
            rb->velocity = Vector2(0.0f, 0.0f);
        }

        if(Input::GetKey(KeyCode::W))
        {
            rb->velocity.y = -20.0f;
        }
        rb->velocity.x = 10.0f;
    }
};

void ExampleScene()
{
    gameObjects.clear();
    int n = -1;
    int m;

    m = 0;
    gameObjects.push_back(new GameObject("Sky", Vector2(0, 0), 0.0, Vector2(10, 10)));
    n++;

    gameObjects[n]->AddComponent<SpriteRenderer>(new SpriteRenderer());
    m++;
    dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->spritePath = "../examples/assets/blue_square.png";
    dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->pixelPerUnit = 1;

    m = 0;
    gameObjects.push_back(new GameObject("Player", Vector2(1, 0), 0.0, Vector2(2, 2)));
    n++;

    gameObjects[n]->AddComponent<SpriteRenderer>(new SpriteRenderer());
    m++;
    dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->spritePath = "../examples/assets/yellow_circle.png";
    dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->pixelPerUnit = 30;

    gameObjects[n]->AddComponent<Rigidbody>(new Rigidbody());
    m++;
    dynamic_cast<Rigidbody*>(gameObjects[n]->components[m])->type = "dynamic";

    gameObjects[n]->AddComponent<BoxCollider>(new BoxCollider());
    m++;
    dynamic_cast<BoxCollider*>(gameObjects[n]->components[m])->isTrigger = false;

    gameObjects[n]->AddComponent<PlayerController>(new PlayerController());
    m++;

    m = 0;
    gameObjects.push_back(new GameObject("Ground", Vector2(10, 20), 0.0, Vector2(2, 2)));
    n++;

    gameObjects[n]->AddComponent<SpriteRenderer>(new SpriteRenderer());
    m++;
    dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->spritePath = "../examples/assets/green_square.png";
    dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->pixelPerUnit = 30;

    gameObjects[n]->AddComponent<Rigidbody>(new Rigidbody());
    m++;
    dynamic_cast<Rigidbody*>(gameObjects[n]->components[m])->type = "static";

    gameObjects[n]->AddComponent<BoxCollider>(new BoxCollider());
    m++;
    dynamic_cast<BoxCollider*>(gameObjects[n]->components[m])->isTrigger = false;

    m = 0;
    gameObjects.push_back(new GameObject("Camera"));
    n++;
    gameObjects[n]->AddComponent<Camera>(new Camera());
}

int main()
{
    // Initializing the Ducktape Engine
    DT::Initialize();

    /* Each function is considered a scene. 
    The list below will initiate a new scene in the order of which they're called. 
    Note that it is possible to initiate a scene from another scene.
    Thus calling all of the scenes here is not important. */
    ExampleScene();

    // This will take care of the rest of the Engine.
    DT::Update();

    return 0;
}