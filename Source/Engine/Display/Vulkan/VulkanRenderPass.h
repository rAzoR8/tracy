#ifndef TRACY_VULKANRENDERPASS_H
#define TRACY_VULKANRENDERPASS_H

#include "IShaderFactoryConsumer.h"
#include "..\RenderPassDescription.h"

namespace Tracy
{
	class VulkanRenderPass : public IShaderFactoryConsumer
	{
		friend class VulkanRenderGraph;
	public:
		struct Dependence
		{
			VulkanRenderPass* pPrevPass;

			// TODO: pointer to resource or something cool
			std::vector<InputDependency::Resource> Resources;

			// add pipeline barriers etc
		};
		
		struct ViewportState
		{
			std::vector<vk::Viewport> Viewports;
			std::vector<vk::Rect2D> Scissors;
		};

		VulkanRenderPass(const RenderPassDesc& _Desc, const uint32_t _uPassIndex, const THandle _hDevice = 0);
		~VulkanRenderPass();

		bool Initialize();
		void Uninitialize();

		uint32_t GetPassIndex() const;
		uint64_t GetMaterialID() const;

		const RenderPassDesc& GetDescription() const;

	private:
		void OnFactoryLoaded() final;
		void OnFactoryUnloaded() final;

		void AddDependency(const Dependence& _Dependency);

		// prepares command buffer & dynamic state for recording
		void ActivePass();

		// called before draw or after shader has been selected
		bool ActivatePipeline();
		const size_t CreatePipelineLayout(const std::array<TVarSet, uMaxDescriptorSets>& _Sets, const uint32_t uLastSet, vk::PipelineLayout& _OutPipeline, const PushConstantFactory* _pPushConstants = nullptr);

		bool LoadPipelineCache(const std::wstring& _sPath);
		bool StorePipelineCache(const std::wstring& _sPath);

	private:
		RenderPassDesc m_Description;
		// index relative to parent pass or rendergraph (index into vector)
		const uint32_t m_uPassIndex; 

		ViewportState m_ViewportState;

		std::vector<VulkanRenderPass> m_SubPasses;
		std::vector<Dependence> m_Dependencies;

		// identifies the current pipeline
		size_t m_uPipelineHash = kUndefinedSizeT;
		vk::Pipeline m_ActivePipeline = nullptr;

		std::unordered_map<size_t, vk::DescriptorSetLayout> m_DescriptorSetLayouts;
		std::unordered_map<size_t, vk::PipelineLayout> m_PipelineLayouts;

		// pipeline description hash -> pipeline
		std::unordered_map<size_t, vk::Pipeline> m_Pipelines;

		vk::PipelineCache m_PipelineCache = nullptr;
	};

	inline uint32_t VulkanRenderPass::GetPassIndex() const{	return m_uPassIndex;}

	inline uint64_t VulkanRenderPass::GetMaterialID() const	{ return 1ull << m_uPassIndex;}

	inline const RenderPassDesc& VulkanRenderPass::GetDescription() const {return m_Description;	}

} // Tracy

#endif // !TRACY_VULKANRENDERPASS_H
