#include <Ducktape/ducktape.h>
using namespace DT;

class Parallax : public BehaviourScript {
public:
    float div = 1.f;

    void tick()
    {
        Vector2 pos(entity->transform->getPosition().x - (Input::mousePosition.x - Application::getResolution().x/2), entity->transform->getPosition().y - (Input::mousePosition.y - Application::getResolution().y/2));
        pos = pos / div;

        entity->transform->setPosition(pos);
    }
};

class Rendering : public Scene {
public:
    void init()
    {
        Entity* cam = Entity::instantiate("Camera");
        cam->addComponent<Camera>();

        for (int i = 1; i <= 4; i++) 
        {
            Entity* entity = Entity::instantiate(std::to_string(i));

            SpriteRenderer* sr = entity->addComponent<SpriteRenderer>();
            sr->setSpritePath("../assets/" + std::to_string(i) + ".png");
            sr->setPixelPerUnit(2);

            Parallax* par = entity->addComponent<Parallax>();
            par->div = i * -30;
        }
    }
};

int main()
{
    ProjectSettings::sceneBackgroundColor = Color(238,238,238);
    SceneManager::loadScene<Rendering>();

    init();
    return 0;
}