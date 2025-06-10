#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX


#include <stdio.h>
#include <assert.h>

#include <cstdint>
#include <type_traits>
#include <vector>
#include <optional>
#include <thread>

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif


using U8  = uint8_t;
using U16 = uint16_t;
using U32 = uint32_t;
using U64 = uint64_t;

using I8  = int8_t;
using I16 = int16_t;
using I32 = int32_t;
using I64 = int64_t;

using F32 = float;
using F64 = double;

using B8 = uint8_t;
using B32 = uint32_t;

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using Optional = std::optional<T>;

using Thread = std::thread;


#define U32(x) static_cast<U32>(x)


STATIC_ASSERT(sizeof(U8)  == 1, "U8  is not 1 byte ");
STATIC_ASSERT(sizeof(U16) == 2, "U16 is not 2 bytes");
STATIC_ASSERT(sizeof(U32) == 4, "U32 is not 4 bytes");
STATIC_ASSERT(sizeof(U64) == 8, "U64 is not 8 bytes");

STATIC_ASSERT(sizeof(I8)  == 1, "I8  is not 1 byte ");
STATIC_ASSERT(sizeof(I16) == 2, "I16 is not 2 bytes");
STATIC_ASSERT(sizeof(I32) == 4, "I32 is not 4 bytes");
STATIC_ASSERT(sizeof(I64) == 8, "I64 is not 8 bytes");

STATIC_ASSERT(sizeof(F32) == 4, "F32 is not 4 bytes");
STATIC_ASSERT(sizeof(F64) == 8, "F64 is not 8 bytes");

STATIC_ASSERT(sizeof(B8)  == 1, "B8  is not 1 byte ");
STATIC_ASSERT(sizeof(B32) == 4, "B32 is not 4 bytes");