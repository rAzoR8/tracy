#ifndef TRACY_ISHADERFACTORYCONSUMER_H
#define TRACY_ISHADERFACTORYCONSUMER_H

#include "..\SPIRVShaderFactory\IShaderFactory.h"
#include "..\SPIRVGen\SPIRVInterop.h"
#include "VulkanDevice.h"
#include <unordered_map>
#include "FunctionalUtils.h"
#include "PluginLoader.h"

namespace Tracy
{
	struct CompiledShader
	{
		Spear::ShaderID Identifier;
		uint64_t uIDHash = 0u;
		vk::PipelineShaderStageCreateInfo StageCreateInfo;
        Spear::SPIRVModule Code;
		uint64_t uSpecConstHash = 0u;
		vk::SpecializationInfo SpecInfo;
	};

	class IShaderFactoryConsumer : public hlx::IPluginConsumer<Spear::IShaderFactory>
	{
	public:

		using THashFunc = std::function<uint64_t(const Spear::ShaderID, const void*, const size_t)>;

		IShaderFactoryConsumer(const std::wstring& _sLibName, const THandle _hDevice);
		virtual ~IShaderFactoryConsumer();

		template <class TFunc>
		void SetShaderHashFunction(const TFunc& _Func);

	private:

		// ignores userdata, pass through id
		inline static uint64_t DefaultShaderHash(const Spear::ShaderID _uShaderIdentifier, const void* _pUserData = nullptr, const size_t _uSize = 0u) { return _uShaderIdentifier.uID; }

	protected:
		// reloaded
		void OnPluginReloaded(Spear::IShaderFactory* _pFactory) override;
		void OnPluginUnloaded() override;
		void UninitializeFactory();

		virtual void OnFactoryLoaded() = 0;
		virtual void OnFactoryUnloaded() = 0;

		// returns true if shader changed
		bool SelectShader(const Spear::ShaderID _uShaderIdentifier, const Spear::SpecConstFactory* _pSpecConstFactory = nullptr, const void* _pUserData = nullptr, const size_t _uSize = 0u);
		void DeactivateStage(const Spear::EShaderType _kType);

		const vk::Device& VKDevice() const;

	private:
		THashFunc m_ShaderHasher = DefaultShaderHash;

		// hash -> module
		std::unordered_map<uint64_t, CompiledShader> m_ShaderModules;

	protected:
		VulkanDevice& m_Device;
		std::array<CompiledShader*, Spear::kShaderType_NumOf> m_ActiveShaders;
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
