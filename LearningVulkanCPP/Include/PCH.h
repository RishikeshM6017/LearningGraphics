#pragma once

#include <stdio.h>

#include <vector>
#include <atomic>
#include <thread>

#include "vulkan/vulkan.hpp"
#include "GLFW/glfw3.h"

using U8 = uint8_t;
using U16 = uint16_t;
using U32 = uint32_t;
using U64 = uint64_t;

using I8 = int8_t;
using I16 = int16_t;
using I32 = int32_t;
using I64 = int64_t;

using F32 = float;
using F64 = double;

using B8  = bool;
using B32 = uint32_t;

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using Atomic = std::atomic<T>;

using Thread = std::thread;

using Window = GLFWwindow*;
