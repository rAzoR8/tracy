#ifndef TRACY_ISHADERFACTORYCONSUMER_H
#define TRACY_ISHADERFACTORYCONSUMER_H

#include "..\SPIRVShaderFactory\ShaderFactory.h"
#include "VulkanAPI.h"
#include <unordered_map>
#include "FunctionalUtils.h"

namespace Tracy
{
	struct CompiledShader
	{
		vk::ShaderModule hModule;
		SPIRVModule Code;
	};

	class IShaderFactoryConsumer
	{
		friend class ShaderFactoryLoader;
	public:

		// ignores userdata, pass through id
		//HFUNCTOR(DefaultShaderHash, (const ShaderID _uShaderIdentifier, const void* _pUserData = nullptr, const size_t _uSize = 0u) { return _uShaderIdentifier.uID; })

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

		std::array<CompiledShader*, kShaderType_NumOf> m_ActiveShaders;

		// hash -> module
		std::unordered_map<uint64_t, CompiledShader> m_ShaderModules;
	};
} // Tracy

#endif // !TRACY_ISHADERFACTORYCONSUMER_H
