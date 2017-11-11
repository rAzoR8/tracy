#ifndef ENGINE_HPP
#define ENGINE_HPP

#if defined(_WIN32) || defined(WIN32)
#include "Platform\Win32\Win32Application.h"
#include "Display\DX12\DX12Instance.h"
#endif

#include "Display\Vulkan\VulkanInstance.h"

#endif // !ENGINE_HPP

