#include <Panels/ResourceInspectorPanel.h>

namespace DT
{
    void ResourceInspectorPanel::Start(Engine &engine)
    {
        resourceBrowser = Editor::GetPanel<ResourceBrowserPanel>();
        resourceBrowser->OnEvent(ResourceBrowserPanel::Events::OnItemSelect, [&](EventHandler *event)
                                 {
            ResourceBrowserPanel *rb = (ResourceBrowserPanel *)event;

            if (isItemSelected)
                ResourceInterface::GetInterface(extension)->CloseInspect();

            extension = rb->selectedItemPath.extension().string();

            if (ResourceInterface::HasInterface(extension))
            {
                ResourceInterface::GetInterface(extension)->OpenInspect(ResourceManager::GetRID(rb->selectedItemPath)); 
                isItemSelected = true;
            } });
    }

    void ResourceInspectorPanel::Update(Engine &engine)
    {
        ImGui::Begin(GetWindowName().c_str(), &isOpen);

        if (isItemSelected && ResourceInterface::HasInterface(extension))
            ResourceInterface::GetInterface(extension)->Inspect();

        ImGui::End();
    }
}