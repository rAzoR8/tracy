#ifndef TRACY_SHADERFACTORY_H
#define TRACY_SHADERFACTORY_H

#include "SPIRVModule.h"

#ifdef COMPILE_SHADERFACTROY_DLL
#define DLLINTERFACE  __declspec(dllexport) 
#else
#define DLLINTERFACE  __declspec(dllimport) 
#endif

namespace Tracy
{
	class DLLINTERFACE IShaderFactory
	{
	public:
		IShaderFactory();
		virtual ~IShaderFactory();

		virtual SPIRVModule GetModule(const uint64_t _uShaderIdentifier, const void* _pUserData = nullptr, const size_t _uSize = 0u) = 0;
		virtual void Release() = 0;

		virtual IShaderFactory* GetShaderFactory() = 0;

	private:

	};

	IShaderFactory::IShaderFactory()
	{
	}

	IShaderFactory::~IShaderFactory()
	{
	}

} // Tracy

#endif // !TRACY_SHADERFACTORY_H
