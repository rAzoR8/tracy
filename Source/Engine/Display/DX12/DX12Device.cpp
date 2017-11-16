#include "DX12Device.h"

#include "Logger.h"

using namespace Tracy;

Tracy::DX12Device::DX12Device(IDXGIAdapter1* _pAdapter, const THandle _uHandle) :
	m_pAdapter(_pAdapter)
{
	m_Info.hHandle = _uHandle;

	HRESULT Result;

	// Logical Device
	Result = D3D12CreateDevice(m_pAdapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&m_pDevice));
	HASSERT(Result == S_OK, "Failed to Create DX12 Logical device with code: %#010x", Result);

	DXGI_ADAPTER_DESC1 AdapterDesc;
	m_pAdapter->GetDesc1(&AdapterDesc);

	m_Info.VendorID = ToVendorID(AdapterDesc.VendorId);
	m_Info.uTotalMemory = AdapterDesc.DedicatedVideoMemory;

	D3D12_COMMAND_QUEUE_DESC QueueDesc{};
	QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	// Graphics Queue
	{
		QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		Result = m_pDevice->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&m_pQueueGraphics));
		HASSERT(Result == S_OK, "Failed to Create DX12 Graphics queue with code: %#010x", Result);
	}
	// Compute Queue
	{
		QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
		Result = m_pDevice->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&m_pQueueCompute));
		HASSERT(Result == S_OK, "Failed to Create DX12 Compute queue with code: %#010x", Result);
	}
	// Transfer Queue
	{
		QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_COPY;
		Result = m_pDevice->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&m_pQueueTransfer));
		HASSERT(Result == S_OK, "Failed to Create DX12 Transfer queue with code: %#010x", Result);
	}
}
