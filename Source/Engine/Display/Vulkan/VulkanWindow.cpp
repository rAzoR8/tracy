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

	if (LogVKErrorFailed(_Instance.createWin32SurfaceKHR(&SurfaceDesc, nullptr, &m_Surface)))
	{
		HFATALD("Failed to create Win32 Surface");	
	}
}
#endif

//---------------------------------------------------------------------------------------------------
VulkanWindow::VulkanWindow(VulkanWindow&& _Other) :
	m_Surface(std::move(_Other.m_Surface)),
	m_Swapchain(std::move(_Other.m_Swapchain)),
	m_uWidth(_Other.m_uWidth),
	m_uHeight(_Other.m_uHeight),
	m_hThis(_Other.m_hThis),
	m_hPresentDevice(_Other.m_hPresentDevice),
	m_Backbuffer(std::move(_Other.m_Backbuffer)),
	m_Capabilities(std::move(_Other.m_Capabilities)),
	m_Formats(std::move(_Other.m_Formats)),
	m_PresentModes(std::move(_Other.m_PresentModes)),
	m_Description(std::move(_Other.m_Description))
{
	_Other.m_hThis = kUndefinedSizeT;
	_Other.m_hPresentDevice = kUndefinedSizeT;

	_Other.m_Surface = nullptr;
	_Other.m_Swapchain = nullptr;
}

//---------------------------------------------------------------------------------------------------
VulkanWindow& VulkanWindow::operator=(VulkanWindow&& _Other)
{
	if (this != &_Other)
	{
		// Cleanup old-data
		GetDevice(m_hPresentDevice).GetDevice().destroySwapchainKHR(m_Swapchain);
		VulkanInstance::GetInstance().Destroy(m_Surface);

		// move
		m_Surface = std::move(_Other.m_Surface);
		m_Swapchain = std::move(_Other.m_Swapchain);
		m_Capabilities = std::move(_Other.m_Capabilities);
		m_Formats = std::move(_Other.m_Formats);
		m_PresentModes = std::move(_Other.m_PresentModes);
		m_Backbuffer = std::move(_Other.m_Backbuffer);
		m_uWidth = _Other.m_uWidth;
		m_uHeight = _Other.m_uHeight;
		m_hThis = _Other.m_hThis;
		m_hPresentDevice = _Other.m_hPresentDevice;

		// cleanup _Other
		_Other.m_Surface = nullptr;
		_Other.m_Swapchain = nullptr;

		_Other.m_hThis = kUndefinedSizeT;
		_Other.m_hPresentDevice = kUndefinedSizeT;
	}

	return *this;
}

//---------------------------------------------------------------------------------------------------
VulkanWindow::~VulkanWindow()
{
	for (VulkanTexture& Tex : m_Backbuffer)
	{
		for (const vk::ImageView& view : VKTexture(Tex).Views)
		{
			if (view)
				GetDevice(m_hPresentDevice).GetDevice().destroyImageView(view);
		}
	}

	if (m_Swapchain) 
	{
		GetDevice(m_hPresentDevice).GetDevice().destroySwapchainKHR(m_Swapchain);
	}

	if (m_Surface) 
	{
		VulkanInstance::GetInstance().Destroy(m_Surface);
	}
}

//---------------------------------------------------------------------------------------------------
const bool VulkanWindow::Init(const VulkanDevice& _Device, const uint32_t _uWidth, const uint32_t _uHeight)
{
	if (!m_Surface)
		return false;

	// Check if the device can present to surface
	if (_Device.PresentSupport(m_Surface) == false)
	{
		return false;
	}

	// Get Physical device and store the handle of the device
	m_hPresentDevice = _Device.GetHandle();
	HASSERT(m_hPresentDevice != kUndefinedSizeT, "Invalid present device handle");

	m_uWidth = _uWidth;
	m_uHeight = _uHeight;

	// Resize the backbuffer (release and create swapchain)
	return OnResize(m_uWidth, m_uHeight);
}

//---------------------------------------------------------------------------------------------------
const bool VulkanWindow::OnResize(const uint32_t _uWidth, const uint32_t _uHeight)
{
	return CreateSwapchain(_uWidth, _uHeight);
}

//---------------------------------------------------------------------------------------------------
bool VulkanWindow::ReloadSurfaceInfo()
{
	const vk::PhysicalDevice& Device = GetDevice(m_hPresentDevice).GetAdapter();

	// Fetch all useful data
	if(LogVKErrorFailed(Device.getSurfaceCapabilitiesKHR(m_Surface, &m_Capabilities)))
		return false;

	m_Formats = Device.getSurfaceFormatsKHR(m_Surface);
	if (m_Formats.empty())
	{
		HERROR("Failed to retrieve supported surface formats.");
		return false;
	}

	m_PresentModes = Device.getSurfacePresentModesKHR(m_Surface);
	if (m_PresentModes.empty())
	{
		HERROR("Failed to retrieve supported surface present modes.");
		return false;
	}

	return true;
}

//---------------------------------------------------------------------------------------------------
bool VulkanWindow::CreateSwapchain(const uint32_t _uWidth, const uint32_t _uHeight)
{
	if (m_Swapchain && m_uWidth == _uWidth && m_uHeight == _uHeight)
		return true;

	if (_uWidth == 0u || _uHeight == 0u)
		return false;

	// Retrieve updated info from os layer
	if (ReloadSurfaceInfo() == false)
		return false;

	// Cache old swapchain for release
	vk::SwapchainKHR OldSwapchain = m_Swapchain;

	m_Description = {};
	m_Description.pNext = nullptr;
	m_Description.surface = m_Surface;
	m_Description.imageArrayLayers = 1u; // is the number of views in a multiview/stereo surface. For non-stereoscopic-3D applications, this value is 1.
	m_Description.clipped = VK_TRUE;
	m_Description.imageSharingMode = vk::SharingMode::eExclusive;
	m_Description.queueFamilyIndexCount = 0u;
	m_Description.pQueueFamilyIndices = nullptr;
	m_Description.oldSwapchain = OldSwapchain;

	//
	// Select Color Space and Format
	//
	// If the surface format list only includes one entry with VK_FORMAT_UNDEFINED,
	// there is no preferered format, so we assume LDR_RENDER_FORMAT
	if ((m_Formats.size() > 0u) && (m_Formats[0u].format == vk::Format::eUndefined))
	{
		m_Description.imageFormat = vk::Format::eB8G8R8A8Srgb;
		m_Description.imageColorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;
	}
	else
	{
		// If we need a specific format (e.g. SRGB) we'd need to
		// iterate over the list of available surface format and
		// check for its presence
		m_Description.imageFormat = m_Formats[0u].format;
		m_Description.imageColorSpace = m_Formats[0u].colorSpace;
	}

	//
	// Set Backbuffer Size
	//
	// Width and height are either both 0xFFFFFFFF or both not 0xFFFFFFFF
	if (m_Capabilities.currentExtent.width == 0xFFFFFFFF)
	{
		// If the surface size is undefined, the size is set to
		// the size of the image requested
		m_Description.imageExtent.width = _uWidth;
		m_Description.imageExtent.height = _uHeight;
	}
	else
	{
		// If the surface is defined, the swapchain size must match
		m_Description.imageExtent.width = m_Capabilities.currentExtent.width;
		m_Description.imageExtent.height = m_Capabilities.currentExtent.height;
	}
	m_uWidth = m_Description.imageExtent.width;
	m_uHeight = m_Description.imageExtent.height;

	//
	// Setup V-Sync / Present Mode
	// https://www.khronos.org/registry/vulkan/specs/1.0-extensions/html/vkspec.html#VkPresentModeKHR
	//
	// FIFO indicates that the presentation engine waits for the next vertical blanking period to update 
	// the current image. Tearing cannot be observed. An internal queue is used to hold pending presentation requests. 
	// New requests are appended to the end of the queue, and one request is removed from the beginning of the queue and 
	// processed during each vertical blanking period in which the queue is non-empty. 
	// This is the only value of presentMode that is REQUIRED to be supported.
	m_Description.presentMode = vk::PresentModeKHR::eFifo;

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
				m_Description.presentMode = PresentMode;
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
				m_Description.presentMode = PresentMode;
				break;
			}
		}
	}

	//
	// Number of backbuffer images
	//
	// Default is 1 image more than the minimum supported
	// TODO : might want to use config to set double or triple buffering
	m_Description.minImageCount = m_Capabilities.minImageCount + 1u;
	// Ensure that we can allow this many images
	if (m_Capabilities.maxImageCount > 0u)
	{
		m_Description.minImageCount = std::max(m_Description.minImageCount, m_Capabilities.maxImageCount);
	}

	//
	// Set Surface Transform
	//
	if (m_Capabilities.supportedTransforms & vk::SurfaceTransformFlagBitsKHR::eIdentity)
	{
		m_Description.preTransform = vk::SurfaceTransformFlagBitsKHR::eIdentity;
	}
	else
	{
		m_Description.preTransform = m_Capabilities.currentTransform;
	}

	//
	// Supported Alpha Format
	// https://www.khronos.org/registry/vulkan/specs/1.0-extensions/html/vkspec.html#VkCompositeAlphaFlagBitsKHR
	//
	// We would like to ignore alpha blending of the os windowing system, unfortunately support is not granted.
	m_Description.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
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
			m_Description.compositeAlpha = AlphaMode;
			break;
		}
	}

	//
	// Image Usage
	//
	m_Description.imageUsage = vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eStorage | vk::ImageUsageFlagBits::eSampled;
	// Enable blit to backbuffer if supported, can be nice for postfx
	const vk::FormatProperties& FormatProps = GetDevice(m_hPresentDevice).GetAdapter().getFormatProperties(m_Description.imageFormat);
	if (FormatProps.optimalTilingFeatures & vk::FormatFeatureFlagBits::eBlitDst)
	{
		m_Description.imageUsage |= vk::ImageUsageFlagBits::eTransferSrc;
	}

	//
	// Create Swapchain
	//
	const vk::Device& Device = GetDevice(m_hPresentDevice).GetDevice();
	if (LogVKErrorFailed(Device.createSwapchainKHR(&m_Description, nullptr, &m_Swapchain)))
		return false;

	//
	// Clean-up old Swapchain if present
	//
	if (OldSwapchain)
	{
		for (VulkanTexture& Tex : m_Backbuffer)
		{
			for (const vk::ImageView& view : VKTexture(Tex).Views)
			{
				if (view)
					Device.destroyImageView(view);
			} 
		}

		m_Backbuffer.resize(0);
		Device.destroySwapchainKHR(OldSwapchain);
	}

	//
	// Get Swapchain images
	//
	std::vector<vk::Image>&& SwapchainImages = Device.getSwapchainImagesKHR(m_Swapchain);

	uint32_t uBaseMipLevel = 0u;
	uint32_t uMipLevelCount = 1u;
	uint32_t uBaseArrayLayer = 0u;
	uint32_t uArrayLayerCount = 1u;
	
	vk::ImageViewCreateInfo ColorView{};
	ColorView.pNext = nullptr;
	ColorView.format = m_Description.imageFormat;
	ColorView.components = vk::ComponentMapping();	// Set identity for all channels
	ColorView.subresourceRange = vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, uBaseMipLevel, uMipLevelCount, uBaseArrayLayer, uArrayLayerCount);
	ColorView.viewType = vk::ImageViewType::e2D;

	TImageViews Views;
	for (const vk::Image& Image : SwapchainImages)
	{		
		ColorView.image = Image;
		Views[kViewType_RenderTarget] = Device.createImageView(ColorView);
		m_Backbuffer.emplace_back(m_hPresentDevice, Image, vk::ImageLayout::eUndefined, Views);
	}

	return true;
}
//---------------------------------------------------------------------------------------------------
