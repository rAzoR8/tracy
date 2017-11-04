#include "VulkanWindow.h"

#include "VulkanInstance.h"
#include "Logger.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------
#if defined(WIN32) || defined(_WIN32)
VulkanWindow::VulkanWindow(const vk::Instance& _Instance, const THandle _uHandle, const HWND _hWnd, const HINSTANCE _hInstance) :
	m_hThis(_uHandle)
{
	vk::Win32SurfaceCreateInfoKHR SurfaceDesc{};
	SurfaceDesc.pNext = nullptr;
	SurfaceDesc.hwnd = _hWnd;
	SurfaceDesc.hinstance = _hInstance;

	HASSERT(_Instance.createWin32SurfaceKHR(&SurfaceDesc, nullptr, &m_Surface) == vk::Result::eSuccess, "Failed to create Win32 Surface");
}
#endif

//---------------------------------------------------------------------------------------------------
Tracy::VulkanWindow::VulkanWindow(VulkanWindow&& _Other) :
	m_Surface(nullptr),
	m_Swapchain(nullptr),
	m_uWidth(0u),
	m_uHeight(0u),
	m_hThis(kUndefinedSizeT),
	m_hPresentDevice(kUndefinedSizeT)
{
	m_Surface = std::move(_Other.m_Surface);
	m_Swapchain = std::move(_Other.m_Swapchain);
	m_Capabilities = std::move(_Other.m_Capabilities);
	m_Formats = std::move(_Other.m_Formats);
	m_PresentModes = std::move(_Other.m_PresentModes);
	m_uWidth = _Other.m_uWidth;
	m_uHeight = _Other.m_uHeight;
	m_hThis = _Other.m_hThis;
	m_hPresentDevice = _Other.m_hPresentDevice;

	_Other.m_Surface = nullptr;
	_Other.m_Swapchain = nullptr;
}

//---------------------------------------------------------------------------------------------------
VulkanWindow& Tracy::VulkanWindow::operator=(VulkanWindow&& _Other)
{
	if (this != &_Other)
	{
		// Cleanup old-data
		VulkanInstance::GetInstance().Destroy(m_Swapchain, m_hPresentDevice);
		VulkanInstance::GetInstance().Destroy(m_Surface);

		// move
		m_Surface = std::move(_Other.m_Surface);
		m_Swapchain = std::move(_Other.m_Swapchain);
		m_Capabilities = std::move(_Other.m_Capabilities);
		m_Formats = std::move(_Other.m_Formats);
		m_PresentModes = std::move(_Other.m_PresentModes);
		m_uWidth = _Other.m_uWidth;
		m_uHeight = _Other.m_uHeight;
		m_hThis = _Other.m_hThis;
		m_hPresentDevice = _Other.m_hPresentDevice;

		// cleanup _Other
		_Other.m_Surface = nullptr;
		_Other.m_Swapchain = nullptr;
	}

	return *this;
}

//---------------------------------------------------------------------------------------------------
Tracy::VulkanWindow::~VulkanWindow()
{
	VulkanInstance::GetInstance().Destroy(m_Swapchain, m_hPresentDevice);

	VulkanInstance::GetInstance().Destroy(m_Surface);
}

//---------------------------------------------------------------------------------------------------
const bool Tracy::VulkanWindow::Init(const VulkanDevice& _Device)
{
	// Check if the device can present to surface
	if (_Device.PresentSupport(m_Surface) == false)
	{
		return false;
	}

	// Get Physical device and store the handle of the device
	const vk::PhysicalDevice& DeviceHandle = _Device.GetPhysicalHandle();
	m_hPresentDevice = _Device.GetHandle();
	HASSERT(m_hPresentDevice != kUndefinedSizeT, "Invalid present device handle");

	// Query the surface to retrieve system support info
	ReloadSurfaceInfo();

	// Resize the backbuffer (release and create swapchain)
	return OnResize(m_Capabilities.currentExtent.width, m_Capabilities.currentExtent.height);
}

//---------------------------------------------------------------------------------------------------
const bool Tracy::VulkanWindow::OnResize(const uint32_t _uClientWidth, const uint32_t _uClientHeight)
{
	m_uWidth = _uClientWidth;
	m_uHeight = _uClientHeight;

	//CreateSwapchain();

	return true;
}

//---------------------------------------------------------------------------------------------------
void Tracy::VulkanWindow::ReloadSurfaceInfo()
{
	const vk::PhysicalDevice& DeviceHandle = VulkanInstance::GetInstance().GetDevice(m_hPresentDevice).GetPhysicalHandle();

	// Fetch all useful data
	vk::Result res = DeviceHandle.getSurfaceCapabilitiesKHR(m_Surface, &m_Capabilities);
	HASSERT(res == vk::Result::eSuccess, "Failed to retrieve surface capabilities.");

	m_Formats = DeviceHandle.getSurfaceFormatsKHR(m_Surface);
	HASSERT(m_Formats.size() > 0u, "Failed to retrieve supported surface formats.");

	m_PresentModes = DeviceHandle.getSurfacePresentModesKHR(m_Surface);
	HASSERT(m_PresentModes.size() > 0u, "Failed to retrieve supported surface present modes.");
}

//---------------------------------------------------------------------------------------------------
void VulkanWindow::CreateSwapchain()
{
	vk::SwapchainKHR OldSwapchain = m_Swapchain;

	vk::SwapchainCreateInfoKHR desc{};
	desc.pNext = nullptr;
	desc.imageFormat = vk::Format::eB8G8R8A8Unorm;
	desc.oldSwapchain = OldSwapchain;
	desc.surface = m_Surface;
	desc.imageExtent = vk::Extent2D(m_uWidth, m_uHeight);
	desc.clipped = true;
	desc.imageSharingMode = vk::SharingMode::eExclusive;
	desc.queueFamilyIndexCount = 0u;
	desc.pQueueFamilyIndices = nullptr;
}
