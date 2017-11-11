#ifndef TRACY_DX12DEVICE_H
#define TRACY_DX12DEVICE_H

#include "DX12API.h"
#include "StandardDefines.h"

namespace Tracy
{
	class DX12Device
	{
	public:
		explicit DX12Device(const ComPtr<IDXGIAdapter1> _Adapter, const THandle _uHandle);
		~DX12Device();

		const ComPtr<IDXGIAdapter1> GetAdapter() const;
		const ComPtr<ID3D12Device2> GetDevice() const;

	private:
		// Adapter: https://msdn.microsoft.com/en-us/library/windows/desktop/bb174523(v=vs.85).aspx
		ComPtr<IDXGIAdapter1> m_Adapter;

		// Device: https://msdn.microsoft.com/en-us/library/windows/desktop/dn788650(v=vs.85).aspx
		ComPtr<ID3D12Device2> m_Device;

		THandle m_uHandle;
	};
}

#endif // !TRACY_DX12DEVICE_H

