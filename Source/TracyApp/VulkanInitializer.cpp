#include "VulkanInitializer.h"

Tracy::VulkanInitializer::VulkanInitializer()
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

	if (m_Instance)
	{
		// enumerate devices

		for (auto& Device : m_Instance.enumeratePhysicalDevices())
		{
			m_Devices.emplace_back(Device);
		}

		std::sort(m_Devices.begin(), m_Devices.end());
	}
}

Tracy::VulkanInitializer::~VulkanInitializer()
{
	if (m_Instance)
	{
		m_Instance.destroy();
	}
}