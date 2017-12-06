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

#include "..\SPIRVShaderFactory\ShaderFactory.h"
#include <unordered_map>
#include "Singleton.h"

namespace Tracy
{
	class IShaderFactoryConsumer
	{
		friend class ShaderFactoryLoader;
	public:
		IShaderFactoryConsumer(const std::wstring& _sLibName, const std::wstring& _sFactory);
		virtual ~IShaderFactoryConsumer();

		const std::wstring& GetFactoryName() const { return m_sFactory; }
		const std::wstring& GetLibName() const { return m_sLib; }

	private:
		void FactoryLoaded(const TFactoryPtr& _pFactory);
		void FactoryUnloaded();

	protected:
		// loaded or reloaded
		virtual void OnFactoryLoaded() {}
		virtual void OnFactoryUnloaded() {}

		SPIRVModule GetModule(const ShaderID _uShaderIdentifier, const void* _pUserData = nullptr, const size_t _uSize = 0u);
		bool HasValidFactory() const { return m_pFactory != nullptr; }

	private:
		const std::wstring m_sLib;
		const std::wstring m_sFactory;
		TFactoryPtr m_pFactory = nullptr;
	};

	class ShaderFactoryLoader : public hlx::Singleton<ShaderFactoryLoader>
	{
		friend class IShaderFactoryConsumer;
	public:
		typedef TFactoryPtr(get_factory_func)();
		//using TFactoryFunc = typename dll::detail::library_function<get_factory_func>;
		using TFactoryFunc = get_factory_func;

		struct ShaderLib
		{
			ShaderLib() {}
			~ShaderLib();

			dll::shared_library Lib;
			//TFactoryFunc CreateFactoryFunc;
			TFactoryPtr pFactory = nullptr;
			std::vector<IShaderFactoryConsumer*> Consumers;

			bool Load(const std::wstring& _sName);
			void Unload();
		};

		using TLibMap = std::unordered_map<std::wstring, ShaderLib>;

		ShaderFactoryLoader();
		~ShaderFactoryLoader();

		// or reload
		bool Load(const std::wstring& _sLibName, ShaderLib** _pLibOut = nullptr);

	private:
		void AddConsumer(IShaderFactoryConsumer* _pConsumer);
		void RemoveConsumer(IShaderFactoryConsumer* _pConsumer);

	private:

		// lib name -> dll
		TLibMap m_ShaderLibs;
	};
} // Tracy

#endif // !TRACY_SHADERFACTORYLOADER_H
