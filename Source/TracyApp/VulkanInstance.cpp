#include "VulkanInstance.h"

#include "Logger.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

VulkanInstance::VulkanInstance()
{
	m_Windows.clear();

	m_Devices.clear();
}
//---------------------------------------------------------------------------------------------------

VulkanInstance::~VulkanInstance()
{
}
//---------------------------------------------------------------------------------------------------

void VulkanInstance::Init(const uint32_t _uWidth, const uint32_t _uHeight, HWND _hWnd, HINSTANCE _hInstance)
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
		for (const vk::PhysicalDevice& Device : m_Instance.enumeratePhysicalDevices())
		{
			const auto Res = m_Devices.try_emplace(m_LastDeviceHandle, Device, m_LastDeviceHandle);
			HASSERT(Res.second == true, "Failed to add device");
			m_LastDeviceHandle++;
		}
		HASSERT(m_Devices.size() > 0u, "Failed to create logical devices");

		// create default window.
		// TODO : It should come from a config file
		// first device should be dedicated one after init
		// could also be called from the application, maaybe makes more sense
		THandle BaseWindowHandle = MakeWindow(m_Devices.begin()->first, _uWidth, _uHeight, _hWnd, _hInstance);
		HASSERT(BaseWindowHandle != kUndefinedSizeT, "Failed to create default window.");
	}
}
//---------------------------------------------------------------------------------------------------

void VulkanInstance::OnChangeDisplaySettings(const uint32_t _uWidth, const uint32_t _uHeight)
{
	for (auto& Window : m_Windows)
	{
		Window.second.OnResize(_uWidth, _uHeight);
	}
}

//---------------------------------------------------------------------------------------------------
const VulkanDevice& VulkanInstance::GetDevice(const THandle _hDevice) const
{
	const auto& DeviceIt = m_Devices.find(_hDevice);
	HASSERT(DeviceIt != m_Devices.end(), "Invalid device handle: %d", _hDevice);

	return DeviceIt->second;
}

//---------------------------------------------------------------------------------------------------
const VulkanWindow& Tracy::VulkanInstance::GetWindow(const THandle _hWindow) const
{
	const auto& WindowIt = m_Windows.find(_hWindow);
	HASSERT(WindowIt != m_Windows.end(), "Invalid window handle: %d", _hWindow);

	return WindowIt->second;
}

//---------------------------------------------------------------------------------------------------
#if defined(_WIN32) || defined(WIN32)
const THandle Tracy::VulkanInstance::MakeWindow(const THandle _hPresentDeviceHandle, const uint32_t _uWidth, const uint32_t _uHeight, HWND _hWnd, HINSTANCE _hInstance)
{
	THandle ResultHandle = kUndefinedSizeT;

	const auto& DeviceIt = m_Devices.find(_hPresentDeviceHandle);
	if (DeviceIt != m_Devices.end())
	{
		VulkanWindow Window(m_Instance, m_LastWindowHandle, _hWnd, _hInstance);
		if (Window.Init(DeviceIt->second, _uWidth, _uHeight))
		{
			const auto Res = m_Windows.try_emplace(m_LastWindowHandle, std::move(Window));
			HASSERT(Res.second == true, "Failed to add presentable window");
			ResultHandle = m_LastWindowHandle++;
		}
	}

	return ResultHandle;
}

//---------------------------------------------------------------------------------------------------
void Tracy::VulkanInstance::Destroy(vk::SurfaceKHR& _Surface) const
{
	if (_Surface)
	{
		m_Instance.destroySurfaceKHR(_Surface);
		_Surface = nullptr;
	}
}

//---------------------------------------------------------------------------------------------------
void Tracy::VulkanInstance::Destroy(vk::SwapchainKHR& _Swapchain, const THandle _hDevice) const
{
	if (_Swapchain)
	{
		const VulkanDevice& Device = GetDevice(_hDevice);
		
		Device.m_Device.destroySwapchainKHR(_Swapchain);
		_Swapchain = nullptr;
	}
}

void Tracy::VulkanInstance::Destroy(vk::ImageView& _View, const THandle _hDevice) const
{
	if (_View)
	{
		const VulkanDevice& Device = GetDevice(_hDevice);
		
		Device.m_Device.destroyImageView(_View);
		_View = nullptr;
	}

}
#endif
