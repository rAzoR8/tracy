#ifndef VULKANINITIALIZER_H
#define VULKANINITIALIZER_H

#include "Singleton.h"
#include "VulkanDevice.h"
#include <vector>

namespace Tracy
{
	class VulkanInitializer : public hlx::Singleton<VulkanInitializer>
	{
	public:
		VulkanInitializer();
		~VulkanInitializer();

		VulkanDevice& GetDevice(const uint32_t _uIndex = 0u);
		const VulkanDevice& GetDevice(const uint32_t _uIndex = 0u) const;

	private:
		vk::Instance m_Instance = nullptr;
		std::vector<VulkanDevice> m_Devices;
	};

	inline VulkanDevice & VulkanInitializer::GetDevice(const uint32_t _uIndex)
	{
		return m_Devices[_uIndex];
	}
	inline const VulkanDevice & VulkanInitializer::GetDevice(const uint32_t _uIndex) const
	{
		return m_Devices[_uIndex];
	}
}; // Tracy

#endif // !VULKANINITIALIZER_H