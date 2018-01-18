#include "VulkanRenderPass.h"
#include "FileStream.h"
#include "VulkanTypeConversion.h"
#include "Display\Camera.h"
#include "Display\RenderObject.h"
#include "VulkanTexture.h"
#include "VulkanBuffer.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

VulkanRenderPass::VulkanRenderPass(VulkanRenderPass* _pParent, const RenderPassDesc& _Desc, const uint32_t _uPassIndex, const THandle _hDevice) :
	IShaderFactoryConsumer(_Desc.sLibName, _hDevice),
	m_Description(_Desc),
	m_uPassIndex(_uPassIndex),
	m_pParent(_pParent)
{
	for (const RenderPassDesc& SubPass : m_Description.SubPasses)
	{
		m_SubPasses.emplace_back(this, SubPass, static_cast<uint32_t>(m_SubPasses.size()), _hDevice);
	}
}
//---------------------------------------------------------------------------------------------------

VulkanRenderPass::~VulkanRenderPass()
{
	Uninitialize();
}
//---------------------------------------------------------------------------------------------------

bool VulkanRenderPass::Initialize()
{
	if (m_pParent != nullptr && m_Description.SubPasses.empty() != false)
	{
		HERROR("SubPasses can not have sub passes (%s)", m_Description.sPassName.c_str());
		return false;
	}

	if (HasValidPlugin() == false)
		return false;

	if (LoadPipelineCache(m_Description.sPassName + L"_pipeline.cache") == false)
		return false;

	auto InitPipeline = [&](const PipelineDesc& _Pipeline) -> bool
	{
		// load the shader
		for (const PipelineDesc::ShaderDesc& Shader : _Pipeline.Shaders)
		{
			SelectShader(Shader.Identifier);
		}

		// create pipeline but dont bind to commandbuffer
		return ActivatePipeline(_Pipeline).operator bool();
	};

	// create default pipelines
	for (const PipelineDesc& Pipeline : m_Description.DefaultPipelines)
	{
		m_ActiveShaders.fill(nullptr); // clear previous pipeline (todo: create function that clears all other states too)

		if (InitPipeline(Pipeline) == false)
			return false;
	}

	// set default pipeline
	if (m_Description.DefaultPipelines.size() > 1)
	{
		InitPipeline(m_Description.DefaultPipelines.front());
	}

	for (VulkanRenderPass& SubPass : m_SubPasses)
	{
		if (SubPass.Initialize() == false)
			return false;
	}

	if (m_pParent != nullptr) // subpass
	{
		// take parent command buffer
		m_CommandBuffer = m_pParent->m_CommandBuffer;
		return m_CommandBuffer;
	}
	else
	{
		// create command buffer
		return m_Device.CreateCommandBuffers(vk::QueueFlagBits::eGraphics, vk::CommandPoolCreateFlagBits::eResetCommandBuffer, vk::CommandBufferLevel::eSecondary, &m_CommandBuffer);
	}
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::Uninitialize()
{
	// todo: wait for commandbuffer to finish processing
	if (m_pParent == nullptr)
	{
		m_Device.DestroyCommandBuffers(vk::QueueFlagBits::eGraphics, vk::CommandPoolCreateFlagBits::eResetCommandBuffer, &m_CommandBuffer);
	}

	for (VulkanRenderPass& SubPass : m_SubPasses)
	{
		SubPass.Uninitialize();
	}

	for (auto& kv : m_Samplers)
	{
		m_Device.DestroySampler(kv.second);
	}
	m_Samplers.clear();
	m_MappedSamplers.clear();

	for (auto& kv : m_DescriptorSets)
	{
		m_Device.destroyDescriptorSetLayout(kv.second.hLayout);
	}
	m_DescriptorSets.clear();

	StorePipelineCache(m_Description.sPassName + L"_pipeline.cache");
	m_Device.destroyPipelineCache(m_PipelineCache);
	m_PipelineCache = nullptr;

	for (auto& kv : m_PipelineLayouts)
	{
		m_Device.destroyPipelineLayout(kv.second);
	}
	m_PipelineLayouts.clear();

	for (auto& kv : m_Pipelines)
	{
		m_Device.destroyPipeline(kv.second);
	}
	m_Pipelines.clear();

	m_uPipelineHash = kUndefinedSizeT;
	m_ActivePipeline = nullptr;
	m_BasePipeline = nullptr;
}

//---------------------------------------------------------------------------------------------------

bool VulkanRenderPass::Record(const Camera& _Camera)
{
	// TODO: wait for previous passes to finish work on dependencies

	for (auto& kv : m_DescriptorSets)
	{
		DescriptorSetContainer& Container = kv.second;
		//m_Device.FreeDescriptorSets(Container.Sets);
		//Container.Sets.resize(0);
		Container.uNextFree = 0u;
		Container.UsedSets.clear();
	}

	// Upate pipeline
	{
		if (m_pOnChangePipeline != nullptr)
		{
			m_pOnChangePipeline->OnChangePipeline(*this, m_ActivePipelineDesc);
		}

		if (ActivatePipeline(m_ActivePipelineDesc).operator bool() == false)
			return false;

		ResetMappings();

		// TODO: get ViewportState from pipleine desc m_ActivePipelineDesc
		m_CommandBuffer.setViewport(0, m_ViewportState.Viewports);
		m_CommandBuffer.setScissor(0, m_ViewportState.Scissors);

		if (m_ActivePipelineDesc.kFillMode == kPolygonFillMode_Line)
		{
			m_CommandBuffer.setLineWidth(m_ActivePipelineDesc.fLineWidth);
		}

		if (m_ActivePipelineDesc.bDepthBiasEnabled)
		{
			m_CommandBuffer.setDepthBias(
				m_ActivePipelineDesc.fDepthBiasConstFactor,
				m_ActivePipelineDesc.fDepthBiasClamp,
				m_ActivePipelineDesc.fDepthBiasSlopeFactor);
		}

		if (m_ActivePipelineDesc.DepthStencilState.bStencilTestEnabled)
		{
			m_CommandBuffer.setStencilReference(vk::StencilFaceFlagBits::eFront, m_ActivePipelineDesc.DepthStencilState.uStencilReference);
			//m_CommandBuffer.setStencilCompareMask()
			//m_CommandBuffer.setStencilWriteMask()
		}
	}
	
	// set camera sources
	DigestBuffer(_Camera);

	if (m_pPerCameraCallback != nullptr)
	{
		m_pPerCameraCallback->OnPerCamera(*this, _Camera);
	}

	for (RenderObject* pObj : _Camera.GetObjects())
	{
		const RenderNode& Node = pObj->GetNode();

		if (Node.Material)
		{
			const MaterialRefEntry& Mat = Node.Material.Get();
			bool bShaderChanged = false;

			for (const ShaderID& id : Mat.Shaders)
			{
				if (id.Valid())
				{
					bShaderChanged |= SelectShader(id); // todo: userdata
				}
			}

			// check if shader changed and update the pipeline
			if (bShaderChanged && ActivatePipeline(m_ActivePipelineDesc))
			{
				ResetMappings();

				// camera needs to be remapped
				DigestBuffer(_Camera);

				m_CommandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, m_ActivePipeline);
			}

			for (const BufferSource* pSrc : pObj->GetBufferSources())
			{
				if (pSrc != nullptr)
				{
					DigestBuffer(*pSrc);
				}
			}

			DigestBuffer(Mat.Values); // material values
			DigestImages(Mat.Images); // textures

			// bind descriptor sets
			{
				std::vector<vk::WriteDescriptorSet> Writes;
				std::vector<vk::DescriptorSet> DescriporSets;

				uint32_t uFirstSet = UINT32_MAX;
				for (DescriptorSetContainer* pSet : m_ActiveDescriptorSets)
				{
					if (pSet->Update(m_Device))
					{
						pSet->AddDescriptorWrites(Writes);
					}

					DescriporSets.push_back(pSet->hSet);
					uFirstSet = std::min(uFirstSet, pSet->uSlot);
				}

				if (Writes.empty() == false)
				{
					VKDevice().updateDescriptorSets(Writes, {});				
				}

				// TODO: fill for dynamic uniforms and storage buffers
				std::vector<uint32_t> DynamicOffsets;

				if (m_ActiveDescriptorSets.empty() == false)
				{
					m_CommandBuffer.bindDescriptorSets(
						vk::PipelineBindPoint::eGraphics,
						m_ActivePipelineLayout,
						uFirstSet,
						DescriporSets,
						DynamicOffsets);

				} // else?
			}
		}

		if (m_pPerObjectCallback != nullptr)
		{
			m_pPerObjectCallback->OnPerObject(*this, pObj);
		}

		// set vertex & index buffer
		const Mesh& mesh = Node.Mesh;
		const GPUBuffer& vertexBuffer = mesh.GetVertexBuffer();
		const GPUBuffer& indexBuffer = mesh.GetIndexBuffer();

		// currently we only support one vertex / index stream and default them to binding 0
		switch (mesh.GetDrawMode())
		{
		case kDrawMode_VertexCount:
		{
			m_CommandBuffer.draw(mesh.GetVertexCount(), 0u, 0u, 0u);
		}
		break;
		case kDrawMode_VertexData:
		{
			if (vertexBuffer)
			{
				vk::DeviceSize offset = mesh.GetVertexOffset();
				const auto& Entry = VKBuffer(vertexBuffer);
				m_CommandBuffer.bindVertexBuffers(0u, 1u, &Entry.hBuffer, &offset);
				m_CommandBuffer.draw(mesh.GetVertexCount(), mesh.GetInstanceCount(), mesh.GetFirstVertex(), mesh.GetFirstInstance());
			}
		}
		break;
		case kDrawMode_IndexData:
		{
			if (vertexBuffer && indexBuffer)
			{
				vk::DeviceSize vertOffset = mesh.GetVertexOffset();
				const auto& vertEntry = VKBuffer(vertexBuffer);

				vk::DeviceSize indexOffset = mesh.GetIndexOffset();
				const auto& indexEntry = VKBuffer(indexBuffer);

				m_CommandBuffer.bindVertexBuffers(0u, 1u, &vertEntry.hBuffer, &vertOffset);
				m_CommandBuffer.bindIndexBuffer(indexEntry.hBuffer, indexOffset, GetIndexType(mesh.GetIndexType()));
				m_CommandBuffer.drawIndexed(mesh.GetIndexCount(), mesh.GetInstanceCount(), mesh.GetFirstIndex(), mesh.GetVertexOffset(), mesh.GetFirstInstance());
			}
		}
		break;
		default:
			break;
		}
	}

	return true;
}

//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::OnFactoryLoaded()
{
	Uninitialize();
	Initialize();
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::OnFactoryUnloaded()
{
	Uninitialize();
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::AddDependency(const Dependence& _Dependency)
{
	m_Dependencies.push_back(_Dependency);
}
//---------------------------------------------------------------------------------------------------
// prepares command buffer & dynamic state for recording
// called for each batch of objects that use a different shader
bool VulkanRenderPass::BeginPass()
{
	//vk::ClearValue clearValues[2];
	//clearValues[0].color = { { 0.1f, 0.1f, 0.1f, 1.0f } };
	//clearValues[1].depthStencil = { 1.0f, 0 };

	//vk::RenderPassBeginInfo renderPassBeginInfo{};
	//renderPassBeginInfo.renderPass = renderPass;
	//renderPassBeginInfo.renderArea.offset.x = 0;
	//renderPassBeginInfo.renderArea.offset.y = 0;
	//renderPassBeginInfo.renderArea.extent.width = width;
	//renderPassBeginInfo.renderArea.extent.height = height;
	//renderPassBeginInfo.clearValueCount = 2;
	//renderPassBeginInfo.pClearValues = clearValues;
	//renderPassBeginInfo.framebuffer = framebuffer;

	vk::CommandBufferInheritanceInfo BufferInfo{};

	BufferInfo.occlusionQueryEnable = VK_FALSE;
	//PassInfo.renderPass = m_Renderpass;
	//PassInfo.framebuffer = m_FrameBuffer;

	BufferInfo.subpass = m_pParent != nullptr ? m_uPassIndex : 0;

	vk::CommandBufferBeginInfo BeginInfo{};
	BeginInfo.flags = vk::CommandBufferUsageFlagBits::eRenderPassContinue;
	BeginInfo.pInheritanceInfo = &BufferInfo;

	//m_CommandBuffer.reset(0) //vk::CommandBufferResetFlagBits::eReleaseResources
	if (LogVKErrorBool(m_CommandBuffer.begin(&BeginInfo)) == false) // implicitly resets cmd buffer
		return false;
	
	//vk::RenderPassBeginInfo RenderPassInfo;
	//m_CommandBuffer.beginRenderPass()
	// first recorded cmd should be the PipelineBarriers for all m_Dependencies elements
	// vk::CmdPipelineBarrier

	return true;
}
//---------------------------------------------------------------------------------------------------
bool VulkanRenderPass::EndPass()
{
	m_CommandBuffer.endRenderPass();
	m_CommandBuffer.end();

	return true;
}
//---------------------------------------------------------------------------------------------------

bool VulkanRenderPass::BeginSubPass()
{
	HASSERT(m_pParent != nullptr, "Pass %s is not a SubPass", m_Description.sPassName);

	//VK_SUBPASS_CONTENTS_INLINE
	// specifies that the contents of the subpass will be recorded inline in the primary command buffer, and secondary command buffers must not be executed within the subpass.

	//VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS
	// specifies that the contents are recorded in secondary command buffers that will be called from the primary command buffer, and vkCmdExecuteCommands is the only valid command on the command buffer until vkCmdNextSubpass or vkCmdEndRenderPass.

	m_CommandBuffer.nextSubpass(vk::SubpassContents::eSecondaryCommandBuffers);

	return true;
}
//---------------------------------------------------------------------------------------------------

bool VulkanRenderPass::EndSubPass()
{
	return false;
}
//---------------------------------------------------------------------------------------------------
vk::Pipeline VulkanRenderPass::ActivatePipeline(const PipelineDesc& _Desc)
{
	hlx::Hasher uHash = 0u; // needs to differ from kUndefinedSizeT

	vk::GraphicsPipelineCreateInfo PipelineInfo{};
	PipelineInfo.basePipelineIndex = -1;

	// this is going to be the base pipeline, allow derivatives from this one
	if (!m_BasePipeline && _Desc.bBasePipeline)
	{
		PipelineInfo.flags |= vk::PipelineCreateFlagBits::eAllowDerivatives;
	}

	//---------------------------------------------------------------------------------------------------
	// SHADER STAGES
	//---------------------------------------------------------------------------------------------------

	std::vector<vk::PipelineShaderStageCreateInfo> ShaderStages;
	std::array<TVarSet, kMaxDescriptorSets> DescriptorSets;
	uint32_t uLastDescriptorSet = 0u;

	// load active shaders set by SelectShader function
	for (const CompiledShader* pShader : m_ActiveShaders)
	{
		if (pShader != nullptr)
		{
			ShaderStages.push_back(pShader->StageCreateInfo);
			uHash += pShader->uIDHash;
			uHash += pShader->uSpecConstHash;

			uLastDescriptorSet = std::max(uLastDescriptorSet, SortIntoDescriptorSets(pShader->Code, DescriptorSets));
		}
	}

	PipelineInfo.pStages = ShaderStages.data();
	PipelineInfo.stageCount = static_cast<uint32_t>(ShaderStages.size());

	//---------------------------------------------------------------------------------------------------
	// IMMUTABLE SAMPLERS
	//---------------------------------------------------------------------------------------------------

	for (const PipelineDesc::MappedSampler& Sampler : _Desc.Samplers)
	{
		const uint64_t uDescHash = hlx::Hash(Sampler.Desc);
		auto it = m_Samplers.find(uDescHash);

		vk::Sampler vkSampler{};
		if (it != m_Samplers.end()) 
		{
			vkSampler = it->second;
		}
		else
		{
			if (m_Device.CreateSampler(Sampler.Desc, vkSampler) == false)
			{
				return nullptr;
			}
			m_Samplers.insert({ uDescHash, vkSampler });
		}

		MappedSampler mSamp;
		mSamp.uDescHash = uDescHash;
		mSamp.hSampler = vkSampler;

		const uint64_t uNameHash = hlx::Hash(Sampler.sName);
		m_MappedSamplers.insert_or_assign(uNameHash, mSamp);
	}

	//---------------------------------------------------------------------------------------------------
	// PIPELINE LAYOUT
	//---------------------------------------------------------------------------------------------------

	// TODO: pass pushconst factory
	uint64_t uPipelineLayoutHash = 0u;
	if (ActivatePipelineLayout(DescriptorSets, uLastDescriptorSet, PipelineInfo.layout, uPipelineLayoutHash, nullptr) == false)
	{
		return nullptr;
	}

	//---------------------------------------------------------------------------------------------------
	// VERTEX LAYOUT
	//---------------------------------------------------------------------------------------------------

	const CompiledShader* pVertexShader = m_ActiveShaders[kShaderType_Vertex];

	VertexLayoutFactory VLayout;
	vk::PipelineVertexInputStateCreateInfo VertexInputState{};

	if (pVertexShader != nullptr)
	{
		VertexInputState = VLayout.GetVertexLayout(pVertexShader->Code.GetVariables());
		PipelineInfo.pVertexInputState = &VertexInputState;
		uHash += VLayout.ComputeHash();
	}

	//---------------------------------------------------------------------------------------------------
	// IA STAGE
	//---------------------------------------------------------------------------------------------------

	vk::PipelineInputAssemblyStateCreateInfo IAInfo{};
	IAInfo.primitiveRestartEnable = VK_FALSE; // not supported atm
	IAInfo.topology = GetPrimitiveTopology(_Desc.kPrimitiveTopology);
	PipelineInfo.pInputAssemblyState = &IAInfo;

	uHash << IAInfo.primitiveRestartEnable << IAInfo.topology;

	// dont set Viewport here, use Dynamic state instead: vkCmdSetViewport
	// this allows us the resize the swapchain without recreating the pipeline
	//https://www.khronos.org/registry/vulkan/specs/1.0-wsi_extensions/html/vkspec.html#vkCmdSetViewport

	//---------------------------------------------------------------------------------------------------
	// TESSELATION STAGE
	//---------------------------------------------------------------------------------------------------

	vk::PipelineTessellationStateCreateInfo TInfo{};

	if (m_ActiveShaders[kShaderType_TessellationControl] != nullptr && m_ActiveShaders[kShaderType_TessellationEvaluation] != nullptr) 
	{		
		//TODO: patchControlPoints must be greater than zero and less than or equal to VkPhysicalDeviceLimits::maxTessellationPatchSize
		//pNext must be NULL or a pointer to a valid instance of VkPipelineTessellationDomainOriginStateCreateInfoKHR
		
		HASSERT(_Desc.uPatchControlPointCount > 0u /*&& VkPhysicalDeviceLimits::maxTessellationPatchSize*/, "Invalid number of tesselation patch control points");
		TInfo.patchControlPoints = _Desc.uPatchControlPointCount;
		uHash << TInfo.patchControlPoints;

		PipelineInfo.pTessellationState = &TInfo;
	}

	//---------------------------------------------------------------------------------------------------
	// MULTISAMPLING STATE (unsupported/disabled atm)
	//---------------------------------------------------------------------------------------------------

	vk::PipelineMultisampleStateCreateInfo MSInfo{}; // TODO: add to uHash if MS is needed
	PipelineInfo.pMultisampleState = &MSInfo;

	//---------------------------------------------------------------------------------------------------
	// Rasterizer STAGE
	//---------------------------------------------------------------------------------------------------

	vk::PipelineRasterizationStateCreateInfo RInfo{};
	RInfo.rasterizerDiscardEnable = VK_FALSE; // not supported atm
	uHash << RInfo.rasterizerDiscardEnable;// pNext pointer musst be ignored in the hash 

	RInfo.depthClampEnable = VK_FALSE; // not supported atm
	uHash << RInfo.depthClampEnable;

	RInfo.cullMode = GetCullMode(_Desc.kCullMode);
	uHash << RInfo.cullMode;

	RInfo.polygonMode = GetPolygonMode(_Desc.kFillMode);
	uHash << RInfo.polygonMode;

	RInfo.frontFace = GetFrontFace(_Desc.kFrontFace);
	uHash << RInfo.frontFace;

	RInfo.depthBiasEnable = _Desc.bDepthBiasEnabled;
	uHash << RInfo.depthBiasEnable; // values are set on the command buffer

	PipelineInfo.pRasterizationState = &RInfo;

	//---------------------------------------------------------------------------------------------------
	// DepthStencil STATE
	//---------------------------------------------------------------------------------------------------

	vk::PipelineDepthStencilStateCreateInfo DSInfo = GetDepthStencilState(_Desc.DepthStencilState);
	uHash << DSInfo.depthTestEnable << DSInfo.depthWriteEnable << DSInfo.depthCompareOp << DSInfo.front << DSInfo.back;

	PipelineInfo.pDepthStencilState = &DSInfo;

	//---------------------------------------------------------------------------------------------------
	// DYNAMIC STATES
	//---------------------------------------------------------------------------------------------------

	vk::PipelineDynamicStateCreateInfo DynamicInfo{};

	vk::DynamicState DynamicStates[]{ 
		vk::DynamicState::eViewport,
		vk::DynamicState::eScissor,
		vk::DynamicState::eLineWidth,
		vk::DynamicState::eDepthBias,
		vk::DynamicState::eBlendConstants,
		vk::DynamicState::eDepthBounds,
		vk::DynamicState::eStencilCompareMask,
		vk::DynamicState::eStencilWriteMask,
		vk::DynamicState::eStencilReference
	};

	DynamicInfo.dynamicStateCount = static_cast<uint32_t>(GetArrayLength(DynamicStates));
	DynamicInfo.pDynamicStates = DynamicStates;
	PipelineInfo.pDynamicState = &DynamicInfo;

	//---------------------------------------------------------------------------------------------------
	
	// we want to derive from the base pipeline
	if (m_BasePipeline && _Desc.bBasePipeline == false) 
	{
		PipelineInfo.flags |= vk::PipelineCreateFlagBits::eDerivative;
		PipelineInfo.basePipelineHandle = m_BasePipeline;
	}

	if (uHash != m_uPipelineHash)
	{
		auto it = m_Pipelines.find(uHash);

		if (it != m_Pipelines.end())
		{
			m_ActivePipeline = it->second;
		}
		else
		{
			m_ActivePipelineDesc = _Desc;
			
			if (LogVKErrorBool(m_Device.createGraphicsPipelines(m_PipelineCache, 1u, &PipelineInfo, nullptr, &m_ActivePipeline)) == false)
			{
				return nullptr;
			}

			// this is the base pipeline now
			if (!m_BasePipeline && _Desc.bBasePipeline)
			{
				m_BasePipeline = m_ActivePipeline;
			}

			m_Pipelines.insert({ uHash, m_ActivePipeline });
		}

		m_uPipelineHash = uHash;
	}

	return m_ActivePipeline;
}
//---------------------------------------------------------------------------------------------------

const bool VulkanRenderPass::ActivatePipelineLayout(
	const std::array<TVarSet, kMaxDescriptorSets>& _Sets,
	const uint32_t _uLastSet,
	vk::PipelineLayout& _OutPipeline,
	uint64_t& _uOutHash,
	const PushConstantFactory* _pPushConstants)
{
	m_ActiveDescriptorSets.fill(nullptr); // reset
	
	std::vector<vk::DescriptorSetLayout> Layouts(_uLastSet); // _uLastSet + 1 ?
	hlx::Hasher uHash = 0u;

	for (uint32_t uSet = 0u; uSet < _uLastSet; ++uSet)
	{
		const TVarSet& Vars = _Sets[uSet];
		if (Vars.empty() == false)
		{
			hlx::Hasher uSetHash = 0u;
			std::vector<vk::DescriptorSetLayoutBinding> Bindings;

			// lookup and assign immutable samplers
			for (const VariableInfo& var : Vars)
			{
				// create binding form variable
				vk::DescriptorSetLayoutBinding Binding = CreateDescriptorSetLayoutBinding(var);
				uSetHash << Binding.binding << Binding.descriptorCount << Binding.descriptorType << (uint32_t)Binding.stageFlags;

				if (var.sName.empty())
				{
					HWARNING("Unnamed variable at binding %u", Binding.binding);
				}

				if (var.Type.IsSampler())
				{
					HASSERT(var.sName.empty() == false, "Unnamed sampler at binding %u", Binding.binding);
					uint64_t uNameHash = hlx::Hash(var.sName);
					auto it = m_MappedSamplers.find(uNameHash);
					
					HASSERT(it != m_MappedSamplers.end(), "No sampler found for %s", WCSTR(var.sName));
					if (it != m_MappedSamplers.end())
					{
						// add hash based on both name and desc
						const MappedSampler& Sampler = it->second;
						uSetHash += uNameHash;
						uSetHash += Sampler.uDescHash;
						Binding.pImmutableSamplers = &Sampler.hSampler;
					}
				}

				Bindings.push_back(Binding);
			}

			uHash += uSetHash;

			DescriptorSetContainer* pContainer = nullptr;
			
			auto it = m_DescriptorSets.find(uSetHash);
			if (it != m_DescriptorSets.end())
			{
				pContainer = &it->second;
			}
			else // create new set container & layout
			{
				// create layout
				vk::DescriptorSetLayoutCreateInfo LayoutInfo{};
				LayoutInfo.bindingCount = static_cast<uint32_t>(Bindings.size());
				LayoutInfo.pBindings = Bindings.data();

				//for()

				// add descriptor set container
				pContainer = &m_DescriptorSets.emplace(uSetHash, m_Device.createDescriptorSetLayout(LayoutInfo)).first->second;
				pContainer->uSlot = uSet;
				for (const VariableInfo& var : Vars)
				{
					pContainer->Bindings.push_back(var);
				}
			}

			Layouts[uSet] = pContainer->hLayout;
			m_ActiveDescriptorSets[uSet] = pContainer;
		}
		else // empty set (not sure if that works)
		{
			uHash << uSet;
		}
	}

	vk::PipelineLayoutCreateInfo Info{};
	if (_pPushConstants != nullptr)
	{
		Info.pPushConstantRanges = _pPushConstants->GetRanges();
		Info.pushConstantRangeCount = _pPushConstants->GetRangeCount();
		uHash += _pPushConstants->ComputeRangeHash();
	}

	// check if pipeline layout already exists
	auto it = m_PipelineLayouts.find(uHash);
	if (it != m_PipelineLayouts.end())
	{
		m_ActivePipelineLayout = it->second;
	}
	else
	{
		Info.pSetLayouts = Layouts.data();
		Info.setLayoutCount = static_cast<uint32_t>(Layouts.size());

		if (LogVKErrorBool(m_Device.createPipelineLayout(&Info, nullptr, &m_ActivePipelineLayout)) == false)
		{
			return false;
		}
	}

	_OutPipeline = m_ActivePipelineLayout;
	_uOutHash = uHash;

	return true;
}

//---------------------------------------------------------------------------------------------------

bool VulkanRenderPass::FindBinding(const uint64_t& _uNameHash, InputMapping& _OutMapping) const
{
	uint32_t uSet = 0u;
	for (DescriptorSetContainer* pSet : m_ActiveDescriptorSets)
	{
		if (uint32_t uBinding; uBinding = pSet->FindBinding(_uNameHash))
		{
			_OutMapping.uBindingIndex = uBinding;
			_OutMapping.uSet = uSet;
			return true;
		}
		++uSet;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::DigestImages(const ImageSource& Src)
{
	ResourceMapping& Mapping = m_ImageMappings[Src.GetID()];
	const std::vector<ImageSource::Image>& Images = Src.GetImages();

	if (Mapping.bInitialized == false)
	{
		Mapping.Resource.resize(0);
		uint32_t uSourceIndex = 0u;
		for (const ImageSource::Image& Img : Images)
		{
			InputMapping in;
			in.uSourceIndex = uSourceIndex;
			if (FindBinding(Img.uHash, in))
			{
				Mapping.Resource.push_back(in);
			}
		}

		Mapping.bInitialized = true;
	}

	// transfer images
	for (const InputMapping& Input : Mapping.Resource)
	{
		const ImageSource::Image& Source = Images[Input.uSourceIndex];
		m_ActiveDescriptorSets[Input.uSet]->Bindings[Input.uBindingIndex].Set(Source.Img);
	}
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::DigestBuffer(const BufferSource & Src)
{
	ResourceMapping& Mapping = m_BufferMappings[Src.GetID()];
	const std::vector<BufferSource::Var>& Vars = Src.GetVars();

	if (Mapping.bInitialized == false)
	{
		Mapping.Resource.resize(0);
		uint32_t uSourceIndex = 0u;
		for (const BufferSource::Var& Var : Vars)
		{
			InputMapping in;
			in.uSourceIndex = uSourceIndex;
			if (FindBinding(Var.uHash, in))
			{
				Mapping.Resource.push_back(in);
			}
		}

		Mapping.bInitialized = true;
	}

	// transfer images
	for (const InputMapping& Input : Mapping.Resource)
	{
		const BufferSource::Var& Source = Vars[Input.uSourceIndex];

		// todo: create buffer etc
		//m_ActiveDescriptorSets[Input.uSet]->Bindings[Input.uBindingIndex].Set()
	}
}
//---------------------------------------------------------------------------------------------------

bool VulkanRenderPass::LoadPipelineCache(const std::wstring& _sPath)
{		
	if (!m_PipelineCache)
	{
		hlx::fbytestream stream(_sPath, std::ios_base::in);
		hlx::bytes buffer;

		vk::PipelineCacheCreateInfo Info{};

		if (stream.is_open())
		{
			stream.getAll(buffer);

			Info.initialDataSize = buffer.size();
			Info.pInitialData = buffer.data();

			stream.close();
		}
		else
		{
			HERROR("Failed to load file %s", _sPath.c_str());
		}

		return LogVKErrorBool(m_Device.createPipelineCache(&Info, nullptr, &m_PipelineCache));
	}
	else
	{
		HERROR("PipelineCache has already been loaded");
	}

	return true;
}
//---------------------------------------------------------------------------------------------------

bool VulkanRenderPass::StorePipelineCache(const std::wstring& _sPath)
{
	bool bSuccess = false;

	if (m_PipelineCache)
	{
		hlx::fbytestream stream(_sPath, std::ios_base::out);

		if (stream.is_open())
		{
			size_t uSize = 0u;
			
			if (LogVKErrorBool(m_Device.getPipelineCacheData(m_PipelineCache, &uSize, nullptr)) && uSize > 0)
			{
				hlx::bytes buffer(uSize);

				if (LogVKErrorBool(m_Device.getPipelineCacheData(m_PipelineCache, &uSize, &buffer.front())))
				{
					stream.put(buffer);
					bSuccess = true;
					HLOG("Stored pipeline cache %s [%u bytes]", m_Description.sPassName.c_str(), uSize);
				}
			}

			stream.close();
		}
		else
		{
			HERROR("Failed to open file %s", _sPath.c_str());
		}
	}

	return bSuccess;
}

//---------------------------------------------------------------------------------------------------
void VulkanRenderPass::ResetMappings()
{
	m_BufferMappings.resize(BufferSource::GetInstanceCount());
	m_ImageMappings.resize(ImageSource::GetInstanceCount());

	for (ResourceMapping& Mapping : m_BufferMappings)
	{
		Mapping.Reset();
	}
	for (ResourceMapping& Mapping : m_ImageMappings)
	{
		Mapping.Reset();
	}
}
//---------------------------------------------------------------------------------------------------
void VulkanRenderPass::Binding::Set(const Texture& _Texture)
{
	const VkTexData& Tex = VKTexture(_Texture);
	if (uImageId != _Texture.GetIdentifier())
	{
		uImageId = _Texture.GetIdentifier();
		Image.imageLayout = Tex.hLayout;
		Image.imageView = Tex.Views[kViewType_ShaderResource];
		//Image.sampler TODO: use immutable samplers in PSO object instead

		uHash = hlx::Hash(uImageId, Var.uBinding, kType);
	}
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::Binding::Set(const GPUBuffer& _Buffer)
{
	const VkBufferData& Buf = VKBuffer(_Buffer);
	if (uBufferId != _Buffer.GetIdentifier())
	{
		uBufferId = _Buffer.GetIdentifier();
		Buffer.buffer = Buf.hBuffer;
		//Buffer.offset = Var.uMemberOffset;
		//Buffer.range = Var.Type.GetSize();

		uHash = hlx::Hash(uBufferId, Var.uBinding, kType);
	}
}
//---------------------------------------------------------------------------------------------------

uint32_t VulkanRenderPass::DescriptorSetContainer::FindBinding(const uint64_t& _uNameHash) const
{
	const size_t length = Bindings.size();
	for (uint32_t i = 0; i < length; ++i)
	{
		if (Bindings[i].uNameHash == _uNameHash)
			return i;
	}
	return HUNDEFINED32;
}
//---------------------------------------------------------------------------------------------------

bool VulkanRenderPass::DescriptorSetContainer::Update(VulkanDevice & _Device)
{
	uint64_t uNewHash = 0u;
	for (const Binding& b : Bindings)
	{
		uNewHash = hlx::CombineHashes(uNewHash, b.uHash);
	}

	if (uHash != uNewHash)
	{
		uHash = uNewHash;

		auto it = UsedSets.find(uHash);

		if (it != UsedSets.end())
		{
			hSet = it->second;
		}
		else
		{
			if (uNextFree < FreeSets.size())
			{
				hSet = FreeSets[uNextFree++];
			}
			else // no more free sets
			{
				auto&& NewSets = _Device.AllocateDescriptorSets(hLayout, 32u);

				if (NewSets.empty() == false)
				{
					FreeSets.insert(FreeSets.end(), std::make_move_iterator(NewSets.begin()), std::make_move_iterator(NewSets.end()));
					hSet = FreeSets[uNextFree++];
				}
				else
				{
					hSet = nullptr;
				}
			}

			if (hSet)
			{
				UsedSets.insert({ uHash, hSet });
			}
		}

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::DescriptorSetContainer::AddDescriptorWrites(std::vector<vk::WriteDescriptorSet>& _OutWrites) const
{
	for (const Binding& bind : Bindings)
	{
		vk::WriteDescriptorSet& write = _OutWrites.emplace_back();
		write.descriptorCount = 1u;
		write.descriptorType = bind.kType;
		write.dstArrayElement = 0u; // no array support for now
		write.dstBinding = bind.Var.uBinding;
		write.dstSet = hSet;
		write.pBufferInfo = &bind.Buffer;
		write.pImageInfo = &bind.Image;
		write.pTexelBufferView = nullptr;
	}
}
//---------------------------------------------------------------------------------------------------
