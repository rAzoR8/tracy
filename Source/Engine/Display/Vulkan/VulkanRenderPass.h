#ifndef TRACY_VULKANRENDERPASS_H
#define TRACY_VULKANRENDERPASS_H

#include "IShaderFactoryConsumer.h"
#include "..\RenderPassDescription.h"

namespace Tracy
{
	// forward decl
	class Camera;
	class RenderObject;

	class VulkanRenderPass : public IShaderFactoryConsumer
	{
		friend class VulkanRenderGraph;
	public:
		struct IOnPerObject
		{
			virtual bool OnPerObject(VulkanRenderPass& _Pass, RenderObject* _pObject) = 0;
		};

		struct IOnPerCamera
		{
			virtual bool OnPerCamera(VulkanRenderPass& _Pass, const Camera& _Camera) = 0;
		};

		// called before OnPerCamera
		struct IOnChangePipeline
		{
			virtual void OnChangePipeline(VulkanRenderPass& _Pass, PipelineDesc& _CurrentPipeline) = 0;
		};

		struct Dependence
		{
			VulkanRenderPass* pPrevPass;

			// TODO: pointer to resource or something cool
			std::vector<InputDependency::Resource> Resources;

			// add pipeline barriers etc
		};
		
		// TODO: abstract viewport into display types, add it to pipeline desc
		struct ViewportState
		{
			std::vector<vk::Viewport> Viewports;
			std::vector<vk::Rect2D> Scissors;
		};

		VulkanRenderPass(VulkanRenderPass* _pParent, const RenderPassDesc& _Desc, const uint32_t _uPassIndex, const THandle _hDevice = 0);
		~VulkanRenderPass();

		bool Initialize();
		void Uninitialize();

		// record settings and objects form this camera to the commandbuffer
		bool Record(const Camera& _Camera);

		uint32_t GetPassIndex() const;
		uint64_t GetMaterialID() const;

		std::vector<VulkanRenderPass>& GetSubPasses();
		const RenderPassDesc& GetDescription() const;

		void SetPerObjectCallback(IOnPerObject* _pCallback);
		void SetPerCameraCallback(IOnPerCamera* _pCallback);
		void SetChangePipelineCallback(IOnChangePipeline* _pCallback);

	private:
		void OnFactoryLoaded() final;
		void OnFactoryUnloaded() final;

		void AddDependency(const Dependence& _Dependency);

		// prepares command buffer & dynamic state for recording
		bool BeginPass();
		bool EndPass();

		bool BeginSubPass();
		bool EndSubPass();

		// called before draw or after shader has been selected
		vk::Pipeline ActivatePipeline(const PipelineDesc& _Desc);
		const size_t ActivatePipelineLayout(const std::array<TVarSet, uMaxDescriptorSets>& _Sets, const uint32_t uLastSet, vk::PipelineLayout& _OutPipeline, const PushConstantFactory* _pPushConstants = nullptr);

		bool LoadPipelineCache(const std::wstring& _sPath);
		bool StorePipelineCache(const std::wstring& _sPath);

		bool CreateDescriptorPool();

		const vk::CommandBuffer& GetCommandBuffer() const;

	private:
		VulkanRenderPass* m_pParent = nullptr;

		struct DesciptorSet
		{
			uint32_t uSlot = 0u;
			vk::DescriptorSetLayout Layout;
			vk::DescriptorSet Set;
			TVarSet Variables;

			// per variable ?
			//const VkDescriptorImageInfo*     pImageInfo;
			//const VkDescriptorBufferInfo*    pBufferInfo;
			//const VkBufferView*              pTexelBufferView;
		};

		RenderPassDesc m_Description;
		// index relative to parent pass or rendergraph (index into vector)
		const uint32_t m_uPassIndex; 

		// callbacks
		IOnPerObject* m_pPerObjectCallback = nullptr;
		IOnPerCamera* m_pPerCameraCallback = nullptr;
		IOnChangePipeline* m_pOnChangePipeline = nullptr;

		ViewportState m_ViewportState;

		std::vector<VulkanRenderPass> m_SubPasses;
		std::vector<Dependence> m_Dependencies;

		// identifies the current pipeline
		size_t m_uPipelineHash = kUndefinedSizeT;
		vk::Pipeline m_ActivePipeline = nullptr;
		vk::PipelineLayout m_ActivePipelineLayout = nullptr;
		PipelineDesc m_ActivePipelineDesc;

		std::vector<DesciptorSet*> m_ActiveDescriptorSets;
		vk::Pipeline m_BasePipeline = nullptr;

		// todo: vector<DesciptorSet> currentSets (active sets)
		std::unordered_map<size_t, DesciptorSet> m_DescriptorSets;

		vk::DescriptorPool m_DescriptorPool;

		std::unordered_map<size_t, vk::PipelineLayout> m_PipelineLayouts;

		// pipeline description hash -> pipeline
		std::unordered_map<size_t, vk::Pipeline> m_Pipelines;
		vk::PipelineCache m_PipelineCache = nullptr;

		// name hash -> sampler
		std::unordered_map<uint64_t, vk::Sampler> m_MappedSamplers;

		// todo: make a ringbuffer of commanbuffers that can be pre recorded with static objects
		// and replayed when the are visible (again)
		vk::CommandBuffer m_CommandBuffer;
	};

	inline uint32_t VulkanRenderPass::GetPassIndex() const{	return m_uPassIndex;}

	inline uint64_t VulkanRenderPass::GetMaterialID() const	{ return 1ull << m_uPassIndex;}

	inline std::vector<VulkanRenderPass>& VulkanRenderPass::GetSubPasses()
	{
		return m_SubPasses;
	}

	inline const vk::CommandBuffer& Tracy::VulkanRenderPass::GetCommandBuffer() const
	{
		return m_CommandBuffer;
	}

	inline const RenderPassDesc& VulkanRenderPass::GetDescription() const {return m_Description;	}

	inline void VulkanRenderPass::SetPerObjectCallback(IOnPerObject* _pCallback)
	{
		m_pPerObjectCallback = _pCallback;
	}

	inline void VulkanRenderPass::SetPerCameraCallback(IOnPerCamera* _pCallback)
	{
		m_pPerCameraCallback = _pCallback;
	}

	inline void VulkanRenderPass::SetChangePipelineCallback(IOnChangePipeline* _pCallback)
	{
		m_pOnChangePipeline = _pCallback;
	}

} // Tracy

#endif // !TRACY_VULKANRENDERPASS_H
