#pragma once

#include <stdio.h>

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

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

using B8  = uint8_t;
using B32 = uint32_t;

using IOS = std::ios;

template <typename T>
using Vector = std::vector<T>;

using String = std::string;

using StringStream = std::stringstream;

using InputFileStream = std::ifstream;

using OutputFileStream = std::ofstream;

using Vector3 = glm::vec3;

#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])