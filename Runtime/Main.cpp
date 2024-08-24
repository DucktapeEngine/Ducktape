/*
MIT License

Copyright (c) 2021 - 2023 Aryan Baburajan

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

// #define DT_EXPORT

#include <Utils/math.h>
#include <Components/Tag.h>
#include <Components/SpriteRenderer.h>
#include <Core/Context.h>
#include <Core/Serialization.h>
#include <Core/Window.h>
#include <Core/InputManager.h>
#include <ECS/SceneManager.h>
#include <Renderer/Renderer.h>
#include <Core/Module.h>

#include <Editor.h>
#include <Panels/Export.h>
#include <Panels/FileSystem.h>
#include <Panels/GameView.h>
#include <Panels/Inspector.h>
#include <Panels/WorldOutliner.h>
#include <Panels/WorldView.h>

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
        PROFILE();

        transform = scene->Require<Transform>(entity).Fatal("FreeLookCamera::Init()");
        camera = scene->Require<Camera>(entity).Fatal("FreeLookCamera::Init()");
        window = ctx->GetService<Window>().Fatal("FreeLookCamera::Init()");
        input = ctx->GetService<InputManager>().Fatal("FreeLookCamera::Init()");
    }

    void Tick(Context *ctx, const float &dt) override
    {
        PROFILE();

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
    PROFILE();

    // Project
    std::filesystem::path projectPath;
    if (argc > 1)
        projectPath = std::filesystem::absolute(std::filesystem::path(argv[1]));
    else
        projectPath = std::filesystem::current_path();

    if (!std::filesystem::exists(projectPath / "DucktapeProjectSettings.json"))
    {
        std::cout << "[ERR] Project does not exist at given path: " << (projectPath / "DucktapeProjectSettings.json").generic_string() << "\nPlease open the project through the launcher.\n";
        return 1;
    }

    json projectData = json::parse(std::ifstream(projectPath / "DucktapeProjectSettings.json"));
    std::cout << "[LOG] Opened project at " << projectPath / "DucktapeProjectSettings.json"
              << "\n";

    // Context
    Context context;
    context.projectPath = projectPath;

    // Window
    Error err;
    Window window(context, projectData.value("window", json::object()), &err);
    err.Fatal("main()");
    context.AttachService(&window).Fatal("main()");

    // Module
#ifdef _WIN32
    Module gameModule(std::filesystem::current_path() / "DucktapeProject.dll", &err);
#endif
#ifdef __linux__
    Module gameModule(std::filesystem::current_path() / "DucktapeProject.so", &err);
#endif
    err.Fatal("main()");
    context.AttachService(&gameModule).Fatal("main()");

    // SceneManager
    SceneManager sceneManager(context, projectData.value("sceneManager", json::object()));
    context.AttachService(&sceneManager).Fatal("main()");

    // Renderer
    Renderer renderer(context, projectData.value("renderer", json::object()));
    context.AttachService(&renderer).Fatal("main()");
#ifdef DT_EXPORT
    renderer.SetRenderFrameBuffer(true);
#endif

    // Input
    InputManager input(context);
    context.AttachService(&input).Fatal("main()");

    // Scene
    Entity logo = sceneManager.activeScene.CreateEntity();
    sceneManager.activeScene.Require<Tag>(logo).Fatal("main()")->name = "Logo";
    sceneManager.activeScene.Require<SpriteRenderer>(logo).Fatal("main()")->SetSprite(projectPath / "User" / "Textures" / "logo.png");
    // sceneManager.activeScene.Assign("TransformInspector", logo).Fatal("main()");

    Entity nyan = sceneManager.activeScene.CreateEntity();
    sceneManager.activeScene.Require<Tag>(nyan).Fatal("main()")->name = "Nyan";
    sceneManager.activeScene.Require<Transform>(nyan).Fatal("main()")->translation = glm::vec3(1.f, 0.f, 0.f);
    sceneManager.activeScene.Require<SpriteRenderer>(nyan).Fatal("main()")->SetSprite(projectPath / "User" / "Textures" / "nyan.png");
    // sceneManager.activeScene.Assign("TransformInspector", nyan).Fatal("main()");

    Entity logo2 = sceneManager.activeScene.CreateEntity();
    sceneManager.activeScene.Require<Tag>(logo2).Fatal("main()")->name = "Logo2";
    sceneManager.activeScene.Require<Transform>(logo2).Fatal("main()")->translation = glm::vec3(2.f, 0.f, 0.f);
    sceneManager.activeScene.Require<SpriteRenderer>(logo2).Fatal("main()")->SetSprite(projectPath / "User" / "Textures" / "logo.png");
    // sceneManager.activeScene.Assign("TransformInspector", logo2).Fatal("main()");

    Entity camera = sceneManager.activeScene.CreateEntity();
    sceneManager.activeScene.Require<Tag>(camera).Fatal("main()")->name = "Main Camera";
    sceneManager.activeScene.Require<Camera>(camera).Fatal("main()");
    sceneManager.activeScene.Require<Transform>(camera).Fatal("main()")->translation = glm::vec3(0.f, 0.f, -3.f);
    sceneManager.activeScene.Get<Transform>(camera).Fatal("main()")->LookAt(glm::vec3(1.f, 0.f, 0.f));
    sceneManager.activeScene.Require<FreeLookCamera>(camera).Fatal("main()");

    // Editor
#ifndef DT_EXPORT
    Editor editor(context);
    context.AttachService<Editor>(&editor).Fatal("main()");

    ExportPanel exportPanel;
    FileSystemPanel fileSystem;
    GameViewPanel gameView;
    InspectorPanel inspector;
    WorldOutlinerPanel worldOutliner;
    WorldViewPanel worldView(context);

    editor.AttachPanel(&exportPanel).Fatal("main()");
    editor.AttachPanel(&fileSystem).Fatal("main()");
    editor.AttachPanel(&gameView).Fatal("main()");
    editor.AttachPanel(&inspector).Fatal("main()");
    editor.AttachPanel(&worldOutliner).Fatal("main()");
    editor.AttachPanel(&worldView).Fatal("main()");

    editor.Init(context);
#endif

    sceneManager.Init(&context);

    // Game Loop
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
        renderer.BeginScene(Camera::GetActiveCamera().get());
#ifdef DT_EXPORT
        sceneManager.Tick(&context, deltaTime);
#endif
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