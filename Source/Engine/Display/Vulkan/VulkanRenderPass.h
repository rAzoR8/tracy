#ifndef TRACY_VULKANRENDERPASS_H
#define TRACY_VULKANRENDERPASS_H

#include "IShaderFactoryConsumer.h"

namespace Tracy
{
	struct ShaderCfg
	{
		ShaderID Identifier;
		hlx::bytes UserData;
		// spec const data?
	};

	using TPipelineCfg = std::vector<ShaderCfg>;

	struct RenderPassDesc
	{
		// shaders / pipelines that are frequently used
		std::vector<TPipelineCfg> DefaultPipelines; // pipelines will be created for these on Initialize
	};

	class VulkanRenderPass : public IShaderFactoryConsumer
	{
	public:
		VulkanRenderPass(const std::wstring& _sPassName, const std::wstring& _sLibName, const std::wstring& _sFactory, const THandle _hDevice = 0);
		~VulkanRenderPass();

		bool Initialize(const RenderPassDesc& _Desc);
		void Uninitialize();

	private:
		void OnFactoryLoaded() final;
		void OnFactoryUnloaded() final;

		// called before draw or after shader has been selected
		bool ActivatePipeline(const bool _bBindToCommandBuffer = true);

		bool LoadPipelineCache(const std::wstring& _sPath);
		bool StorePipelineCache(const std::wstring& _sPath);

	private:
		const std::wstring m_sPassName;
		bool m_bStorePipelines = true;

		// identifies the current pipeline
		size_t m_uPipelineHash = kUndefinedSizeT;
		vk::Pipeline m_ActivePipeline = nullptr;

		// pipeline description hash -> pipeline
		std::unordered_map<size_t, vk::Pipeline> m_Pipelines;

		vk::PipelineCache m_PipelineCache = nullptr;
	};

} // Tracy

#endif // !TRACY_VULKANRENDERPASS_H
