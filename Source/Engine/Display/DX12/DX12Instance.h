#ifndef TRACY_DX12INSTANCE_H
#define TRACY_DX12INSTANCE_H

#include "../IGraphicsInstance.h"
#include "DX12Device.h"
#include <unordered_map>

namespace Tracy
{
	class DX12Instance : public IGraphicsInstance
	{
	public:
		static DX12Instance& GetInstance()
		{
			static DX12Instance Instance;
			return Instance;
		}

		DX12Instance(const DX12Instance&) = delete;
		DX12Instance& operator=(const DX12Instance&) = delete;
		DX12Instance(DX12Instance&&) = delete;
		DX12Instance& operator=(DX12Instance&&) = delete;

		~DX12Instance();

		// Virtual Functions
		const std::vector<DeviceInfo> Init() final;
		const THandle MakeWindow(const THandle _hPresentDeviceHandle, const uint32_t _uWidth, const uint32_t _uHeight, HWND _hWnd, HINSTANCE _hInstance) final;
		void OnChangeDisplaySettings(const uint32_t _uWidth, const uint32_t _uHeight) final;

	private:
		DX12Instance();

		// Factory: 
		IDXGIFactory5* m_pFactory;

		// Devices
		std::unordered_map<THandle, DX12Device> m_Devices;
	};
}

#endif // !TRACY_DX12INSTANCE_H
