#ifndef TRACY_DX12DEVICE_H
#define TRACY_DX12DEVICE_H

#include "DX12API.h"

namespace Tracy
{
	class DX12Device
	{
	public:

	private:
		// Adapter: https://msdn.microsoft.com/en-us/library/windows/desktop/bb174523(v=vs.85).aspx
		ComPtr<IDXGIAdapter1> m_adapter;

		// Device: https://msdn.microsoft.com/en-us/library/windows/desktop/dn788650(v=vs.85).aspx
		ComPtr<ID3D12Device2> m_device;
	};
}

#endif // !TRACY_DX12DEVICE_H

