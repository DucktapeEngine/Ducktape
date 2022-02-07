#include <Ducktape/ducktape.h>
using namespace DT;

class MouseHandler : public BehaviourScript {
public:
    SpriteRenderer* spriteRenderer;
    float lerp = 0.5f;
    Vector2 offset;
    int mouseButton = 0;

    void Init()
    {
        spriteRenderer = entity->GetComponent<SpriteRenderer>();
    }

    void Tick()
    {
        Color targetColor(0, 0, 0);
        if (Input::GetMouseButton(mouseButton)) {
            targetColor = Color(240,84,84);
        }
        else
        {
            targetColor = Color(255,255,255);
        }

        Color currentColor = Color::Lerp(spriteRenderer->GetColor(), targetColor, lerp);
        spriteRenderer->SetColor(currentColor);

        entity->transform->SetPosition(Camera::ScreenToWorldPos(Input::mousePosition) + offset);
    }
};

class KeyHandler : public BehaviourScript {
public:
    SpriteRenderer* spriteRenderer;
    float lerp = 0.5f;
    KeyCode key;

    void Init()
    {
        spriteRenderer = entity->GetComponent<SpriteRenderer>();
    }

    void Tick()
    {
        Color targetColor(0, 0, 0);
        if (Input::GetKey(key)) {
            targetColor = Color(240,84,84);
        }
        else
        {
            targetColor = Color(255,255,255);
        }
        
        Color currentColor = Color::Lerp(spriteRenderer->GetColor(), targetColor, lerp);
        spriteRenderer->SetColor(currentColor);
    }

    KeyHandler* SetKey(KeyCode key)
    {
        this->key = key;
        return this;
    }
};

class InputScene : public Scene {
public:
    void Init()
    {
        Entity* cam = Entity::Instantiate("Camera");
        cam->AddComponent<Camera>()->backgroundColor = Color(18,18,18);

        float scale = 10.f;

        Entity* entity = Entity::Instantiate("a", Vector2(-1.f * scale, 0.f), 0.f, Vector2(0.5f, 0.5f));

        entity->AddComponent<SpriteRenderer>()->SetSpritePath("../assets/a.png");

        entity->AddComponent<KeyHandler>()->SetKey(KeyCode::A);

        entity = Entity::Instantiate("s", Vector2(0.f, 0.f), 0.f, Vector2(0.5f, 0.5f));

        entity->AddComponent<SpriteRenderer>()->SetSpritePath("../assets/s.png");

        entity->AddComponent<KeyHandler>()->SetKey(KeyCode::S);

        entity = Entity::Instantiate("d", Vector2(1.f * scale, 0.f), 0.f, Vector2(0.5f, 0.5f));

        entity->AddComponent<SpriteRenderer>()->SetSpritePath("../assets/d.png");

        entity->AddComponent<KeyHandler>()->SetKey(KeyCode::D);

        entity = Entity::Instantiate("w", Vector2(0.f, -1.025f * scale), 0.f, Vector2(0.5f, 0.5f));

        entity->AddComponent<SpriteRenderer>()->SetSpritePath("../assets/w.png");

        entity->AddComponent<KeyHandler>()->SetKey(KeyCode::W);

        entity = Entity::Instantiate("space", Vector2(0.f, 1.025f * scale), 0.f, Vector2(0.5f, 0.5f));

        entity->AddComponent<SpriteRenderer>()->SetSpritePath("../assets/space.png");

        entity->AddComponent<KeyHandler>()->SetKey(KeyCode::Space);

        entity = Entity::Instantiate("mouseLeft", Vector2(0.f, 0.f), 0.f, Vector2(0.25f, 0.25f));

        entity->AddComponent<SpriteRenderer>()->SetSpritePath("../assets/mouse.png");

        MouseHandler* mouseHandler = entity->AddComponent<MouseHandler>();
        mouseHandler->offset = Vector2(-1.f, -1.f) * 3.f;
        mouseHandler->mouseButton = 0;

        entity = Entity::Instantiate("mouseRight", Vector2(0.f, 0.f), 0.f, Vector2(0.25f, 0.25f));

        entity->AddComponent<SpriteRenderer>()->SetSpritePath("../assets/mouse.png");

        mouseHandler = entity->AddComponent<MouseHandler>();
        mouseHandler->offset = Vector2(1.f, -1.f) * 3.f;
        mouseHandler->mouseButton = 1;

        entity = Entity::Instantiate("mouse", Vector2(0.f, 0.f), 0.f, Vector2(0.5f, 0.5f));

        entity->AddComponent<SpriteRenderer>()->SetSpritePath("../assets/mouse.png");

        mouseHandler = entity->AddComponent<MouseHandler>();
        mouseHandler->offset = Vector2(0.f, 2.1f) * 3.f;
        mouseHandler->mouseButton = -1;
    }
};

int main()
{
    ProjectSettings::Application::windowTitle = "Input";
    ProjectSettings::SceneManagement::initialScene = new InputScene();

    Init();
    return 0;
}