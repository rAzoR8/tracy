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

		IShaderFactoryConsumer(const std::wstring& _sLibName, const THandle _hDevice = 0u);
		virtual ~IShaderFactoryConsumer();

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

		bool HasValidFactory() const { return m_pFactory != nullptr; }

		void SelectShader(const ShaderID _uShaderIdentifier, const SpecConstFactory* _pSpecConstFactory = nullptr, const void* _pUserData = nullptr, const size_t _uSize = 0u);
		void DeactivateStage(const EShaderType _kType);

		const vk::Device& VKDevice() const;

	private:
		const std::wstring m_sLib;
		TFactoryPtr m_pFactory = nullptr;

		THashFunc m_ShaderHasher = DefaultShaderHash;

		// hash -> module
		std::unordered_map<uint64_t, CompiledShader> m_ShaderModules;

	protected:
		VulkanDevice& m_Device;
		std::array<CompiledShader*, kShaderType_NumOf> m_ActiveShaders;
	};
	//---------------------------------------------------------------------------------------------------

	template<class TFunc>
	inline void IShaderFactoryConsumer::SetShaderHashFunction(const TFunc& _Func)
	{
		m_ShaderHasher = _Func;
	}

	inline const vk::Device& IShaderFactoryConsumer::VKDevice() const
	{
		return m_Device.GetDevice();
	}
} // Tracy

#endif // !TRACY_ISHADERFACTORYCONSUMER_H
