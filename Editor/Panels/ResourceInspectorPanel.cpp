#include <Panels/ResourceInspectorPanel.h>

namespace DT
{
    void ResourceInspectorPanel::Start(ContextPtr &ctx)
    {
        resourceBrowser = Editor::GetPanel<ResourceBrowserPanel>();
        resourceBrowser->OnEvent(ResourceBrowserPanel::Events::OnItemSelect, [&](EventHandler *event)
                                 {
            ResourceBrowserPanel *rb = (ResourceBrowserPanel *)event;

            if (isItemSelected)
                ResourceInterface::GetInterface(extension)->CloseInspect(ctx);

            extension = rb->selectedItemPath.extension().string();

            if (ResourceInterface::HasInterface(extension))
            {
                ResourceInterface::GetInterface(extension)->OpenInspect(ctx.resourceManager->GetRID(rb->selectedItemPath), ctx); 
                isItemSelected = true;
            } });
    }

    void ResourceInspectorPanel::Update(ContextPtr &ctx)
    {
        ImGui::Begin(GetWindowName().c_str(), &isOpen);

        if (isItemSelected && ResourceInterface::HasInterface(extension))
            ResourceInterface::GetInterface(extension)->Inspect(ctx);

        ImGui::End();
    }
}