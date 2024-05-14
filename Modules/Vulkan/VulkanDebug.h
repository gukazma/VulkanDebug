#pragma once
#include <vector>
#include <string>
#include <vulkan/vulkan.h>

extern const std::vector<const char*> validationLayers;

bool checkValidationLayerSupport();