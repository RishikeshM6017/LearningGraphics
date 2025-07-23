#pragma once

#include "PCH.h"

#include "Logger.h"

vk::Instance BuildInstance(const char* engineName, Deque<Function<void()>>& deletionQueue);


