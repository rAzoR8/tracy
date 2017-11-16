#ifndef TRACY_DX12DEVICE_H
#define TRACY_DX12DEVICE_H

#include "../IDevice.h"
#include "StandardDefines.h"
#include "DX12API.h"

namespace Tracy
{
	class DX12Device : public IDevice
	{
	public:
		explicit DX12Device(IDXGIAdapter1* _Adapter, const THandle _uHandle);
		~DX12Device();

		const IDXGIAdapter1* GetAdapter() const;
		const ID3D12Device2* GetDevice() const;

	private:
		// Adapter: https://msdn.microsoft.com/en-us/library/windows/desktop/bb174523(v=vs.85).aspx
		IDXGIAdapter1* m_pAdapter;

		// Device: https://msdn.microsoft.com/en-us/library/windows/desktop/dn788650(v=vs.85).aspx
		ID3D12Device2* m_pDevice;

		// Command Queue: https://msdn.microsoft.com/en-us/library/windows/desktop/dn788627(v=vs.85).aspx
		ID3D12CommandQueue* m_pQueueGraphics;
		ID3D12CommandQueue* m_pQueueCompute;
		ID3D12CommandQueue* m_pQueueTransfer;
	};
}

#endif // !TRACY_DX12DEVICE_H

