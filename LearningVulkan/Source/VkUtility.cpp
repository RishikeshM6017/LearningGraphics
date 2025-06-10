#include "PCH.h"
#include "VkUtility.h"

#define VK_TEST(x) assert(x == VK_SUCCESS)

#define VK_CHECK(x, msg) if (x!= VK_SUCCESS) printf(msg);

VkResult Vulkan::CreateInstance(VkApplicationInfo* pAppInfo, Vector<const char*> layers, Vector<const char*> extensions, VkInstance* pInstance)
{
    VkInstanceCreateInfo instanceInfo = {};
    instanceInfo.sType                      = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pNext                      = nullptr;
    instanceInfo.flags                      = 0;
    instanceInfo.pApplicationInfo           = pAppInfo;
    instanceInfo.enabledLayerCount          = U32(layers.size());
    instanceInfo.ppEnabledLayerNames        = layers.data();
    instanceInfo.enabledExtensionCount      = U32(extensions.size());
    instanceInfo.ppEnabledExtensionNames    = extensions.data();

    return vkCreateInstance(&instanceInfo, nullptr, pInstance);
}

VkResult Vulkan::PickPhysicalDevice(VkInstance instance, VkPhysicalDevice* pPhysicalDevice)
{
    U32 physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);

    Vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data());

    for (const auto& physicalDevice : physicalDevices)
    {
        return VK_SUCCESS;
    }

    *pPhysicalDevice = physicalDevices[0];

    return VK_SUBOPTIMAL_KHR;
}

Vector<const char*> Vulkan::GetRequiredInstanceExtensions()
{
    Vector<const char*> extensions = { "VK_LAYER_KHRONOS_validation" };

    return extensions;
}

Vector<const char*> Vulkan::GetRequiredInstanceLayers()
{
    Vector<const char*> extensions = {};

    U32 glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    return Vector<const char*>();
}
