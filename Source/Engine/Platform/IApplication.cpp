#include "IApplication.h"
#include "Display/Vulkan/VulkanInstance.h"
#include "Display/DX12/DX12Instance.h"
#include "Display/Vulkan/VulkanRenderer.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

bool IApplication::InitAPI(const uint32_t _uWidth, const uint32_t _uHeight, const EGraphicsAPI _kAPI, std::vector<DeviceInfo>& _OutDevices)
{
	ApplicationInfo::Instance().SetGfxAPI(_kAPI);

	if (OnInitAPI(_uWidth, _uHeight))
	{
		switch (_kAPI)
		{
		case kGraphicsAPI_Vulkan:
			_OutDevices = VulkanInstance::GetInstance().Init();
			break;
		default:
			break;
		}
	}

	return _OutDevices.empty() == false;
}
//---------------------------------------------------------------------------------------------------

bool IApplication::InitWindowAndRenderer(const RenderGraphDesc& _Desc, const THandle _hDevice)
{
	THandle hWnd = kUndefinedSizeT;

	if (OnInitWindow(_hDevice, hWnd))
	{
		switch (ApplicationInfo::Instance().GetGfxAPI())
		{
		case kGraphicsAPI_Vulkan:
			m_pRenderer = std::make_unique<VulkanRenderer>(_Desc, hWnd);
			break;
		default:
			break;
		}
	}

	return m_pRenderer != nullptr ? m_pRenderer->Init() : false;
}
//---------------------------------------------------------------------------------------------------
