#include "IApplication.h"

using namespace Tracy;

bool IApplication::Initialize(const uint32_t _uWidth, const uint32_t _uHeight, const EGraphicsAPI _eAPI, const RenderGraphDesc& _RenderDesc)
{
	m_pRenderer = OnInit(_uWidth, _uHeight, _eAPI, _RenderDesc);

	if (m_pRenderer)
	{
		return m_pRenderer->Init();
	}

	return false;
}
