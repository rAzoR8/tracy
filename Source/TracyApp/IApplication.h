#ifndef TRACY_IAPPLICATION_H
#define TRACY_IAPPLICATION_H

#include "StandardDefines.h"
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
		virtual bool Init(const uint32_t _uWidth, const uint32_t _uHeight, const EGraphicsAPI _eAPI) = 0;
		virtual int Run() = 0;
	};
}

#endif // !TRACY_IAPPLICATION_H
