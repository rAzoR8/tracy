#ifndef TRACY_SHADERFACTORYLOADER_H
#define TRACY_SHADERFACTORYLOADER_H

#ifdef STANDARD_DLL
#include <dll>
namespace dll = std::dll;
#else
#include <boost\dll.hpp>
namespace dll = boost::dll;
#endif

#include "..\SPIRVShaderFactory\ShaderFactory.h"
#include <unordered_map>
#include "Singleton.h"

namespace Tracy
{
	class IShaderFactoryConsumer
	{
	public:
		IShaderFactoryConsumer(const std::string& _sFactoryIdentifier);
		virtual ~IShaderFactoryConsumer();
		// loaded or reloaded
		virtual void OnFactoryLoaded(const TFactoryPtr& _pFactory) {}
		virtual void OnFactoryUnloaded() {}

		const std::string& GetFactoryIdentifier() const { return m_sFactoryIdentifier; }

	private:
		const std::string m_sFactoryIdentifier;
	};

	class ShaderFactoryLoader : public hlx::Singleton<ShaderFactoryLoader>
	{
		friend class IShaderFactoryConsumer;
	public:
		ShaderFactoryLoader();
		~ShaderFactoryLoader();

		bool Load(const std::string& _sLibPath);

	private:
		void AddConsumer(IShaderFactoryConsumer* _pConsumer);
		void RemoveConsumer(IShaderFactoryConsumer* _pConsumer);

	private:
		std::unordered_map<std::string, TFactoryPtr> m_ShaderFactories;

		std::unordered_map<std::string, IShaderFactoryConsumer*> m_FactoryConsumers;
	};
} // Tracy

#endif // !TRACY_SHADERFACTORYLOADER_H
