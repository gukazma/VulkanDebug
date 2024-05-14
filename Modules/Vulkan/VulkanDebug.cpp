#include "VulkanDebug.h"
#include <iostream>
const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

bool checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const auto& layerName : validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            std::cout << "checkValidationLayerSupport: Can not find layer = " << layerName
                      << std::endl;
            return false;
        }
    }

    return true;
}
