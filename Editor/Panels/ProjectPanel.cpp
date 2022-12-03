#include <Panels/ProjectPanel.h>

namespace DT
{
    void ProjectPanel::Update(Engine &engine)
    {
        ImGui::Begin("Project", &isOpen);

        Configuration &config = engine.project.config;

        ImGui::Vec2("window size", &config.windowSize);
        ImGui::InputText("window title", &config.windowTitle);
        ImGui::Vec3("version", &config.version);
        ImGui::InputInt("target FPS", &config.targetFPS);
        ImGui::Checkbox("draw wireframe", &config.drawWireframe);
        ImGui::Checkbox("vsync", &config.vsync);
        ImGui::Checkbox("hide window", &config.hideWindow);
        ImGui::Checkbox("draw to quad", &config.drawToQuad);

        if (ImGui::Button("Apply"))
            engine.project.Save();

        ImGui::End();
    }
}