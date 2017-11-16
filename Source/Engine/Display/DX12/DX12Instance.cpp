#include "DX12Instance.h"

#include "Logger.h"

using namespace Tracy;

DX12Instance::DX12Instance()
{
}

DX12Instance::~DX12Instance()
{
}

const std::vector<DeviceInfo> DX12Instance::Init()
{
	HRESULT uResult;
	uint32_t uFactoryCreateFlags = 0;

	// Activate Debug Layer
#if defined(DEBUG) || defined(_DEBUG)
	{
		// Debug: https://msdn.microsoft.com/en-us/library/windows/desktop/dn950153(v=vs.85).aspx
		ID3D12Debug1* debugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();

			uFactoryCreateFlags |= DXGI_CREATE_FACTORY_DEBUG;
		}
	}
#endif

	// Create DXGIFactory
	uResult = CreateDXGIFactory2(uFactoryCreateFlags, IID_PPV_ARGS(&m_pFactory));
	HASSERT(uResult == S_OK, "Failed to create DXGIFactory.");

	std::vector<DeviceInfo> DeviceInfos;
	IDXGIAdapter1* pAdapter;
	for (uint32_t uAdapterIndex = 0u; m_pFactory->EnumAdapters1(uAdapterIndex, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++uAdapterIndex)
	{
		DXGI_ADAPTER_DESC1 Desc;
		pAdapter->GetDesc1(&Desc);

		// Filter out software adapters
		if (Desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;

		const auto ResultIt = m_Devices.insert({ m_LastDeviceHandle, DX12Device(pAdapter, m_LastDeviceHandle) });
		HASSERT(ResultIt.second == true, "Failed to store DX12Device.");
		DeviceInfos.push_back(ResultIt.first->second.GetInfo());
		m_LastDeviceHandle++;
	}

	return DeviceInfos;
}

const THandle DX12Instance::MakeWindow(const THandle _hPresentDeviceHandle, const uint32_t _uWidth, const uint32_t _uHeight, HWND _hWnd, HINSTANCE _hInstance)
{
	return kUndefinedSizeT;
}

void DX12Instance::OnChangeDisplaySettings(const uint32_t _uWidth, const uint32_t _uHeight)
{
}
