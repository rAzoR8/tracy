#include "VulkanInitializer.h"

#include "Logger.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

VulkanInitializer::VulkanInitializer()
{
}
//---------------------------------------------------------------------------------------------------

VulkanInitializer::~VulkanInitializer()
{
	m_Devices.clear();

	if (m_Instance)
	{
		m_Instance.destroySurfaceKHR(m_Surface);

		m_Instance.destroy();
	}
}
//---------------------------------------------------------------------------------------------------

void Tracy::VulkanInitializer::Init(HWND _hWnd, HINSTANCE _hInstance, const uint32_t _uClientWidth, const uint32_t _uClientHeight)
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

		for (const auto& Device : m_Instance.enumeratePhysicalDevices())
		{
			m_Devices.emplace_back(Device);
		}

		std::sort(m_Devices.begin(), m_Devices.end());

		// Create Surface, could be put in a window wrapper and will be substituted by Qt
#if defined(WIN32) || defined(_WIN32)
		vk::Win32SurfaceCreateInfoKHR SurfaceDesc{};
		SurfaceDesc.pNext = nullptr;
		SurfaceDesc.hwnd = m_hWnd;
		SurfaceDesc.hinstance = m_hInstance;

		m_Surface = m_Instance.createWin32SurfaceKHR(SurfaceDesc);
#endif // defined(WIN32) || defined(_WIN32)

		// Select a logical device that support presenting to the swapchain for now
		// Can implement a better logic later when actually needed!
		// Checking for support is important, vulkan layer will fail validation of swapchain 
		// if queue index was not tested against presenting!
		for (size_t uDeviceIndex = 0, end = m_Devices.size(); uDeviceIndex < end; ++uDeviceIndex)
		{	
			if (m_Devices[uDeviceIndex].PresentSupport(m_Surface))
			{
				m_uPresentDeviceIndex = uDeviceIndex;
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------------------------------

void Tracy::VulkanInitializer::OnChangeDisplaySettings(const uint32_t _uClientWidth, const uint32_t _uClientHeight)
{
	vk::SwapchainCreateInfoKHR SwapchainDesc{};
	SwapchainDesc.pNext = nullptr;

	// Query surface formats, this could be at Init time but it might be useful later
	// to support HDR display outputs
	std::vector<vk::SurfaceFormatKHR> SurfaceFormats = m_Devices[m_uPresentDeviceIndex].GetSurfaceFormats(m_Surface);
	HASSERTD(SurfaceFormats.size() > 0u, "Failed to retrieve supported swapchain formats.");

	// TODO : add HDR render target format and color space selection
	// We would have to look for Outputs and do some accurate work to make it pretty.
	// If the surface format list only includes one entry with VK_FORMAT_UNDEFINED,
	// there is no preferered format, so we assume LDR_RENDER_FORMAT
	if (SurfaceFormats[0].format == vk::Format::eUndefined)
	{
		SwapchainDesc.imageFormat = vk::Format::eR8G8B8A8Unorm;
	}
	else
	{
		// Always select the first available color format
		// If you need a specific format (e.g. SRGB),
		// iterate over the list of available surface format and
		// check for its presence
		SwapchainDesc.imageFormat = SurfaceFormats[0].format;
	}
	SwapchainDesc.imageColorSpace = SurfaceFormats[0].colorSpace;

	// Store a pointer to the old swapchain for cleanup
	vk::SwapchainKHR OldSwapchain = m_Swapchain;

	// Retrieve Surface capabilities
	vk::SurfaceCapabilitiesKHR SurfaceCapabilities = m_Devices[m_uPresentDeviceIndex].GetSurfaceCapabilities(m_Surface);

	// Retrieve Present modes
}
//---------------------------------------------------------------------------------------------------

void VulkanInitializer::CreateSwapchain(const uint32_t _uClientWidth, const uint32_t _uClientHeight)
{
	vk::SwapchainKHR OldSwapchain = m_Swapchain;

	vk::SwapchainCreateInfoKHR desc{};
	desc.pNext = nullptr;
	desc.imageFormat = vk::Format::eB8G8R8A8Unorm;
	desc.oldSwapchain = OldSwapchain;
	desc.surface = m_Surface;
	desc.imageExtent = vk::Extent2D(_uClientWidth, _uClientHeight);
	desc.clipped = true;
	desc.imageSharingMode = vk::SharingMode::eExclusive;
	desc.queueFamilyIndexCount = 0u;
	desc.pQueueFamilyIndices = nullptr;
}
//---------------------------------------------------------------------------------------------------