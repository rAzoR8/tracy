#ifndef TRACY_EXAMPLEFACTORY_H
#define TRACY_EXAMPLEFACTORY_H

#include "Display\Vulkan\IShaderFactory.h"
#include <unordered_map>

namespace Tracy
{
	class ExampleFactory : public IShaderFactory
	{
	public:
		ExampleFactory();
		~ExampleFactory();

		SPIRVModule GetModule(const ShaderID _ShaderIdentifier, const void* _pUserData = nullptr, const size_t _uSize = 0u) final;
		void Release() final;

		PLUGIN_INTERFACE(ExampleFactory, 2u);
	private:

		SPIRVModule Compile(const ShaderID _ShaderIdentifier) const;

	private:
		std::unordered_map<uint64_t, SPIRVModule> m_Modules;
	};

	PLUGIN_ALIAS(Tracy::ExampleFactory::GetPlugin)
} // Tracy

#endif // !TRACY_EXAMPLEFACTORY_H
