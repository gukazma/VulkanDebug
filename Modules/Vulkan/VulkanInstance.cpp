#include "VulkanInstance.h"
#include "VulkanDebug.h"
#include <iostream>

VulkanInstance::VulkanInstance(bool bValidLayers)
    : m_instance(VK_NULL_HANDLE)
    , m_enableSurface(false)
    , m_hasEnableValidationLayers(bValidLayers)
{
    AddInstanceExtension(VK_KHR_SURFACE_EXTENSION_NAME);
}

VulkanInstance* VulkanInstance::Create(bool bEnableSurface, bool bValidLayers)
{
    VulkanInstance* rnt = new VulkanInstance(true);
    if (!rnt->Init(true))
    {
        return nullptr;
    }
    
    return rnt;
}

bool VulkanInstance::Init(bool bEnableSurface) {
    m_enableSurface = bEnableSurface;
    if (m_hasEnableValidationLayers) {
        m_instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    }

    if (m_enableSurface) {
#if defined(_WIN32)
        AddInstanceExtension("VK_KHR_win32_surface");
#else
        AddInstanceExtension("VK_KHR_xcb_surface");
#endif
        if (m_hasEnableValidationLayers && !checkValidationLayerSupport()) {
            std::cout << "Validation layers requested, but not available!" << std::endl;
            return false;
        }
    }
}

size_t VulkanInstance::GetDeviceCount() const
{
    return size_t();
}

void VulkanInstance::AddInstanceExtension(const char* pszInstanceExtensionName)
{
    m_instanceExtensions.push_back(pszInstanceExtensionName);
}

