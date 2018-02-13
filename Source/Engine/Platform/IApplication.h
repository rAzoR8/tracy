#ifndef TRACY_IAPPLICATION_H
#define TRACY_IAPPLICATION_H

#include "StandardDefines.h"
#include "..\Display\Renderer.h"
#include <memory>

namespace Tracy
{
	enum EGraphicsAPI
	{
		kGraphicsAPI_Vulkan = 0,
		kGraphicsAPI_D3D12,

		kGraphicsAPI_NumOf,
		kGraphicsAPI_Unknown = kGraphicsAPI_NumOf
	};

	class IApplication
	{
	public:
		virtual ~IApplication() {}

		bool Initialize(const uint32_t _uWidth, const uint32_t _uHeight, const EGraphicsAPI _eAPI, const RenderGraphDesc& _RenderDesc);

	protected:
		virtual std::unique_ptr<Renderer> OnInit(const uint32_t _uWidth, const uint32_t _uHeight, const EGraphicsAPI _eAPI, const RenderGraphDesc& _RenderDesc) = 0;
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

		inline const EGraphicsAPI GetGfxAPI() const { return m_kGfxAPI; }

	private:
		inline void SetGfxAPI(const EGraphicsAPI _kAPI) { m_kGfxAPI = _kAPI; }

	private:
		EGraphicsAPI m_kGfxAPI = kGraphicsAPI_Unknown;
	};
}

#endif // !TRACY_IAPPLICATION_H
