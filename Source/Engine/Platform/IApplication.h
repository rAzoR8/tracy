#ifndef TRACY_IAPPLICATION_H
#define TRACY_IAPPLICATION_H

#include "Display/DeviceInfo.h"
#include "Display/Renderer.h"
#include <memory>

namespace Tracy
{
	class IApplication
	{
	public:
		virtual ~IApplication() {}

		bool InitAPI(const uint32_t _uWidth, const uint32_t _uHeight, std::vector<DeviceInfo>& _OutDevices);

		bool InitWindowAndRenderer(const RenderGraphDesc& _Desc, const THandle _hDevice);

		inline const std::unique_ptr<Renderer>& GetRenderer() const { return m_pRenderer; };
		inline std::unique_ptr<Renderer>& GetRenderer() { return m_pRenderer; };

	protected:
		virtual bool OnInitAPI(const uint32_t _uWidth, const uint32_t _uHeight) = 0;

		virtual bool OnInitWindow(const THandle _hDevice, THandle& _hWnd) = 0;

		virtual int Run() = 0;

	protected:
		std::unique_ptr<Renderer> m_pRenderer = nullptr;
	};

	class ApplicationInfo
	{
		friend class IApplication;
	public:
		static ApplicationInfo& Instance()
		{
			static ApplicationInfo Info;
			return Info;
		}
	};
}

#endif // !TRACY_IAPPLICATION_H
