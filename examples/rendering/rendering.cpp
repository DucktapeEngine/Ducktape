#include <Ducktape/ducktape.h>
using namespace DT;

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
        Entity* cam = Entity::Instantiate("Camera");
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
    }
};

int main()
{
    ProjectSettings::Application::windowTitle = "Rendering";
    ProjectSettings::SceneManagement::initialScene = new Rendering();

    Init();
    return 0;
}