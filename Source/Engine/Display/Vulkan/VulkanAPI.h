#ifndef VULKANAPI_H
#define VULKANAPI_H

#if defined(_WIN32) || defined(WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#include <vulkan/vulkan.hpp>
#pragma comment(lib, "vulkan-1.lib")

#endif // !VULKANAPI_H
