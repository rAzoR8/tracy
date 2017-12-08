#ifndef TRACY_SHADERFACTORYLOADER_H
#define TRACY_SHADERFACTORYLOADER_H

#ifdef STANDARD_DLL
#include <dll>
namespace dll = std::dll;
#else
#include <boost/dll.hpp>
namespace dll = boost::dll;
#endif

#include <boost/function.hpp>

#include "IShaderFactoryConsumer.h"
#include <unordered_map>
#include "Singleton.h"

namespace Tracy
{
	class ShaderFactoryLoader : public hlx::Singleton<ShaderFactoryLoader>
	{
		friend class IShaderFactoryConsumer;
	public:
		typedef TFactoryPtr(get_factory_func)();
		using TFactoryFunc = get_factory_func;

		struct ShaderLib
		{
			ShaderLib() {}
			~ShaderLib();

			dll::shared_library Lib;
			TFactoryPtr pFactory = nullptr;
			std::vector<IShaderFactoryConsumer*> Consumers;

			bool Load(const std::wstring& _sName);
			void Unload(const bool _bKeepConsumers);
		};

		using TLibMap = std::unordered_map<std::wstring, ShaderLib>;

		ShaderFactoryLoader();
		~ShaderFactoryLoader();

		// or reload
		bool Load(const std::wstring& _sLibName, ShaderLib** _pLibOut = nullptr);

		// does not remove the lib!
		void Unload(const std::wstring& _sLibName, const bool _bKeepConsumers);

	private:
		void AddConsumer(IShaderFactoryConsumer* _pConsumer);
		void RemoveConsumer(IShaderFactoryConsumer* _pConsumer);

	private:

		// lib name -> dll
		TLibMap m_ShaderLibs;
	};
} // Tracy

#endif // !TRACY_SHADERFACTORYLOADER_H
