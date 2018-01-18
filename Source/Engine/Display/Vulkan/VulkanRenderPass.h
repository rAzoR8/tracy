#ifndef TRACY_VULKANRENDERPASS_H
#define TRACY_VULKANRENDERPASS_H

#include "IShaderFactoryConsumer.h"
#include "..\RenderPassDescription.h"

namespace Tracy
{
	// forward decl
	class Camera;
	class RenderObject;
	class Texture;
	class GPUBuffer;
	class ImageSource;
	class BufferSource;

	class VulkanRenderPass : public IShaderFactoryConsumer
	{
		friend class VulkanRenderGraph;
	public:
#pragma region Types
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
#pragma endregion

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
		struct InputMapping
		{
			uint32_t uSourceIndex;
			uint32_t uSet;
			uint32_t uBindingIndex;
		};

		struct ResourceMapping
		{
			inline void Reset() { bInitialized = false; Resource.resize(0); }
			std::vector<InputMapping> Resource; // index into source
			bool bInitialized = false;
		};

		struct Binding
		{
			Binding(const VariableInfo& _Var) : 
				Var(_Var), kType(GetDescriptorType(_Var)), uNameHash(hlx::Hash(_Var.sName)){}

			void Set(const Texture& _Texture);
			void Set(const GPUBuffer& _Buffer);

		//private:
			vk::DescriptorImageInfo Image;
			uint64_t uImageId = HUNDEFINED64;
			vk::DescriptorBufferInfo Buffer;
			uint64_t uBufferId = HUNDEFINED64;
			uint64_t uHash = HUNDEFINED64;

			const uint64_t uNameHash;
			const VariableInfo Var;
			const vk::DescriptorType kType;
		};

		struct DescriptorSetContainer
		{
			DescriptorSetContainer(const vk::DescriptorSetLayout& _hLayout) : hLayout(_hLayout) {}
			const vk::DescriptorSetLayout hLayout;

			std::vector<vk::DescriptorSet> FreeSets;
			std::unordered_map<uint64_t, vk::DescriptorSet> UsedSets;
			uint32_t uNextFree = 0u;
			uint32_t uSlot = 0u;
			std::vector<Binding> Bindings;
			vk::DescriptorSet hSet;
			uint64_t uHash = 0u;

			// returns index
			uint32_t FindBinding(const uint64_t& _uNameHash) const;
			bool Update(VulkanDevice& _Device);
			void AddDescriptorWrites(std::vector<vk::WriteDescriptorSet>& _OutWrites) const;
		};

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
		const bool ActivatePipelineLayout(
			const std::array<TVarSet, kMaxDescriptorSets>& _Sets,
			const uint32_t uLastSet,
			vk::PipelineLayout& _OutPipeline,
			uint64_t& _uOutHash,
			const PushConstantFactory* _pPushConstants = nullptr);

		bool LoadPipelineCache(const std::wstring& _sPath);
		bool StorePipelineCache(const std::wstring& _sPath);

		const vk::CommandBuffer& GetCommandBuffer() const;

		void ResetMappings();

		// find binding in current descriptor sets
		bool FindBinding(const uint64_t& _uNameHash, InputMapping& _OutMapping) const;

		void DigestImages(const ImageSource& Src);
		void DigestBuffer(const BufferSource& Src);

	private:
		VulkanRenderPass* m_pParent = nullptr;
		
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

		std::vector<ResourceMapping> m_ImageMappings;
		std::vector<ResourceMapping> m_BufferMappings;

		// identifies the current pipeline
		uint64_t m_uPipelineHash = HUNDEFINED64;
		vk::Pipeline m_BasePipeline = nullptr;
		vk::Pipeline m_ActivePipeline = nullptr;
		vk::PipelineLayout m_ActivePipelineLayout = nullptr;
		PipelineDesc m_ActivePipelineDesc;

		std::unordered_map<uint64_t, DescriptorSetContainer> m_DescriptorSets;
		std::array<DescriptorSetContainer*, kMaxDescriptorSets> m_ActiveDescriptorSets;

		std::unordered_map<uint64_t, vk::PipelineLayout> m_PipelineLayouts;

		// pipeline description hash -> pipeline
		std::unordered_map<uint64_t, vk::Pipeline> m_Pipelines;
		vk::PipelineCache m_PipelineCache = nullptr;

		// desc hash -> sampler

		struct MappedSampler
		{
			uint64_t uDescHash;
			vk::Sampler hSampler;
		};

		std::unordered_map<uint64_t, vk::Sampler> m_Samplers;

		// name hash -> sampler
		std::unordered_map<uint64_t, MappedSampler> m_MappedSamplers;

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
