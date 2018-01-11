#ifndef TRACY_VULKANDEVICE_H
#define TRACY_VULKANDEVICE_H

#include "../IDevice.h"

#include "VulkanAPI.h"
#include "StandardDefines.h"
#include "VulkanMemoryAllocator.h"
#include "VulkanTypeConversion.h"
#include "Display/DisplayTypes.h"
#include "Async/AsyncTask.h"

#include <unordered_map>
#include <mutex>

namespace Tracy
{
	constexpr uint32_t kInvalidQueueIndex = UINT32_MAX;

	class VulkanDevice : public IDevice
	{
		friend class VulkanInstance;
		friend class VulkanTexture;
		friend class VulkanRenderGraph;
		friend class VulkanRenderPass;

	public:
		explicit VulkanDevice(const vk::PhysicalDevice& _PhysDevice, const THandle _uHandle);
		~VulkanDevice();		

		// todo: make this stuff private

		// Getters
		const vk::PhysicalDeviceProperties& GetProperties() const;
		const uint64_t GetTotalMemory() const;
		const uint32_t GetQueueIndex(const vk::QueueFlagBits _kQueueType) const;
		
		const vk::PhysicalDevice& GetAdapter() const;
		const vk::Device& GetDevice() const;
		const THandle& GetHandle() const;

		// Methods
		const bool PresentSupport(vk::SurfaceKHR& _Surface, const vk::QueueFlagBits _kQueueType = vk::QueueFlagBits::eGraphics) const;

		explicit operator bool() const
		{
			return m_Device && m_PhysicalDevice;
		}

		//---------------------------------------------------------------------------------------------------
		// DEVICE CALLS

		// any overload
#ifndef DeviceFunc
#define DeviceFunc(_funcName) \
		template <class ...Args> \
		inline auto _funcName(Args ... _Args) { return make_task([&]() { std::lock_guard<std::mutex> lock(m_Mutex); return m_Device._funcName(_Args...); }); }
#endif

		DeviceFunc(createDescriptorPool)
		DeviceFunc(destroyDescriptorPool)

		DeviceFunc(createDescriptorSetLayout)
		DeviceFunc(destroyDescriptorSetLayout)

		DeviceFunc(createPipelineLayout)
		DeviceFunc(destroyPipelineLayout)

		DeviceFunc(createPipelineCache)
		DeviceFunc(destroyPipelineCache)

		DeviceFunc(getPipelineCacheData)

		DeviceFunc(createGraphicsPipelines)
		DeviceFunc(destroyPipeline)

	private:
		bool Initialize();

		// Textures
		const bool CreateTexture(const TextureDesc& _Desc, VulkanAllocation& _Allocation, vk::Image& _Image);

		const bool CreateCommandBuffers(const vk::QueueFlagBits _kQueueType, const vk::CommandPoolCreateFlagBits _kBufferType, const vk::CommandBufferLevel _kLevel, vk::CommandBuffer* _pOutBuffers, const uint32_t _uCount = 1u);

		const bool DestroyCommandBuffers(const vk::QueueFlagBits _kQueueType, const vk::CommandPoolCreateFlagBits _kBufferType, vk::CommandBuffer* _pBuffers, const uint32_t _uCount = 1u);

		const bool CreateSampler(const SamplerDesc& _Desc, vk::Sampler& _OutSampler);

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

		std::mutex m_Mutex;
		vk::PhysicalDevice m_PhysicalDevice;
		vk::Device m_Device;
		vk::PhysicalDeviceProperties m_Properties;
		std::unordered_map<vk::QueueFlagBits, Queue> m_Queues;

		struct CommandPoolEntry
		{
			vk::CommandPool ResetPool;
			vk::CommandPool TransientPool;
		};

		std::vector<CommandPoolEntry> m_CommandPools; // one for each family index

		// Allocator
		VulkanMemoryAllocator* m_pAllocator;
	};

	//---------------------------------------------------------------------------------------------------
	inline const vk::PhysicalDeviceProperties& Tracy::VulkanDevice::GetProperties() const
	{
		return m_Properties;
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
