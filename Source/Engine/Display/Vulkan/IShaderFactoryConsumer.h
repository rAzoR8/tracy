#ifndef TRACY_ISHADERFACTORYCONSUMER_H
#define TRACY_ISHADERFACTORYCONSUMER_H

#include "..\SPIRVShaderFactory\ShaderFactory.h"
#include "VulkanDevice.h"
#include <unordered_map>
#include "FunctionalUtils.h"
#include "SPIRVInterop.h"

namespace Tracy
{
	struct CompiledShader
	{
		ShaderID Identifier;
		uint64_t uIDHash = 0u;
		vk::PipelineShaderStageCreateInfo StageCreateInfo;
		SPIRVModule Code;
		uint64_t uSpecConstHash = 0u;
		vk::SpecializationInfo SpecInfo;
	};

	class IShaderFactoryConsumer
	{
		friend class ShaderFactoryLoader;
	public:

		using THashFunc = std::function<uint64_t(const ShaderID, const void*, const size_t)>;

		IShaderFactoryConsumer(const std::wstring& _sLibName, const std::wstring& _sFactory, const THandle _hDevice = 0);
		virtual ~IShaderFactoryConsumer();

		const std::wstring& GetFactoryName() const { return m_sFactory; }
		const std::wstring& GetLibName() const { return m_sLib; }

		template <class TFunc>
		void SetShaderHashFunction(const TFunc& _Func);

	private:
		void FactoryLoaded(const TFactoryPtr& _pFactory);
		void FactoryUnloaded();

		// ignores userdata, pass through id
		inline static uint64_t DefaultShaderHash(const ShaderID _uShaderIdentifier, const void* _pUserData = nullptr, const size_t _uSize = 0u) { return _uShaderIdentifier.uID; }

	protected:
		// loaded or reloaded
		virtual void OnFactoryLoaded() {}
		virtual void OnFactoryUnloaded() {}

		SPIRVModule GetModule(const ShaderID _uShaderIdentifier, const void* _pUserData = nullptr, const size_t _uSize = 0u);
		bool HasValidFactory() const { return m_pFactory != nullptr; }

		void SelectShader(const ShaderID _uShaderIdentifier, const SpecConstFactory* _pSpecConstFactory = nullptr, const void* _pUserData = nullptr, const size_t _uSize = 0u);
		void DeactivateStage(const EShaderType _kType);

	private:
		VulkanDevice& m_Device;
		const std::wstring m_sLib;
		const std::wstring m_sFactory;
		TFactoryPtr m_pFactory = nullptr;

		THashFunc m_ShaderHasher = DefaultShaderHash;

		std::array<CompiledShader*, kShaderType_NumOf> m_ActiveShaders;

		// hash -> module
		std::unordered_map<uint64_t, CompiledShader> m_ShaderModules;
	};
	//---------------------------------------------------------------------------------------------------

	template<class TFunc>
	inline void IShaderFactoryConsumer::SetShaderHashFunction(const TFunc& _Func)
	{
		m_ShaderHasher = _Func;
	}
} // Tracy

#endif // !TRACY_ISHADERFACTORYCONSUMER_H
