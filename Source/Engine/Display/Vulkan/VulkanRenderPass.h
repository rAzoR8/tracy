#ifndef TRACY_VULKANRENDERPASS_H
#define TRACY_VULKANRENDERPASS_H

#include "IShaderFactoryConsumer.h"
#include "..\RenderPassDescription.h"
#include "VulkanBuffer.h"
#include "Datastructures\BufferSource.h"
#include "VulkanTexture.h"
#include "MathTypes.h"

namespace Tracy
{
	// forward decl
	class Camera;
	class RenderObject;
	//class Texture;
	//class GPUBuffer;
	class ImageSource;
	class BufferSource;

	class VulkanRenderPass : public IShaderFactoryConsumer
	{
		friend class VulkanRenderGraph;
	public:
#pragma region types
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
		
		// maybe put this into a different header
		struct Framebuffer
		{
			Framebuffer();

			struct Attachment
			{
				std::string sName;
				EAttachmentType kType = kAttachmentType_Color;
				EAttachmentSourceType kSource = kAttachmentSourceType_Backbuffer;
				VulkanTexture Texture;
			};

			void Reset();

			uint3_t vRTDimensions; // width height layers
			BufferSource DimensionSource; // stores rendertarget info for shader access

			std::vector<Attachment> Attachments;
			std::vector<vk::ClearValue> ClearValues;
		};
#pragma endregion

		VulkanRenderPass(VulkanRenderGraph& _Graph, VulkanRenderPass* _pParent, const RenderPassDesc& _Desc, const uint32_t _uPassIndex, const THandle _hDevice = 0);
		virtual ~VulkanRenderPass();

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
#pragma region internal_types
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
			Binding(const VariableInfo& _Var, const THandle _hDevice);
			~Binding();

			void Set(const Texture& _Texture);

			// return true if data changed
			bool Set(const void* _pData, const size_t _uSize);

		//private:
			VulkanBuffer StagingBuffer;
			VulkanBuffer GPUBuffer;

			vk::DescriptorImageInfo ImageInfo;
			uint64_t uImageId = HUNDEFINED64;
			vk::DescriptorBufferInfo BufferInfo; // GPU buffer
			uint32_t uBufferHash = HUNDEFINED32;
			uint64_t uHash = HUNDEFINED64;

			const uint64_t uNameHash;
			const VariableInfo Var;
			const vk::DescriptorType kType;
		};

		struct DescriptorSetContainer
		{
			DescriptorSetContainer(const vk::DescriptorSetLayout& _hLayout) : kLayout(_hLayout) {}
			const vk::DescriptorSetLayout kLayout;

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

		struct MappedSampler
		{
			uint64_t uDescHash;
			vk::Sampler hSampler;
		};

#pragma endregion

		void OnFactoryLoaded() final;
		void OnFactoryUnloaded() final;

		void AddDependency(const Dependence& _Dependency);

		// prepares command buffer & dynamic state for recording
		bool BeginCommandbuffer(const VulkanTexture& _CurrentBackbuffer, const uint32_t  _uIndex);
		void EndCommandbuffer();

		void NextSubPass();
		
		// called before draw or after shader has been selected
		vk::Pipeline ActivatePipeline(const PipelineDesc& _Desc);
		const bool ActivatePipelineLayout(
			const std::array<TVarSet, kMaxDescriptorSets>& _Sets,
			const int32_t _uLastUsedSet,
			vk::PipelineLayout& _OutPipeline,
			uint64_t& _uOutHash,
			const PushConstantFactory* _pPushConstants = nullptr);

		bool LoadPipelineCache(const std::wstring& _sPath);
		bool StorePipelineCache(const std::wstring& _sPath);

		// called from begin commandbuffer
		bool CreateFramebuffer(const VulkanTexture& _CurrentBackbuffer, const uint32_t  _uIndex);
		bool CreateRenderPass();

		void ResetFramebuffer();
		void ResetRenderPass();

		const vk::CommandBuffer& GetCommandBuffer() const;

		void ResetMappings();

		// find binding in current descriptor sets
		bool FindBinding(const uint64_t& _uNameHash, InputMapping& _OutMapping) const;

		void DigestImages(const ImageSource& Src);
		void DigestBuffer(const BufferSource& Src);

		void PipelineBarrier();

	private:
		VulkanRenderGraph& m_RenderGraph;
		VulkanRenderPass* m_pParent = nullptr;
		
		RenderPassDesc m_Description;
		// index relative to parent pass or rendergraph (index into vector)
		const uint32_t m_uPassIndex; 

		// callbacks
		IOnPerObject* m_pPerObjectCallback = nullptr;
		IOnPerCamera* m_pPerCameraCallback = nullptr;
		IOnChangePipeline* m_pOnChangePipeline = nullptr;

		std::vector<VulkanRenderPass> m_SubPasses;
		std::vector<Dependence> m_Dependencies;

		std::vector<vk::MemoryBarrier> m_MemoryBarriers;
		std::vector<vk::BufferMemoryBarrier> m_BufferBarriers;
		std::vector<vk::ImageMemoryBarrier> m_ImageBarriers;

		vk::RenderPassBeginInfo m_BeginInfo;

		vk::RenderPass m_hRenderPass = nullptr;
		Framebuffer m_Framebuffer;

		struct FramebufferInstance
		{
			vk::Framebuffer hBuffer = nullptr;
			uint64_t uIdentifier = kUndefinedSizeT;
		};

		std::vector<FramebufferInstance> m_VkFramebuffers;
		vk::Framebuffer m_hFrameBuffer;
		
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
		vk::PipelineCache m_hPipelineCache = nullptr;
		
		// desc hash -> sampler
		std::unordered_map<uint64_t, vk::Sampler> m_Samplers;

		// name hash -> sampler
		std::unordered_map<uint64_t, MappedSampler> m_MappedSamplers;

		// todo: make a ringbuffer of commanbuffers that can be pre recorded with static objects
		// and replayed when the are visible (again)
		vk::CommandBuffer m_hCommandBuffer = nullptr;
	};

	inline uint32_t VulkanRenderPass::GetPassIndex() const{	return m_uPassIndex;}

	inline uint64_t VulkanRenderPass::GetMaterialID() const	{ return 1ull << m_uPassIndex;}

	inline std::vector<VulkanRenderPass>& VulkanRenderPass::GetSubPasses()
	{
		return m_SubPasses;
	}

	inline const vk::CommandBuffer& Tracy::VulkanRenderPass::GetCommandBuffer() const
	{
		return m_hCommandBuffer;
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
