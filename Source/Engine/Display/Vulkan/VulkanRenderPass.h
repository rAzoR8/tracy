#ifndef TRACY_VULKANRENDERPASS_H
#define TRACY_VULKANRENDERPASS_H

#include "IShaderFactoryConsumer.h"

namespace Tracy
{
	class VulkanRenderPass : public IShaderFactoryConsumer
	{
	public:
		VulkanRenderPass(const std::wstring& _sPassName, const std::wstring& _sLibName, const std::wstring& _sFactory, const THandle _hDevice = 0);
		~VulkanRenderPass();

	private:
		void OnFactoryLoaded() final {}
		void OnFactoryUnloaded() final {}

		// called before draw or after shader has been selected
		bool ActivatePipeline();

		void LoadPipelineCache(const std::wstring& _sPath);
		void StorePipelineCache(const std::wstring& _sPath);

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
