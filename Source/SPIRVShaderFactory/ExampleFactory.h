#ifndef TRACY_EXAMPLEFACTORY_H
#define TRACY_EXAMPLEFACTORY_H

#include "ShaderFactory.h"
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

		FACTORYINTERFACE(ExampleFactory, 2u);
	private:

		SPIRVModule Compile(const ShaderID _ShaderIdentifier) const;

	private:
		std::unordered_map<uint64_t, SPIRVModule> m_Modules;
	};

	FACTORY_ALIAS(Tracy::ExampleFactory::GetShaderFactory)
} // Tracy

#endif // !TRACY_EXAMPLEFACTORY_H
