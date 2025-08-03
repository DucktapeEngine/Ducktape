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

#pragma once

#include <iostream>

#include <fmt/core.h>
#include <utils/math.h>

#include "components/first_person_controller.h"
#include "components/sprite_renderer.h"
#include "components/tag.h"
#include "core/context.h"
#include "core/input_manager.h"
#include "core/log.h"
#include "core/module.h"
#include "core/serialization.h"
#include "core/window.h"
#include "renderer/renderer.h"
#include "scene/scene_manager.h"

#ifdef DT_EDITOR
#include "editor.h"
#include "panels/hierarchy_panel.h"
#include "panels/inspector_panel.h"
#include "panels/world_view_panel.h"
#endif

#include <tracy/Tracy.hpp>

namespace dt {
class application_t {
  public:
    window_t window;
    renderer_t renderer;
    input_manager_t input_manager;
    scene_manager_t scene_manager;
    editor_t editor;

    tag_system_t tag_system;
    transform_system_t transform_system;
    camera_system_t camera_system;
    sprite_renderer_system_t sprite_renderer_system;
    first_person_controller_system_t first_person_controller_system;

    context_t context;

    entt::entity camera;

    application_t() : renderer(&window), input_manager(&window), editor(window) {
        scene_manager.bind<&tag_system_t::inspector>(tag_system, scene_manager.systems.inspector, stage_t::both);

        scene_manager.bind<&transform_system_t::inspector>(transform_system, scene_manager.systems.inspector, stage_t::both);

        scene_manager.bind<&camera_system_t::init>(camera_system, scene_manager.systems.init, stage_t::both);
        scene_manager.bind<&camera_system_t::tick>(camera_system, scene_manager.systems.tick, stage_t::both);
        scene_manager.bind<&camera_system_t::inspector>(camera_system, scene_manager.systems.inspector, stage_t::both);

        scene_manager.bind<&sprite_renderer_system_t::init>(sprite_renderer_system, scene_manager.systems.init, stage_t::both);
        scene_manager.bind<&sprite_renderer_system_t::render>(sprite_renderer_system, scene_manager.systems.render, stage_t::both);
        scene_manager.bind<&sprite_renderer_system_t::inspector>(sprite_renderer_system, scene_manager.systems.inspector, stage_t::both);

        scene_manager.bind<&first_person_controller_system_t::init>(first_person_controller_system, scene_manager.systems.init, stage_t::runtime);
        scene_manager.bind<&first_person_controller_system_t::tick>(first_person_controller_system, scene_manager.systems.tick, stage_t::runtime);
        scene_manager.bind<&first_person_controller_system_t::inspector>(first_person_controller_system, scene_manager.systems.inspector, stage_t::both);

        camera = scene_manager.scene.create();
        scene_manager.scene.emplace<tag_component>(camera).name = "Camera";
        scene_manager.scene.emplace<camera_component>(camera);

        entt::entity logo = scene_manager.scene.create();
        scene_manager.scene.emplace<tag_component>(logo).name = "Logo";
        scene_manager.scene.emplace<sprite_renderer_component>(logo).set_sprite("textures/logo.png");

        entt::entity nyan = scene_manager.scene.create();
        scene_manager.scene.emplace<tag_component>(nyan).name = "Nyan";
        scene_manager.scene.emplace<sprite_renderer_component>(nyan).set_sprite("textures/nyan.png");

        // editor
#ifdef DT_EDITOR
        editor.panels.push_back(std::make_shared<inspector_panel>());
        editor.panels.push_back(std::make_shared<hierarchy_panel>());
        editor.panels.push_back(std::make_shared<world_view_panel>());
#endif

        context = {&window, &scene_manager, &renderer, &input_manager, &editor};
        glfwSetWindowUserPointer(window.handle, reinterpret_cast<void *>(&context));
    }

    void run() {
#ifdef DT_EDITOR
        scene_manager.invoke_all(scene_manager.systems.init, stage_t::editor, &context);
        editor.start(&context);
#else
        scene_manager.invoke_all(scene_manager.systems.init, stage_t::runtime, &context);
#endif

        float last_time = 0.0f;
        while (!glfwWindowShouldClose(window.handle)) {
            glfwPollEvents();

            if (glfwWindowShouldClose(window.handle))
                break;

            float delta_time = glfwGetTime() - last_time;
            last_time = glfwGetTime();

            input_manager.process_input();

#ifdef DT_EDITOR
            editor.new_frame();
            editor.draw(&context, delta_time);
#endif

            renderer.render(context, delta_time);

#ifdef DT_EDITOR
            if (editor.current_state == editor_t::state::runtime)
                scene_manager.invoke_all(scene_manager.systems.tick, stage_t::runtime, &context, delta_time);
            else if (editor.current_state == editor_t::state::editor)
                scene_manager.invoke_all(scene_manager.systems.tick, stage_t::editor, &context, delta_time);
#else
            scene_manager.invoke_all(scene_manager.systems.tick, stage_t::runtime, &context, delta_time);
#endif

#ifdef DT_EDITOR
            editor.end_frame();
#endif
            input_manager.clear_tick_state();

            glfwSwapBuffers(window.handle);

            FrameMark;
        }
    }

    ~application_t() {
        asset<material_t>::cache.clear();
        asset<mesh_t>::cache.clear();
        asset<shader_t>::cache.clear();
        asset<texture_t>::cache.clear();
    }
};
} // namespace dt