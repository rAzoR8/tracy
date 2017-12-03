#ifndef TRACY_VULKANDEVICE_H
#define TRACY_VULKANDEVICE_H

#include "../IDevice.h"

#include "VulkanAPI.h"
#include "StandardDefines.h"
#include "VulkanTexture.h"
#include <unordered_map>

namespace Tracy
{
	constexpr uint32_t kInvalidQueueIndex = UINT32_MAX;

	class VulkanDevice : public IDevice
	{
		friend class VulkanInstance;

	public:
		explicit VulkanDevice(const vk::PhysicalDevice& _PhysDevice, const THandle _uHandle);
		~VulkanDevice();

		// Getters
		const vk::PhysicalDeviceProperties& GetProperties() const;
		const vk::PhysicalDeviceMemoryProperties& GetMemoryProperties() const;
		const uint64_t GetTotalMemory() const;
		const uint32_t GetQueueIndex(const vk::QueueFlagBits _QueueType) const;
		
		const vk::PhysicalDevice& GetAdapter() const;
		const vk::Device& GetDevice() const;
		const THandle& GetHandle() const;

		// Methods
		const bool PresentSupport(vk::SurfaceKHR& _Surface, const vk::QueueFlagBits _QueueType = vk::QueueFlagBits::eGraphics) const;
		
		// Textures
		const THandle CreateRenderTarget(const uint32_t _uWidth, const uint32_t _uHeight, const vk::Format _kFormat);

		explicit operator bool() const
		{
			return m_Device && m_PhysicalDevice;
		}

	private:
		void Create();

	private:
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

			Queue() :
				uFamilyIndex(kInvalidQueueIndex),
				Handle(nullptr)
			{}
		};

		// Device and Queues
		vk::PhysicalDevice m_PhysicalDevice;
		vk::Device m_Device;
		vk::PhysicalDeviceProperties m_Properties;
		vk::PhysicalDeviceMemoryProperties m_MemoryProperties;
		std::unordered_map<vk::QueueFlagBits, Queue> m_Queues;

		// Base address of memory blocks
		vk::DeviceMemory m_TextureMemory;
		vk::DeviceMemory m_BufferMemory;

		// Texture Tables
		std::unordered_map<THandle, VulkanRenderTexture> m_RenderTargets;
		THandle m_hNextRenderTarget = 0u;
	};

	//---------------------------------------------------------------------------------------------------
	inline const vk::PhysicalDeviceProperties& Tracy::VulkanDevice::GetProperties() const
	{
		return m_Properties;
	}

	//---------------------------------------------------------------------------------------------------
	inline const vk::PhysicalDeviceMemoryProperties& VulkanDevice::GetMemoryProperties() const
	{
		return m_MemoryProperties;
	}

	//---------------------------------------------------------------------------------------------------
	inline const uint64_t VulkanDevice::GetTotalMemory() const
	{
		return m_Info.uTotalMemory;
	}

	//---------------------------------------------------------------------------------------------------
	inline const uint32_t VulkanDevice::GetQueueIndex(const vk::QueueFlagBits _QueueType) const
	{
		auto queuePair = m_Queues.find(_QueueType);
		// No need to check, all available queue types are created on device init
		return queuePair->second.uFamilyIndex;
	}

	//---------------------------------------------------------------------------------------------------
	inline const vk::PhysicalDevice& VulkanDevice::GetAdapter() const
	{
		return m_PhysicalDevice;
	}

	//---------------------------------------------------------------------------------------------------
	inline const vk::Device& VulkanDevice::GetDevice() const
	{
		return m_Device;
	}

	//---------------------------------------------------------------------------------------------------
	inline const THandle& VulkanDevice::GetHandle() const
	{
		return m_Info.hHandle;
	}

	//---------------------------------------------------------------------------------------------------
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
