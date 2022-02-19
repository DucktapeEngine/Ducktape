#include <Ducktape/ducktape.h>
using namespace DT;

class MousePointer : public BehaviourScript {
public:
    void Tick()
    {
        // Get the mouse position
        auto mousePos = Input::mousePosition;

        // Get the mouse position in world space
        auto worldPos = Camera::ScreenToWorldPos(mousePos);

        // Set the transform position to the mouse position
        entity->transform->SetPosition(worldPos);
    }
};

class Parallax : public BehaviourScript {
public:
    float div = 1.f;

    void Tick()
    {
        Vector2 pos(entity->transform->SetPosition().x - (Input::mousePosition.x - Application::GetResolution().x/2), entity->transform->SetPosition().y - (Input::mousePosition.y - Application::GetResolution().y/2));
        pos = pos / div;

        entity->transform->SetPosition(pos);
    }
};

class Rendering : public Scene {
public:
    void Init()
    {
        Entity* cam = Entity::Instantiate("Camera", Vector2(0.f, 0.f), 0.f, Vector2(1.f, 1.f));
        cam->AddComponent<Camera>()->backgroundColor = Color(238,238,238);;

        for (int i = 1; i <= 4; i++) 
        {
            Entity* entity = Entity::Instantiate(std::to_string(i));

            SpriteRenderer* sr = entity->AddComponent<SpriteRenderer>();
            sr->SetSpritePath("../assets/" + std::to_string(i) + ".png");
            sr->SetPixelPerUnit(2);

            Parallax* par = entity->AddComponent<Parallax>();
            par->div = i * -30;
        }

        // Cursor
        Entity* cursor = Entity::Instantiate("Cursor");
        cursor->AddComponent<SpriteRenderer>()
            ->SetSpritePath("../assets/cursor.png")
            ->SetPixelPerUnit(2);
        cursor->AddComponent<MousePointer>();
    }
};

int main()
{
    ProjectSettings::Application::windowTitle = "Rendering";
    ProjectSettings::SceneManagement::initialScene = new Rendering();

    Init();
    return 0;
}