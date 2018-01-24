#ifndef TRACY_IAPPLICATION_H
#define TRACY_IAPPLICATION_H

#include "StandardDefines.h"
#include "..\Display\Renderer.h"
#include <memory>

namespace Tracy
{
	enum class EGraphicsAPI
	{
		eVulkan = 0,
		eD3D12
	};

	class IApplication
	{
	public:
		virtual ~IApplication() {}

		bool Initialize(const uint32_t _uWidth, const uint32_t _uHeight, const EGraphicsAPI _eAPI, const RenderGraphDesc& _RenderDesc);

	protected:
		virtual std::unique_ptr<Renderer> OnInit(const uint32_t _uWidth, const uint32_t _uHeight, const EGraphicsAPI _eAPI, const RenderGraphDesc& _RenderDesc) = 0;
		virtual int Run() = 0;

	private:
		std::unique_ptr<Renderer> m_pRenderer = nullptr;
	};
}

#endif // !TRACY_IAPPLICATION_H
