#include "DX12Device.h"

#include "Logger.h"

using namespace Tracy;

Tracy::DX12Device::DX12Device(const ComPtr<IDXGIAdapter1> _Adapter, const THandle _uHandle) :
	m_Adapter(std::move(_Adapter)),
	m_uHandle(_uHandle)
{
}
