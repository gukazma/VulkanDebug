#include <gtest/gtest.h>
#include "VulkanInstance.h"
TEST(Smart3DTest,Test1)
{
    auto vulkaninstance = VulkanInstance::Create(true, true);
    EXPECT_TRUE(vulkaninstance);
}