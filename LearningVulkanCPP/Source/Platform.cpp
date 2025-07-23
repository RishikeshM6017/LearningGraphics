#include "PCH.h"
#include "Platform.h"

Window Platform::BuildWindow(I32 width, I32 height, const char* title)
{
    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    return glfwCreateWindow(width, height, title, NULL, NULL);
}
