#ifndef TRACY_VULKANRESOURCEMANAGER_H
#define TRACY_VULKANRESOURCEMANAGER_H

#include "VulkanInstance.h"

namespace Tracy
{
	class VulkanResourceFactory
	{
	public:
		explicit VulkanResourceFactory(const THandle& _hDevice);
		~VulkanResourceFactory();
	};
}

#endif // !TRACY_VULKANRESOURCEMANAGER_H