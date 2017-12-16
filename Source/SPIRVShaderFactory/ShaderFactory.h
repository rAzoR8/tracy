#ifndef TRACY_SHADERFACTORY_H
#define TRACY_SHADERFACTORY_H

#include "..\SPIRVGen\SPIRVModule.h"
#include "ShaderIdentifier.h"

#ifdef COMPILE_SHADERFACTROY_DLL
#define DLLINTERFACE  __declspec(dllexport) 
#else
#define DLLINTERFACE  __declspec(dllimport) 
#endif

#include <boost\dll\alias.hpp>

namespace Tracy
{
	static constexpr uint32_t kFactoryInterfaceVersion = 1u;

	class DLLINTERFACE IShaderFactory
	{
	public:
		IShaderFactory() {};
		virtual ~IShaderFactory() {};

		virtual uint32_t GetInterfaceVersion() const = 0;
		virtual uint32_t GetFactoryVersion() const = 0;
		// TODO: maybe provide some info like: is threadsafe & caches modules

		virtual std::wstring GetIdentifier() const = 0;
		virtual SPIRVModule GetModule(const ShaderID _uShaderIdentifier, const void* _pUserData = nullptr, const size_t _uSize = 0u) = 0;

		virtual void Release() = 0;
	};

	using TFactoryPtr = IShaderFactory*;

#define GETFACTORY_ALIAS get_shader_factory
#define GETFACTORY_ALIASNAME "get_shader_factory"

#define FACTORYINTERFACE(_type, _version)	static TFactoryPtr GetShaderFactory(){ return new _type();} \
											uint32_t GetInterfaceVersion() const final { return kFactoryInterfaceVersion; } \
											uint32_t GetFactoryVersion() const final { return _version;} \
											std::wstring GetIdentifier() const final {return L#_type;}

#define FACTORY_ALIAS(_funcname) BOOST_DLL_ALIAS(_funcname, GETFACTORY_ALIAS);

//#define DLLINTERFACE ()
} // Tracy

#endif // !TRACY_SHADERFACTORY_H
