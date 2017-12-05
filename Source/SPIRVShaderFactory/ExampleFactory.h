#ifndef TRACY_EXAMPLEFACTORY_H
#define TRACY_EXAMPLEFACTORY_H

#include "ShaderFactory.h"
#include <unordered_map>

namespace Tracy
{
	class /*DLLINTERFACE*/ ExampleFactory : public IShaderFactory
	{
	public:
		ExampleFactory();
		~ExampleFactory();

		std::string GetIdentifier() const final { return "ExampleFactory"; }
		SPIRVModule GetModule(const ShaderID _ShaderIdentifier, const void* _pUserData = nullptr, const size_t _uSize = 0u) final;
		void Release() final;
	private:

		SPIRVModule Compile(const ShaderID _ShaderIdentifier) const;

	private:
		std::unordered_map<uint64_t, SPIRVModule> m_Modules;
	};
} // Tracy

#endif // !TRACY_EXAMPLEFACTORY_H
