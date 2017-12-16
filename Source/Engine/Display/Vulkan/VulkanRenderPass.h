#ifndef TRACY_VULKANRENDERPASS_H
#define TRACY_VULKANRENDERPASS_H

#include "IShaderFactoryConsumer.h"
#include "..\RenderPassDescription.h"
#include "UniqueAssociationID.h"

namespace Tracy
{
	class VulkanRenderPass : public IShaderFactoryConsumer
	{
	public:
		VulkanRenderPass(const RenderPassDesc& _Desc, const THandle _hDevice = 0);
		~VulkanRenderPass();

		bool Initialize();
		void Uninitialize();

		uint64_t GetMaterialID() const;

	private:
		void OnFactoryLoaded() final;
		void OnFactoryUnloaded() final;

		// called before draw or after shader has been selected
		bool ActivatePipeline();
		const size_t CreatePipelineLayout(const std::array<TVarSet, uMaxDescriptorSets>& _Sets, const uint32_t uLastSet, vk::PipelineLayout& _OutPipeline, const PushConstantFactory* _pPushConstants = nullptr);

		bool LoadPipelineCache(const std::wstring& _sPath);
		bool StorePipelineCache(const std::wstring& _sPath);

	private:
		RenderPassDesc m_Description;
		// maybe rename to passid?
		const uint64_t m_uMaterialID; // 1 << m_MaterialIDs.GetAssociatedID()

		std::vector<VulkanRenderPass> m_SubPasses;

		// identifies the current pipeline
		size_t m_uPipelineHash = kUndefinedSizeT;
		vk::Pipeline m_ActivePipeline = nullptr;

		std::unordered_map<size_t, vk::DescriptorSetLayout> m_DescriptorSetLayouts;
		std::unordered_map<size_t, vk::PipelineLayout> m_PipelineLayouts;

		// pipeline description hash -> pipeline
		std::unordered_map<size_t, vk::Pipeline> m_Pipelines;

		vk::PipelineCache m_PipelineCache = nullptr;

		// maps renderpass name to unique id (only main passes, subpasses are ignored)
		static hlx::UniqueAssociationID<std::wstring, uint64_t> m_MaterialIDs;
	};

	inline uint64_t VulkanRenderPass::GetMaterialID() const	{ return m_uMaterialID;	}

} // Tracy

#endif // !TRACY_VULKANRENDERPASS_H
