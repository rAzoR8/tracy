#ifndef VULKANINITIALIZER_H
#define VULKANINITIALIZER_H

#include "Singleton.h"

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan\vulkan.hpp>
#include <vector>

namespace Tracy
{
	class VulkanInitializer //: public hlx::Singleton<VulkanInitializer>
	{
	public:
		VulkanInitializer();
		~VulkanInitializer();

	private:
		vk::Instance m_Instance = nullptr;
	};

	VulkanInitializer::VulkanInitializer()
	{
		vk::ApplicationInfo AppInfo{};
		AppInfo.apiVersion = VK_API_VERSION_1_0;
		AppInfo.applicationVersion = 0u;
		AppInfo.engineVersion = 666u;
		AppInfo.pEngineName = "Tracy";
		AppInfo.pApplicationName = "TracyApp";

		vk::InstanceCreateInfo CreateInfo{};
		CreateInfo.pApplicationInfo = &AppInfo;

		std::vector<const char*> Extensions = { VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME };

#ifdef _DEBUG
		Extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		const char* pDebugLayer = "VK_LAYER_LUNARG_standard_validation";
		CreateInfo.ppEnabledLayerNames = &pDebugLayer;
		CreateInfo.enabledLayerCount = 1u;
#endif // DEBUG

		CreateInfo.ppEnabledExtensionNames = Extensions.data();
		CreateInfo.enabledExtensionCount = static_cast<uint32_t>(Extensions.size());

		m_Instance = vk::createInstance(CreateInfo);
	}

	VulkanInitializer::~VulkanInitializer()
	{
		if (m_Instance)
		{
			m_Instance.destroy();
		}
	}
}; // Tracy

#endif // !VULKANINITIALIZER_H