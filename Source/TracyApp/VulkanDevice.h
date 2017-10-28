#ifndef VULKANDEVICE_H
#define VULKANDEVICE_H

#include "VulkanAPI.h"
#include <unordered_map>

namespace Tracy
{
	constexpr uint32_t kInvalidQueueIndex = UINT32_MAX;

	class VulkanDevice 
	{
		friend class VulkanInitializer;

	public:
		VulkanDevice(const vk::PhysicalDevice& _PhysDevice);
		~VulkanDevice();

		const vk::PhysicalDeviceProperties& GetProperties() const;
		const vk::PhysicalDeviceMemoryProperties& GetMemoryProperties() const;
		const uint64_t GetTotalMemory() const;
		const uint32_t GetQueueIndex(const vk::QueueFlagBits _QueueType) const;
		/*const std::vector<vk::SurfaceFormatKHR> GetSurfaceFormats(vk::SurfaceKHR& _Surface);
		const std::vector<vk::PresentModeKHR> GetSurfacePresentModes(vk::SurfaceKHR& _Surface);
		const vk::SurfaceCapabilitiesKHR GetSurfaceCapabilities(vk::SurfaceKHR& _Surface);*/
		
		const vk::PhysicalDevice& GetPhysicalHandle() const;
		const vk::Device& GetLogicalHandle() const;

		const bool PresentSupport(vk::SurfaceKHR& _Surface, const vk::QueueFlagBits _QueueType=vk::QueueFlagBits::eGraphics) const
		{
			// Check if given queue is supported by the implementation
			const auto& QueueIndexPair = m_Queues.find(_QueueType);
			if (QueueIndexPair != m_Queues.cend() || QueueIndexPair->second.uFamilyIndex == kInvalidQueueIndex)
			{
				return false;
			}

			return m_PhysicalDevice.getSurfaceSupportKHR(QueueIndexPair->second.uFamilyIndex, _Surface);
		}

	private:
		void Create();

		struct QueueOffset
		{
			uint32_t uFamilyIndex;
			uint32_t uOffset;

			QueueOffset(const uint32_t _uFamilyIndex, const uint32_t _uOffset) :
				uFamilyIndex(_uFamilyIndex),
				uOffset(_uOffset)
			{}
		};

		struct Queue
		{
			uint32_t uFamilyIndex;
			vk::Queue Handle;

			/*Queue(const uint32_t _uFamilyIndex, const vk::Queue _QueueHandle) :
				uFamilyIndex(_uFamilyIndex),
				Handle(_QueueHandle)
			{}*/

			Queue() :
				uFamilyIndex(kInvalidQueueIndex),
				Handle(nullptr)
			{}
		};

		vk::PhysicalDevice m_PhysicalDevice;
		vk::Device m_Device;
		vk::PhysicalDeviceProperties m_Properties;
		vk::PhysicalDeviceMemoryProperties m_MemoryProperties;
		uint64_t m_uTotalMemory;
		std::unordered_map<vk::QueueFlagBits, Queue> m_Queues;
	};
	//---------------------------------------------------------------------------------------------------

	inline const vk::PhysicalDeviceProperties& Tracy::VulkanDevice::GetProperties() const
	{
		return m_Properties;
	}

	inline const vk::PhysicalDeviceMemoryProperties& VulkanDevice::GetMemoryProperties() const
	{
		return m_MemoryProperties;
	}

	inline const uint64_t VulkanDevice::GetTotalMemory() const
	{
		return m_uTotalMemory;
	}

	inline const uint32_t VulkanDevice::GetQueueIndex(const vk::QueueFlagBits _QueueType) const
	{
		auto queuePair = m_Queues.find(_QueueType);
		// No need to check, all available queue types are created on device init
		return queuePair->second.uFamilyIndex;
	}

	/*inline const std::vector<vk::SurfaceFormatKHR> VulkanDevice::GetSurfaceFormats(vk::SurfaceKHR& _Surface)
	{
		return m_PhysicalDevice.getSurfaceFormatsKHR(_Surface);
	}

	inline const std::vector<vk::PresentModeKHR> VulkanDevice::GetSurfacePresentModes(vk::SurfaceKHR& _Surface)
	{
		return m_PhysicalDevice.getSurfacePresentModesKHR(_Surface);
	}

	inline const vk::SurfaceCapabilitiesKHR VulkanDevice::GetSurfaceCapabilities(vk::SurfaceKHR& _Surface)
	{
		return m_PhysicalDevice.getSurfaceCapabilitiesKHR(_Surface);
	}*/

	inline const vk::PhysicalDevice& VulkanDevice::GetPhysicalHandle() const
	{
		return m_PhysicalDevice;
	}

	inline const vk::Device& VulkanDevice::GetLogicalHandle() const
	{
		return m_Device;
	}

	inline bool operator<(const VulkanDevice& lDev, const VulkanDevice& rDev)
	{
		if (lDev.GetProperties().deviceType == rDev.GetProperties().deviceType)
		{
			return lDev.GetTotalMemory() < rDev.GetTotalMemory();
		}
		else
		{
			return std::abs((int)vk::PhysicalDeviceType::eDiscreteGpu - (int)lDev.GetProperties().deviceType) <
				std::abs((int)vk::PhysicalDeviceType::eDiscreteGpu - (int)rDev.GetProperties().deviceType);
		}
	}
} // Tracy

#endif // !VULKANDEVICE_H
