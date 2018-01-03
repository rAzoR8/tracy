#ifndef TRACY_ISHADERFACTORY_H
#define TRACY_ISHADERFACTORY_H

#include "Plugin\IPlugin.h"
#include "..\SPIRVGen\SPIRVModule.h"
#include "Display\DisplayTypes.h"

namespace Tracy
{
	class IShaderFactory : public IPlugin
	{
	public:
		virtual SPIRVModule GetModule(const ShaderID _uShaderIdentifier, const void* _pUserData = nullptr, const size_t _uSize = 0u) = 0;
	};
}

#endif // !TRACY_ISHADERFACTORY_H
