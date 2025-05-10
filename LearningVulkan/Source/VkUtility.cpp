#include "PCH.h"

#include "VkUtility.h"

vk::Result VkUtility::CreateInstance(bool debug, const char* appName, vk::Instance instance)
{
    if (debug) std::cout << "Creating Vulkan Instance\n\n";

    //Vulkan Version
    U32 version = 0;
    vkEnumerateInstanceVersion(&version);

    DEBUG_MESSAGE(debug, "System Supports Vulkan\n"); 
    DEBUG_MESSAGE(debug, "Variant: " << VK_API_VERSION_VARIANT(version) << '\n');
    DEBUG_MESSAGE(debug, "Major:   " << VK_API_VERSION_MAJOR(version)   << '\n');
    DEBUG_MESSAGE(debug, "Minor:   " << VK_API_VERSION_MINOR(version)   << '\n');
    DEBUG_MESSAGE(debug, "Patch:   " << VK_API_VERSION_PATCH(version)   << '\n\n');

    version &= ~(0xFFFU);

    //Application Info
    vk::ApplicationInfo appInfo = vk::ApplicationInfo
    (
        appName,
        version,
        "Vulkan Engine",
        VK_MAKE_API_VERSION(0, 1, 0, 0),
        NULL
    );

    //Get Required Extensions
    U32 glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (debug)
    {
        std::cout << "Requested Extensions:\n";
        for (const char* extensionName : extensions)
        {
            std::cout << '\t' << extensionName << '\n';
        }
        std::cout << '\n';
    }


    //Create Instance
    vk::InstanceCreateInfo instanceInfo = vk::InstanceCreateInfo
    (
        vk::InstanceCreateFlags(),
        &appInfo,
        0,
        nullptr,
        U32(extensions.size()),
        extensions.data()
    );

    return vk::createInstance(&instanceInfo, nullptr, &instance, nullptr);
}
