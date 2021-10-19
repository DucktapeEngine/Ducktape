#include "ducktape.hpp"

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
            Vector2 move = Vector2(0.0, rb->velocity.y);

            move.x += 10.0f;
            if(Input::GetKey(KeyCode::W))
            {
                move.y = -20.0;
            }
            rb->velocity = move;
        }
};

void ExampleScene()
{
    gameObjects.clear();
    int n = -1;
    int m;  

    m = 0;
    gameObjects.push_back(new GameObject("Player", Vector2(1, 0), 0.0, Vector2(1, 1)));
    n++;
    gameObjects[n]->AddComponent<SpriteRenderer>(new SpriteRenderer());
    m++;
    dynamic_cast<SpriteRenderer*>(gameObjects[n]->components[m])->spritePath = "./Assets/Characters/character_0000.png";
    gameObjects[n]->AddComponent<Rigidbody>(new Rigidbody());
    m++;
    dynamic_cast<Rigidbody*>(gameObjects[n]->components[m])->type = "dynamic";
    dynamic_cast<Rigidbody*>(gameObjects[n]->components[m])->isTrigger = false;
    gameObjects[n]->AddComponent<PlayerController>(new PlayerController());
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