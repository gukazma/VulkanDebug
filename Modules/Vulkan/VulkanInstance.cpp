#include "VulkanInstance.h"

VulkanInstance::VulkanInstance(bool bValidLayers)
    : m_instance(VK_NULL_HANDLE)
    , m_enableSurface(false)
    , m_hasEnableValidationLayers(bValidLayers)
{
    AddInstanceExtension(VK_KHR_SURFACE_EXTENSION_NAME);
}

void VulkanInstance::AddInstanceExtension(const char* pszInstanceExtensionName) {
    m_instanceExtensions.push_back(pszInstanceExtensionName);
}
