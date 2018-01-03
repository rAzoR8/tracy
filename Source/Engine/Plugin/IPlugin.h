#ifndef TRACY_IPLUGIN_H
#define TRACY_IPLUGIN_H

//#include "..\SPIRVGen\SPIRVModule.h"
//#include "ShaderIdentifier.h"

#ifdef COMPILE_SHADERFACTROY_DLL
#define DLLINTERFACE  __declspec(dllexport) 
#else
#define DLLINTERFACE  __declspec(dllimport) 
#endif

#include <string>
#include <boost\dll\alias.hpp>

namespace Tracy
{
	static constexpr uint32_t kPluginInterfaceVersion = 1u;

	class DLLINTERFACE IPlugin
	{
	public:
		IPlugin() {};
		virtual ~IPlugin() {};

		virtual uint32_t GetInterfaceVersion() const = 0;
		virtual uint32_t GetPluginVersion() const = 0;
		// TODO: maybe provide some info like: is threadsafe & caches modules

		virtual std::wstring GetIdentifier() const = 0;

		virtual void Release() = 0;
	};

	//using TPluginPtr = IPlugin*;

#define GETPLUGIN_ALIAS get_tracy_plugin
#define GETPLUGIN_ALIASNAME "get_tracy_plugin"

#define PLUGIN_INTERFACE(_type, _version)	static _type* GetPlugin(){ return new _type();} \
											uint32_t GetInterfaceVersion() const final { return kPluginInterfaceVersion; } \
											uint32_t GetPluginVersion() const final { return _version;} \
											std::wstring GetIdentifier() const final {return L#_type;}

	// GetPlugin with complete namespace: Tracy::PluginType::GetPlugin
#define PLUGIN_ALIAS(_funcname) BOOST_DLL_ALIAS(_funcname, GETPLUGIN_ALIAS);

} // Tracy

#endif // !TRACY_SHADERFACTORY_H
