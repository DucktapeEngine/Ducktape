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

#include <fmt/core.h>

#include <utils/math.h>
#include <components/tag.h>
#include <components/sprite_renderer.h>
#include <core/context.h>
#include <core/serialization.h>
#include <core/window.h>
#include <core/input_manager.h>
#include <scene/scene_manager.h>
#include <renderer/renderer.h>
#include <core/module.h>
#include <core/log.h>

#include <editor.h>
#include <panels/export.h>
#include <panels/file_system.h>
#include <panels/game_view.h>
#include <panels/inspector.h>
#include <panels/world_outliner.h>
#include <panels/world_view.h>

using namespace DT;

class FreeLookCamera : public Component
{
public:
    std::shared_ptr<Transform> transform;
    std::shared_ptr<Camera> camera;
    Window *window;
    InputManager *input;

    glm::vec3 orientation;
    float speed = 2.5f, sensitivity = 75.f;

    float lastx;

    FreeLookCamera(Context *ctx) {}

    void Init(Context *ctx) override
    {
        transform = scene->Require<Transform>(entity);
        camera = scene->Require<Camera>(entity);
        window = ctx->GetService<Window>();
        input = ctx->GetService<InputManager>();
    }

    void Tick(Context *ctx, const float &dt) override
    {
        if (camera->isOrthographic)
        {
            if (input->IsKeyHeld(KEY_W))
                transform->translation += speed * dt * transform->Up();
            if (input->IsKeyHeld(KEY_A))
                transform->translation -= speed * dt * transform->Right();
            if (input->IsKeyHeld(KEY_S))
                transform->translation -= speed * dt * transform->Up();
            if (input->IsKeyHeld(KEY_D))
                transform->translation += speed * dt * transform->Right();

            transform->translation.z = -3.f;
            transform->SetEulerRotation({0.f, 180.f, 0.f});
        }
        else
        {
            if (input->IsKeyHeld(KEY_W))
                transform->translation += speed * dt * transform->Forward();
            if (input->IsKeyHeld(KEY_A))
                transform->translation -= speed * dt * transform->Right();
            if (input->IsKeyHeld(KEY_S))
                transform->translation -= speed * dt * transform->Forward();
            if (input->IsKeyHeld(KEY_D))
                transform->translation += speed * dt * transform->Right();
            if (input->IsKeyHeld(KEY_SPACE))
                transform->translation += speed * dt * glm::vec3(0.f, 1.f, 0.f);
            if (input->IsKeyHeld(KEY_LEFT_SHIFT))
                transform->translation -= speed * dt * glm::vec3(0.f, 1.f, 0.f);
            if (input->IsKeyHeld(KEY_E))
                orientation.z += sensitivity * dt;
            if (input->IsKeyHeld(KEY_Q))
                orientation.z -= sensitivity * dt;

            // Look
            orientation.y += input->GetMouseDelta().x * sensitivity * dt;
            orientation.x += -input->GetMouseDelta().y * sensitivity * dt;

            if (orientation.x < -90.0f)
                orientation.x = -90.0f;
            if (orientation.x > 90.0f)
                orientation.x = 90.0f;

            orientation = glm::angNormalize(orientation);
            transform->SetEulerRotation(orientation);
            transform->LookAt(glm::vec3(1.f, 0.f, 0.f));
        }
    }
};

int main(int argc, char *argv[])
{
    std::filesystem::path projectPath;
    if (argc > 1)
        projectPath = std::filesystem::absolute(std::filesystem::path(argv[1]));
    else
        projectPath = std::filesystem::current_path();

    // if (!std::filesystem::exists(projectPath / "DucktapeProjectSettings.json"))
    // {
    //     LOG("Project does not exist at given path: {}\nPlease open the project through the launcher.", (projectPath / "DucktapeProjectSettings.json").generic_string());
    //     return 1;
    // }

    // json projectData = json::parse(std::ifstream(projectPath / "DucktapeProjectSettings.json"));
    std::cout << "Opened project at " << projectPath << "\n";

    Context context;
    context.projectPath = projectPath;

    Window window(context);
    context.AttachService(&window);

#ifdef _WIN32
    Module gameModule(std::filesystem::current_path() / "DucktapeProject.dll");
#endif
#ifdef __linux__
    Module gameModule(std::filesystem::current_path() / "DucktapeProject.so");
#endif
    context.AttachService(&gameModule);

    // SceneManager
    SceneManager sceneManager(context);
    context.AttachService(&sceneManager);

    // Renderer
    Renderer renderer(context);
    context.AttachService(&renderer);
#ifdef DT_EXPORT
    renderer.SetRenderFrameBuffer(true);
#endif

    // Input
    InputManager input(context);
    context.AttachService(&input);

    // Scene
    Entity logo = sceneManager.activeScene.CreateEntity();
    sceneManager.activeScene.Require<Tag>(logo)->name = "Logo";
    sceneManager.activeScene.Require<SpriteRenderer>(logo)->SetSprite(projectPath / "user" / "textures" / "logo.png");
    // sceneManager.activeScene.Assign("TransformInspector", logo);

    Entity nyan = sceneManager.activeScene.CreateEntity();
    sceneManager.activeScene.Require<Tag>(nyan)->name = "Nyan";
    sceneManager.activeScene.Require<Transform>(nyan)->translation = glm::vec3(1.f, 0.f, 0.f);
    sceneManager.activeScene.Require<SpriteRenderer>(nyan)->SetSprite(projectPath / "user" / "textures" / "nyan.png");
    // sceneManager.activeScene.Assign("TransformInspector", nyan);

    Entity logo2 = sceneManager.activeScene.CreateEntity();
    sceneManager.activeScene.Require<Tag>(logo2)->name = "Logo2";
    sceneManager.activeScene.Require<Transform>(logo2)->translation = glm::vec3(2.f, 0.f, 0.f);
    sceneManager.activeScene.Require<SpriteRenderer>(logo2)->SetSprite(projectPath / "user" / "textures" / "logo.png");
    // sceneManager.activeScene.Assign("TransformInspector", logo2);

    Entity camera = sceneManager.activeScene.CreateEntity();
    sceneManager.activeScene.Require<Tag>(camera)->name = "Main Camera";
    sceneManager.activeScene.Require<Camera>(camera);
    sceneManager.activeScene.Require<Transform>(camera)->translation = glm::vec3(0.f, 0.f, -3.f);
    sceneManager.activeScene.Get<Transform>(camera)->LookAt(glm::vec3(1.f, 0.f, 0.f));
    sceneManager.activeScene.Require<FreeLookCamera>(camera);

    // Editor
#ifndef DT_EXPORT
    Editor editor(context);
    context.AttachService<Editor>(&editor);

    ExportPanel exportPanel;
    FileSystemPanel fileSystem;
    GameViewPanel gameView;
    InspectorPanel inspector;
    WorldOutlinerPanel worldOutliner;
    WorldViewPanel worldView(context);

    editor.AttachPanel(&exportPanel);
    editor.AttachPanel(&fileSystem);
    editor.AttachPanel(&gameView);
    editor.AttachPanel(&inspector);
    editor.AttachPanel(&worldOutliner);
    editor.AttachPanel(&worldView);

    editor.Init(context);
#endif

    sceneManager.Init(&context);

    float lastTime = 0.0f;
    while (window.IsOpen())
    {
        window.PollEvents();
#ifdef DT_EXPORT
        if (!window.IsFocused())
            continue;
#endif

        float deltaTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();

        if (!window.IsOpen())
            break;

        input.Process();
#ifndef DT_EXPORT
        editor.NewFrame();
        editor.Tick(context, deltaTime);
#endif
        renderer.BeginScene(Camera::GetActiveCamera());
        sceneManager.Tick(&context, deltaTime);
        renderer.EndScene();
#ifndef DT_EXPORT
        renderer.BeginScene(&worldView.editorCamera);
        worldView.editorCamera.Recalculate(&window);
        sceneManager.EditorTick(&context, deltaTime);
        renderer.EndScene();
        editor.EndFrame();
#endif
        window.SwapBuffers();
    }

    Shader::ClearCache(context);

    return 0;
}