#pragma once

namespace Ducktape
{
    class Shader
    {
    public:
        VkShaderModule shaderModule;

        Shader(const std::string &filePath, VkDevice &device)
        {
            shaderModule = CreateShaderModule(AssetManager::ReadFile(filePath), device);
        }

        void LoadShader(const std::string filePath, VkDevice &device)
        {
            shaderModule = CreateShaderModule(AssetManager::ReadFile(filePath), device);
        }

        VkShaderModule CreateShaderModule(const std::vector<char> &code, VkDevice &device)
        {
            VkShaderModuleCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            createInfo.codeSize = code.size();
            createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());

            VkShaderModule shaderModule;
            if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to create shader module!");
            }

            return shaderModule;
        }
    };
}