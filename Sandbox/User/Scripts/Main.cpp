#include <ECS/Component.h>
#include <Components/Transform.h>
#include <ECS/Scene.h>
#include <Components/ComponentRegister.h>
using namespace DT;

class TransformInspector : public Component
{
public:
    std::shared_ptr<Transform> transform;
    float speed = 2.5f, sensitivity = 75.f;
    glm::vec3 orientation;
    char dir = 'x';

    TransformInspector(Context *ctx) {}

    void Init(Context *ctx) override
    {
        transform = scene->Require<Transform>(entity).Fatal("TransformInspector::Init()");
    }

    void Tick(Context *ctx, const float &dt) override
    {
        if (dir == 'x')
            orientation.x += sensitivity * dt;
        if (dir == 'y')
            orientation.y += sensitivity * dt;
        if (dir == 'z')
            orientation.z += sensitivity * dt;
        transform->SetEulerRotation(orientation);
    }
};

REGISTER_COMPONENT(TransformInspector);