#include "VulkanInstance.h"
#include "VulkanDebug.h"
#include <iostream>

static VKAPI_ATTR VkBool32 VKAPI_CALL
debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
              VkDebugUtilsMessageTypeFlagsEXT             messageType,
              const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

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

    VkApplicationInfo app_Info = {VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                  NULL,
                                  "Smart3D MVS",
                                  VK_MAKE_VERSION(1, 0, 0),
                                  "Smart3D MVS Vulkan Engine",
                                  VK_MAKE_VERSION(1, 0, 0),
                                  VK_API_VERSION_1_0};

    VkInstanceCreateInfo instance_info  = {};
    instance_info.sType                 = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_info.pApplicationInfo      = &app_Info;
    instance_info.enabledExtensionCount = static_cast<uint32_t>(m_instanceExtensions.size());
    instance_info.ppEnabledExtensionNames = m_instanceExtensions.data();

    if (m_hasEnableValidationLayers) {
        instance_info.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        instance_info.ppEnabledLayerNames = validationLayers.data();
    }
    else {
        instance_info.enabledLayerCount   = 0;
        instance_info.ppEnabledLayerNames = NULL;
    }

    VkDebugUtilsMessengerCreateInfoEXT dbg_messenger_create_info;
    dbg_messenger_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    dbg_messenger_create_info.pNext = NULL;
    dbg_messenger_create_info.flags = 0;
    dbg_messenger_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    dbg_messenger_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    dbg_messenger_create_info.pfnUserCallback = debugCallback;
    dbg_messenger_create_info.pUserData = NULL;
    if (m_hasEnableValidationLayers) {
        instance_info.pNext = &dbg_messenger_create_info;
    }
    else {
        instance_info.pNext = NULL;
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

