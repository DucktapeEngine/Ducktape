/*
MIT License

Copyright (c) 2021 - 2025 Aryan Baburajan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <random>

#include "components/first_person_controller.h"
#include "components/sprite_renderer.h"
#include "components/tag.h"
#include "core/application.h"

using namespace dt;

class billboard_component {
  public:
};

class billboard_system_t {
    transform_component *camera_transform;

  public:
    void init(context_t *ctx) {
        auto view = ctx->scene_manager->scene.view<camera_component>();
        camera_transform = &ctx->scene_manager->scene.get<transform_component>(view.front());
    }

    void tick(context_t *ctx, float dt) {
        auto view = ctx->scene_manager->scene.view<billboard_component, transform_component>();
        for (auto [billboard, transform] : view.each()) {
            transform.set_euler_rotation(glm::vec3(0.f, camera_transform->get_euler_rotation().y, 0.f));
        }
    }
};

int main(int argc, char *argv[]) {
    // std::filesystem::path project_path = std::filesystem::current_path();

#ifdef DT_EDITOR
    // LOG("opened project at {} ", project_path.string());
#endif

    application_t app;

    billboard_system_t billboard_system;
    app.scene_manager.bind<&billboard_system_t::init>(billboard_system, app.scene_manager.systems.init, stage_t::both);
    app.scene_manager.bind<&billboard_system_t::tick>(billboard_system, app.scene_manager.systems.tick, stage_t::both);

    {
        entt::entity camera = app.scene_manager.scene.create();
        app.scene_manager.scene.emplace<tag_component>(camera).name = "Camera";
        app.scene_manager.scene.emplace<camera_component>(camera);
        auto &transform = app.scene_manager.scene.emplace<transform_component>(camera);
        auto &fps = app.scene_manager.scene.emplace<first_person_controller_component>(camera);
        fps.body_transform = fps.head_transform = &transform;
        {
            entt::entity inventory = app.scene_manager.scene.create();
            app.scene_manager.scene.emplace<tag_component>(inventory).name = "Inventory";
            app.scene_manager.scene.emplace<transform_component>(inventory).scale = glm::vec3(0.5f);
            auto &joint = app.scene_manager.scene.emplace<joint_component>(inventory);
            joint.joined_transform = &transform;
            joint.offset.position = glm::vec3(0.f, 0.f, 0.5f);
            app.scene_manager.scene.emplace<sprite_renderer_component>(inventory)
                .set_sprite("textures/inventory.png");
        }
    }
    {
        // entt::entity bike = app.scene_manager.scene.create();
        // app.scene_manager.scene.emplace<tag_component>(bike).name = "Bike";
        // app.scene_manager.scene.emplace<transform_component>(bike);
        // app.scene_manager.scene.emplace<model_renderer_component>(bike).model_asset.load("models/bike/source/shirokocycle.glb");
        // app.scene_manager.scene.emplace<model_filter_component>(bike).model.load("models/nanashi-mumei/source/Nanashi_Mumei.fbx");
        // app.scene_manager.scene.emplace<model_renderer_component>(bike).material_asset->texture_assets.emplace("diffuse", "models/nanashi-mumei/textures/Skin.png");
    }
    {
        entt::entity ground = app.scene_manager.scene.create();
        app.scene_manager.scene.emplace<tag_component>(ground).name = "Ground";
        auto &transform = app.scene_manager.scene.emplace<transform_component>(ground);
        transform.position = glm::vec3(0.f, -1.f, 0.f);
        transform.set_euler_rotation({90.f, 0.f, 0.f});
        transform.scale = glm::vec3(10.f, 10.f, 1.f);
        app.scene_manager.scene.emplace<sprite_renderer_component>(ground).set_sprite("textures/ground.png");
    }
    {
        entt::entity mountains = app.scene_manager.scene.create();
        app.scene_manager.scene.emplace<tag_component>(mountains).name = "Mountains";
        auto &transform = app.scene_manager.scene.emplace<transform_component>(mountains);
        transform.position = glm::vec3(0.f, 0.f, 60.f);
        transform.scale = glm::vec3(90.f, 60.f, 1.f);
        app.scene_manager.scene.emplace<sprite_renderer_component>(mountains).set_sprite("textures/mountains.png");
    }
    {
        entt::entity castle = app.scene_manager.scene.create();
        app.scene_manager.scene.emplace<tag_component>(castle).name = "Castle";
        auto &transform = app.scene_manager.scene.emplace<transform_component>(castle);
        transform.position = glm::vec3(0.f, 20.f, 50.f);
        transform.scale = glm::vec3(50.f);
        app.scene_manager.scene.emplace<sprite_renderer_component>(castle).set_sprite("textures/castle.png");
    }
    {
        float width = 5.f;
        float depth = 50.f;
        float spacing = 1.f;
        float jitter_amount = 0.5f;

        std::mt19937 rng(std::random_device{}());
        std::uniform_real_distribution<float> jitter(-jitter_amount, jitter_amount);

        auto &scene = app.scene_manager.scene;

        auto create_cross_tree = [&](float x, float z, int index) {
            glm::vec3 base_position = glm::vec3(x, 0.f, z);
            glm::vec3 jittered_position = base_position + glm::vec3(jitter(rng), 0.f, jitter(rng));
            glm::vec3 scale = glm::vec3(1.f, 1.5f, 1.f);

            // quad 1
            {
                entt::entity tree = scene.create();
                scene.emplace<tag_component>(tree).name = "Tree_" + std::to_string(index) + "_A";

                auto &transform = scene.emplace<transform_component>(tree);
                transform.position = jittered_position;
                transform.scale = scale;
                transform.set_euler_rotation(glm::vec3(0.f, 0.f, 0.f));

                scene.emplace<sprite_renderer_component>(tree).set_sprite("textures/tree.png");
            }
            // quad 2 (rotated)
            {
                entt::entity tree = scene.create();
                scene.emplace<tag_component>(tree).name = "Tree_" + std::to_string(index) + "_B";

                auto &transform = scene.emplace<transform_component>(tree);
                transform.position = jittered_position;
                transform.scale = scale;
                transform.set_euler_rotation(glm::vec3(0.f, 90.f, 0.f));

                scene.emplace<sprite_renderer_component>(tree).set_sprite("textures/tree.png");
            }
        };

        int tree_id = 0;
        for (float x = -width; x <= width; ++x) {
            if (x == 0.f)
                continue;
            for (float z = 0.f; z < depth; ++z) {
                create_cross_tree(x * spacing, z * spacing, tree_id++);
            }
        }
    }

    app.run();

    return 0;
}