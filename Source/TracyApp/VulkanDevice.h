#ifndef VULKANDEVICE_H
#define VULKANDEVICE_H

#include "VulkanAPI.h"

namespace Tracy
{
	class VulkanDevice 
	{
		friend class VulkanInitializer;

	public:
		VulkanDevice(const vk::PhysicalDevice& _PhysDevice);
		~VulkanDevice();

		const vk::PhysicalDeviceProperties& GetProperties() const;
		const vk::PhysicalDeviceMemoryProperties& GetMemoryProperties() const;
		const uint64_t GetTotalMemory() const;

	private:
		vk::PhysicalDevice m_PhysicalDevice;
		vk::Device m_Device;
		vk::PhysicalDeviceProperties m_Properties;
		vk::PhysicalDeviceMemoryProperties m_MemoryProperties;
		uint64_t m_uTotalMemory;
	};

	inline const vk::PhysicalDeviceProperties & Tracy::VulkanDevice::GetProperties() const
	{
		return m_Properties;
	}

	inline const vk::PhysicalDeviceMemoryProperties & VulkanDevice::GetMemoryProperties() const
	{
		return m_MemoryProperties;
	}

	inline const uint64_t VulkanDevice::GetTotalMemory() const
	{
		return m_uTotalMemory;
	}

	bool operator<(const VulkanDevice& lDev, const VulkanDevice& rDev);
} // Tracy

#endif // !VULKANDEVICE_H
