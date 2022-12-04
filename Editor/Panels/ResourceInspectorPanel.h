#pragma once

#include <functional>

#include <Panels/Panel.h>
#include <Panels/ResourceBrowserPanel.h>
#include <Editor.h>
#include <Panels/ResourceInterface.h>

namespace DT
{
    class ResourceInspectorPanel : public Panel
    {
    protected:
        ResourceBrowserPanel *resourceBrowser = nullptr;

        json loadedResource;
        std::filesystem::path loadedResourcePath;
        bool isItemSelected = false;
        std::string extension;

    public:
        inline std::string GetWindowName() override { return "Resource Inspector"; }

        void Start(Engine &engine) override;
        void Update(Engine &engine) override;
    };
}