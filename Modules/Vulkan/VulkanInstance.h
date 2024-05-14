#pragma once
#include <vulkan/vulkan.h>
#include <vector>
class VulkanInstance
{
public:
    VulkanInstance(bool bValidLayers);
    ~VulkanInstance();

    static VulkanInstance* Create(bool bEnableSurface, bool bValidLayers = false);
    bool                   Init(bool bEnableSurface);
    size_t                 GetDeviceCount() const;
    void                   AddInstanceExtension(const char* pszInstanceExtensionName);

private:
    VkInstance m_instance;
    VkDebugUtilsMessengerCreateInfoEXT dbg_messenger_create_info;
    bool                               m_enableSurface;
    bool                               m_hasEnableValidationLayers;
    std::vector<const char*>           m_instanceExtensions;
};