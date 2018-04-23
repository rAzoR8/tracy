#include "IApplication.h"
#include "Display/Vulkan/VulkanInstance.h"
#include "Display/Vulkan/VulkanRenderer.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

bool IApplication::InitAPI(const uint32_t _uWidth, const uint32_t _uHeight, std::vector<DeviceInfo>& _OutDevices)
{
	if (OnInitAPI(_uWidth, _uHeight))
	{
		_OutDevices = VulkanInstance::GetInstance().Init();
	}

	return _OutDevices.empty() == false;
}
//---------------------------------------------------------------------------------------------------

bool IApplication::InitWindowAndRenderer(const RenderGraphDesc& _Desc, const THandle _hDevice)
{
	THandle hWnd = kUndefinedSizeT;

	if (OnInitWindow(_hDevice, hWnd))
	{
		m_pRenderer = std::make_unique<VulkanRenderer>(_Desc, hWnd);
	}

	return m_pRenderer != nullptr ? m_pRenderer->Init() : false;
}
//---------------------------------------------------------------------------------------------------
