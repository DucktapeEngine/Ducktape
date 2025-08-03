// #include <components/component_register.h>
// #include <components/transform.h>
// #include <scene/component.h>
// #include <scene/scene.h>
// using namespace DT;

// class TransformInspector : public Component {
//   public:
//     std::shared_ptr<Transform> transform;
//     float speed = 2.5f, sensitivity = 75.f;
//     glm::vec3 orientation;
//     char dir = 'x';

//     TransformInspector(Context *ctx) {}

//     void Init(Context *ctx) override {
//         transform = scene->Require<Transform>(entity);
//     }

//     void Tick(Context *ctx, float dt) override {
//         if (dir == 'x')
//             orientation.x += sensitivity * dt;
//         if (dir == 'y')
//             orientation.y += sensitivity * dt;
//         if (dir == 'z')
//             orientation.z += sensitivity * dt;
//         transform->set_euler_rotation(orientation);
//     }
// };

// REGISTER_COMPONENT(transform_inspector);