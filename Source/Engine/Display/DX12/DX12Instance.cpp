#include "DX12Instance.h"

using namespace Tracy;

DX12Instance::DX12Instance()
{
}

DX12Instance::~DX12Instance()
{
}

const std::vector<DeviceInfo> DX12Instance::Init(/*const uint32_t _uWidth, const uint32_t _uHeight, HWND _hWnd, HINSTANCE _hInstanc*/)
{

	return std::vector<DeviceInfo>();
}

const THandle DX12Instance::MakeWindow(const THandle _hPresentDeviceHandle, const uint32_t _uWidth, const uint32_t _uHeight, HWND _hWnd, HINSTANCE _hInstance)
{
	return THandle();
}

void DX12Instance::OnChangeDisplaySettings(const uint32_t _uWidth, const uint32_t _uHeight)
{
}
