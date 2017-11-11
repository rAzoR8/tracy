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
	for (auto& BufferView : m_Backbuffer)
	{
		VulkanInstance::GetInstance().Destroy(BufferView, m_hPresentDevice);
	}

	VulkanInstance::GetInstance().Destroy(m_Swapchain, m_hPresentDevice);

	VulkanInstance::GetInstance().Destroy(m_Surface);
}

//---------------------------------------------------------------------------------------------------
const bool Tracy::VulkanWindow::Init(const VulkanDevice& _Device, const uint32_t _uWidth, const uint32_t _uHeight)
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

	m_uWidth = _uWidth;
	m_uHeight = _uHeight;

	// Resize the backbuffer (release and create swapchain)
	return OnResize(m_uWidth, m_uHeight);
}

//---------------------------------------------------------------------------------------------------
const bool Tracy::VulkanWindow::OnResize(const uint32_t _uWidth, const uint32_t _uHeight)
{
	CreateSwapchain(_uWidth, _uHeight);

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
void VulkanWindow::CreateSwapchain(const uint32_t _uWidth, const uint32_t _uHeight)
{
	// Retrieve updated info from os layer
	ReloadSurfaceInfo();

	// Cache old swapchain for release
	vk::SwapchainKHR OldSwapchain = m_Swapchain;

	vk::SwapchainCreateInfoKHR SwapchainDesc{};
	SwapchainDesc.pNext = nullptr;
	SwapchainDesc.surface = m_Surface;
	SwapchainDesc.imageArrayLayers = 1u; // is the number of views in a multiview/stereo surface. For non-stereoscopic-3D applications, this value is 1.
	SwapchainDesc.clipped = VK_TRUE;
	SwapchainDesc.imageSharingMode = vk::SharingMode::eExclusive;
	SwapchainDesc.queueFamilyIndexCount = 0u;
	SwapchainDesc.pQueueFamilyIndices = nullptr;
	SwapchainDesc.oldSwapchain = OldSwapchain;

	//
	// Select Color Space and Format
	//
	// If the surface format list only includes one entry with VK_FORMAT_UNDEFINED,
	// there is no preferered format, so we assume LDR_RENDER_FORMAT
	if ((m_Formats.size() > 0u) && (m_Formats[0u].format == vk::Format::eUndefined))
	{
		SwapchainDesc.imageFormat = vk::Format::eB8G8R8A8Srgb;
		SwapchainDesc.imageColorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;
	}
	else
	{
		// If we need a specific format (e.g. SRGB) we'd need to
		// iterate over the list of available surface format and
		// check for its presence
		SwapchainDesc.imageFormat = m_Formats[0u].format;
		SwapchainDesc.imageColorSpace = m_Formats[0u].colorSpace;
	}

	//
	// Set Backbuffer Size
	//
	// Width and height are either both 0xFFFFFFFF or both not 0xFFFFFFFF
	if (m_Capabilities.currentExtent.width == 0xFFFFFFFF)
	{
		// If the surface size is undefined, the size is set to
		// the size of the image requested
		SwapchainDesc.imageExtent.width = _uWidth;
		SwapchainDesc.imageExtent.height = _uHeight;
	}
	else
	{
		// If the surface is defined, the swapchain size must match
		SwapchainDesc.imageExtent.width = m_Capabilities.currentExtent.width;
		SwapchainDesc.imageExtent.height = m_Capabilities.currentExtent.height;
	}
	m_uWidth = SwapchainDesc.imageExtent.width;
	m_uHeight = SwapchainDesc.imageExtent.height;

	//
	// Setup V-Sync / Present Mode
	// https://www.khronos.org/registry/vulkan/specs/1.0-extensions/html/vkspec.html#VkPresentModeKHR
	//
	// FIFO indicates that the presentation engine waits for the next vertical blanking period to update 
	// the current image. Tearing cannot be observed. An internal queue is used to hold pending presentation requests. 
	// New requests are appended to the end of the queue, and one request is removed from the beginning of the queue and 
	// processed during each vertical blanking period in which the queue is non-empty. 
	// This is the only value of presentMode that is REQUIRED to be supported.
	SwapchainDesc.presentMode = vk::PresentModeKHR::eFifo;

	bool bEnableVSync = false;	// TODO : should come from config
	if (bEnableVSync)
	{
		for (const vk::PresentModeKHR& PresentMode : m_PresentModes)
		{
			// MAILBOX indicates that the presentation engine waits for the next vertical blanking period to 
			// update the current image. Tearing cannot be observed. An internal single-entry queue is used to 
			// hold pending presentation requests. If the queue is full when a new presentation request is received, 
			// the new request replaces the existing entry, and any images associated with the prior entry become 
			// available for re-use by the application. One request is removed from the queue and processed during 
			// each vertical blanking period in which the queue is non-empty.
			if (PresentMode == vk::PresentModeKHR::eMailbox)
			{
				SwapchainDesc.presentMode = PresentMode;
				break;
			}
		}
	}
	else
	{
		for (const vk::PresentModeKHR& PresentMode : m_PresentModes)
		{
			// IMMEDIATE indicates that the presentation engine does not wait for a vertical blanking period
			// to update the current image, meaning this mode may result in visible tearing.
			// No internal queuing of presentation requests is needed, as the requests are applied immediately.
			if (PresentMode == vk::PresentModeKHR::eImmediate)
			{
				SwapchainDesc.presentMode = PresentMode;
				break;
			}
		}
	}

	//
	// Number of backbuffer images
	//
	// Default is 1 image more than the minimum supported
	// TODO : might want to use config to set double or triple buffering
	SwapchainDesc.minImageCount = m_Capabilities.minImageCount + 1u;
	// Ensure that we can allow this many images
	SwapchainDesc.minImageCount = std::min(SwapchainDesc.minImageCount, m_Capabilities.maxImageCount);

	//
	// Set Surface Transform
	//
	if (m_Capabilities.supportedTransforms & vk::SurfaceTransformFlagBitsKHR::eIdentity)
	{
		SwapchainDesc.preTransform = vk::SurfaceTransformFlagBitsKHR::eIdentity;
	}
	else
	{
		SwapchainDesc.preTransform = m_Capabilities.currentTransform;
	}

	//
	// Supported Alpha Format
	// https://www.khronos.org/registry/vulkan/specs/1.0-extensions/html/vkspec.html#VkCompositeAlphaFlagBitsKHR
	//
	// We would like to ignore alpha blending of the os windowing system, unfortunately support is not granted.
	SwapchainDesc.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
	std::vector<vk::CompositeAlphaFlagBitsKHR> CompositeAlphaFlags =
	{
		vk::CompositeAlphaFlagBitsKHR::eOpaque,
		vk::CompositeAlphaFlagBitsKHR::eInherit,
		vk::CompositeAlphaFlagBitsKHR::ePreMultiplied,
		vk::CompositeAlphaFlagBitsKHR::ePostMultiplied
	};
	// Search the first available
	for (const auto& AlphaMode : CompositeAlphaFlags)
	{
		if (AlphaMode & m_Capabilities.supportedCompositeAlpha)
		{
			SwapchainDesc.compositeAlpha = AlphaMode;
			break;
		}
	}

	//
	// Image Usage
	//
	SwapchainDesc.imageUsage = vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eStorage;
	// Enable blit to backbuffer if supported, can be nice for postfx
	const vk::FormatProperties& FormatProps = VulkanInstance::GetInstance().GetDevice(m_hPresentDevice).GetPhysicalHandle().getFormatProperties(SwapchainDesc.imageFormat);
	if (FormatProps.optimalTilingFeatures & vk::FormatFeatureFlagBits::eBlitDst)
	{
		SwapchainDesc.imageUsage |= vk::ImageUsageFlagBits::eTransferSrc;
	}

	//
	// Create Swapchain
	//
	const vk::Device& Device = VulkanInstance::GetInstance().GetDevice(m_hPresentDevice).GetLogicalHandle();
	vk::Result Res = Device.createSwapchainKHR(&SwapchainDesc, nullptr, &m_Swapchain);
	HASSERT(Res == vk::Result::eSuccess, "Failed to create swapchain");

	//
	// Clean-up old Swapchain if present
	//
	if (OldSwapchain)
	{
		for (auto& BufferView : m_Backbuffer)
		{
			VulkanInstance::GetInstance().Destroy(BufferView, m_hPresentDevice);
		}
		Device.destroySwapchainKHR(OldSwapchain);
	}

	//
	// Get Swapchain images
	//
	std::vector<vk::Image>&& SwapchainImages = Device.getSwapchainImagesKHR(m_Swapchain);
	m_Backbuffer.reserve(SwapchainImages.size());

	uint32_t uBaseMipLevel = 0u;
	uint32_t uMipLevelCount = 1u;
	uint32_t uBaseArrayLayer = 0u;
	uint32_t uArrayLayerCount = 1u;
	
	vk::ImageViewCreateInfo ColorView{};
	ColorView.pNext = nullptr;
	ColorView.format = SwapchainDesc.imageFormat;
	ColorView.components = vk::ComponentMapping();	// Set identity for all channels
	ColorView.subresourceRange = vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, uBaseMipLevel, uMipLevelCount, uBaseArrayLayer, uArrayLayerCount);
	ColorView.viewType = vk::ImageViewType::e2D;

	for (const vk::Image& Image : SwapchainImages)
	{
		ColorView.image = Image;

		m_Backbuffer.push_back(Device.createImageView(ColorView));
	}
}
