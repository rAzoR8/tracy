#ifndef TRACY_DEFAULTFACTORY_H
#define TRACY_DEFAULTFACTORY_H

#include "Display\Vulkan\IShaderFactory.h"
#include <unordered_map>

namespace Tracy
{
	class TracyDefaultShaderFactory : public IShaderFactory
	{
	public:
		TracyDefaultShaderFactory();
		~TracyDefaultShaderFactory();

		SPIRVModule GetModule(const ShaderID _ShaderIdentifier, const void* _pUserData = nullptr, const size_t _uSize = 0u) final;
		void Release() final;

		PLUGIN_INTERFACE(TracyDefaultShaderFactory, 2u);
	private:

		SPIRVModule Compile(const ShaderID _ShaderIdentifier) const;

	private:
		std::unordered_map<uint64_t, SPIRVModule> m_Modules;
	};

	PLUGIN_ALIAS(Tracy::TracyDefaultShaderFactory::GetPlugin)
} // Tracy

#endif // !TRACY_DEFAULTFACTORY_H
