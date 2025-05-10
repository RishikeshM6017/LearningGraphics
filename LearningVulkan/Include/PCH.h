#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

typedef uint32_t U32;

#define U32(x) static_cast<U32>(x)

#define DEBUG_MESSAGE(x, y) if (x) std::cout << y