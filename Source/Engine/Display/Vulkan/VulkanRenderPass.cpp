#include "VulkanRenderPass.h"
#include "FileStream.h"
#include "VulkanTypeConversion.h"
#include "..\Camera.h"
#include "..\RenderObject.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

VulkanRenderPass::VulkanRenderPass(const RenderPassDesc& _Desc, const uint32_t _uPassIndex, const THandle _hDevice) :
	IShaderFactoryConsumer(_Desc.sLibName, _hDevice),
	m_Description(_Desc),
	m_uPassIndex(_uPassIndex)
{
	for (const RenderPassDesc& SubPass : m_Description.SubPasses)
	{
		m_SubPasses.emplace_back(SubPass, (uint32_t)m_SubPasses.size(), _hDevice);
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
	if (HasValidPlugin() == false)
		return false;

	if (LoadPipelineCache(m_Description.sPassName + L"_pipeline.cache") == false)
		return false;

	if (CreateDescriptorPool() == false)
		return false;

	auto InitPipeline = [&](const PipelineDesc& _Pipeline) -> bool
	{
		// load the shader
		for (const PipelineDesc::ShaderDesc& Shader : _Pipeline.Shaders)
		{
			SelectShader(Shader.Identifier, nullptr/*, Shader.UserData.data(), Shader.UserData.size()*/);
		}

		// create pipeline but dont bind to commandbuffer
		return CreatePipeline(_Pipeline).operator bool();
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

	// create command buffer
	return m_Device.CreateCommandBuffers(vk::QueueFlagBits::eGraphics, vk::CommandPoolCreateFlagBits::eResetCommandBuffer, vk::CommandBufferLevel::eSecondary, &m_CommandBuffer);
}
//---------------------------------------------------------------------------------------------------

void VulkanRenderPass::Uninitialize()
{
	// todo: wait for commandbuffer to finish processing
	m_Device.DestroyCommandBuffers(vk::QueueFlagBits::eGraphics, vk::CommandPoolCreateFlagBits::eResetCommandBuffer, &m_CommandBuffer);

	for (VulkanRenderPass& SubPass : m_SubPasses)
	{
		SubPass.Uninitialize();
	}

	StorePipelineCache(m_Description.sPassName + L"_pipeline.cache");
	m_Device.destroyPipelineCache(m_PipelineCache);
	m_PipelineCache = nullptr;

	m_Device.destroyDescriptorPool(m_DescriptorPool);
	m_DescriptorPool = nullptr;

	for (auto& kv : m_DescriptorSets)
	{
		DesciptorSet& Set = kv.second;
		m_Device.destroyDescriptorSetLayout(Set.Layout);
	}
	m_DescriptorSets.clear();	

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
	
	if (m_pOnChangePipeline != nullptr)
	{
		if (CreatePipeline(m_pOnChangePipeline->OnChangePipeline(*this)).operator bool() == false)
			return false;
	}

	struct VariableMapping
	{
		//vk::buffer
		//descriptorset & vars
		std::vector<uint32_t> Variables; // index into buffer source
		bool Initialized() { return bInitialized; }
		bool Valid() { return bValid; }

		bool bValid = false;
		bool bInitialized = false;
	};

	struct ImageMapping
	{
		std::vector<uint32_t> Images; // index into image source
		bool Initialized() { return bInitialized; }
		bool Valid() { return bValid; }

		bool bValid = false;
		bool bInitialized = false;
	};

	std::vector<VariableMapping> VarMappings(BufferSource::GetInstanceCount());
	std::vector<ImageMapping> ImageMappings(ImageSource::GetInstanceCount());

	// helper function
	auto DigestBuffer = [&](const BufferSource& Src)
	{
		VariableMapping& Mapping = VarMappings[Src.GetID()];

		if (Mapping.Initialized() == false)
		{
			// write indices of variables with names matching in descriptor set and buffer source into mapping Variables
		}

		if (Mapping.Valid())
		{
			const std::vector<BufferSource::Var>& Source = Src.GetVars();
			// transfer 
			for (const uint32_t& i : Mapping.Variables)
			{
				//Source[i].pData
			}
		}
	};

	auto DigestImages = [&](const ImageSource& Src)
	{
		ImageMapping& Mapping = ImageMappings[Src.GetID()];

		if (Mapping.Initialized() == false)
		{
		}

		if (Mapping.Valid())
		{
			const std::vector<ImageSource::Image>& Source = Src.GetImages();
			// transfer 
			for (const uint32_t& i : Mapping.Images)
			{
				//Source[i].Image
			}
		}
	};

	// set camera sources
	DigestBuffer(_Camera);

	if (m_pPerCameraCallback != nullptr)
	{
		m_pPerCameraCallback->OnPerCamera(*this, _Camera);
	}

	for (RenderObject* pObj : _Camera.GetObjects())
	{
		// TODO: check if material / shader changed and call SelectShader() & create pipeline	
		const RenderNode& Node = pObj->GetNode();

		if (Node.Material)
		{
			const MaterialRefEntry& Mat = Node.Material.Get();
			bool bShaderChanged = false;

			for (const ShaderID& id : Mat.Shaders)
			{
				if (id.Valid())
				{
					bShaderChanged |= SelectShader(id);
				}
			}

			if (bShaderChanged && CreatePipeline(m_ActivePipelineDesc))
			{
				m_CommandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, m_ActivePipeline);
			}

			DigestBuffer(Mat.Values); // material values
			DigestImages(Mat.Images); // textures
		}

		for (const BufferSource* pSrc : pObj->GetBufferSources()) 
		{			
			if (pSrc != nullptr)
			{
				DigestBuffer(*pSrc);
			}
		}

		// TODO: set vertex & index buffer

		if (m_pPerObjectCallback != nullptr)
		{
			m_pPerObjectCallback->OnPerObject(*this, pObj);
		}

		// TODO: record draw call
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
	vk::CommandBufferInheritanceInfo PassInfo{};

	PassInfo.occlusionQueryEnable = VK_FALSE;
	//PassInfo.renderPass = m_Renderpass;
	//PassInfo.framebuffer = m_FrameBuffer;

	PassInfo.subpass = m_Description.bSubPass ? m_uPassIndex : 0;

	vk::CommandBufferBeginInfo BeginInfo{};
	BeginInfo.flags = vk::CommandBufferUsageFlagBits::eRenderPassContinue;
	BeginInfo.pInheritanceInfo = &PassInfo;

	//m_CommandBuffer.reset(0) //vk::CommandBufferResetFlagBits::eReleaseResources
	if (LogVKErrorBool(m_CommandBuffer.begin(&BeginInfo)) == false) // implicitly resets cmd buffer
		return false;
	
	// ViewportState
	m_CommandBuffer.setViewport(0, m_ViewportState.Viewports);
	m_CommandBuffer.setScissor(0, m_ViewportState.Scissors);

	// first recorded cmd should be the PipelineBarriers for all m_Dependencies elements
	// vk::CmdPipelineBarrier

	return true;
}
//---------------------------------------------------------------------------------------------------
bool VulkanRenderPass::EndPass()
{
	m_CommandBuffer.end();

	return true;
}
//---------------------------------------------------------------------------------------------------
vk::Pipeline VulkanRenderPass::CreatePipeline(const PipelineDesc& _Desc)
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
	std::array<TVarSet, uMaxDescriptorSets> DescriptorSets;
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
	// PIPELINE LAYOUT
	//---------------------------------------------------------------------------------------------------

	// TODO: pass pushconst factory
	uHash += CreatePipelineLayout(DescriptorSets, uLastDescriptorSet, PipelineInfo.layout, nullptr);

	if (!PipelineInfo.layout)
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

	RInfo.depthBiasEnable = _Desc.fDepthBiasClamp != 0.f || _Desc.fDepthBiasConstFactor != 0.f || _Desc.fDepthBiasSlopeFactor;
	uHash << RInfo.depthBiasEnable;

	if (_Desc.kFillMode == kPolygonFillMode_Line)
	{
		RInfo.lineWidth = _Desc.fLineWidth;
		uHash << RInfo.lineWidth;
	}

	if (RInfo.depthBiasEnable)
	{
		RInfo.depthBiasConstantFactor = _Desc.fDepthBiasConstFactor;
		RInfo.depthBiasClamp = _Desc.fDepthBiasClamp;
		RInfo.depthBiasSlopeFactor = _Desc.fDepthBiasSlopeFactor;

		uHash << RInfo.depthBiasConstantFactor;
		uHash << RInfo.depthBiasClamp;
		uHash << RInfo.depthBiasSlopeFactor;
	}

	PipelineInfo.pRasterizationState = &RInfo;

	//---------------------------------------------------------------------------------------------------
	// DepthStencil STATE
	//---------------------------------------------------------------------------------------------------

	vk::PipelineDepthStencilStateCreateInfo DSInfo = GetDepthStencilState(_Desc.DepthStencilState);
	uHash << DSInfo.depthTestEnable << DSInfo.depthWriteEnable << DSInfo.depthCompareOp << DSInfo.front << DSInfo.back;

	PipelineInfo.pDepthStencilState = &DSInfo;

	// ...
	// TODO: fill out the other stuff

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

const size_t VulkanRenderPass::CreatePipelineLayout(const std::array<TVarSet, uMaxDescriptorSets>& _Sets, const uint32_t _uLastSet, vk::PipelineLayout& _OutPipeline, const PushConstantFactory* _pPushConstants)
{
	std::vector<vk::DescriptorSetLayout> Layouts(_uLastSet);
	std::vector<vk::DescriptorSetLayout> SetsToAllocate;
	std::vector<uint64_t> SetHashesToAllocate;

	hlx::Hasher uHash = 0u;

	for (uint32_t uSet = 0u; uSet < _uLastSet; ++uSet)
	{
		const TVarSet& Vars = _Sets[uSet];
		if (Vars.empty() == false)
		{
			std::vector<vk::DescriptorSetLayoutBinding> Bindings;
			const size_t uSetHash = CreateDescriptorSetLayoutBindings(Vars, Bindings);
			uHash += uSetHash;

			auto it = m_DescriptorSets.find(uSetHash);

			if (it != m_DescriptorSets.end())
			{
				Layouts[uSet] = it->second.Layout;
			}
			else // create new set
			{
				vk::DescriptorSetLayoutCreateInfo Info{};
				Info.bindingCount = static_cast<uint32_t>(Bindings.size());
				Info.pBindings = Bindings.data();

				DesciptorSet NewSet;
				NewSet.Layout = m_Device.createDescriptorSetLayout(Info);
				NewSet.Set = nullptr; // init later
				NewSet.Variables = Vars;

				m_DescriptorSets.insert({ uSetHash, NewSet });

				Layouts[uSet] = NewSet.Layout;

				// batch together all sets that need to be created
				SetsToAllocate.push_back(NewSet.Layout);
				SetHashesToAllocate.push_back(uSetHash);
			}
		}
		else
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

	// batch create sets
	if (SetsToAllocate.empty() == false)
	{
		vk::DescriptorSetAllocateInfo Info{};
		Info.descriptorPool = m_DescriptorPool;
		Info.descriptorSetCount = static_cast<uint32_t>(SetsToAllocate.size());
		Info.pSetLayouts = SetsToAllocate.data();

		std::vector<vk::DescriptorSet> NewSets(Info.descriptorSetCount); 

		// allocate batch in once call
		if (LogVKErrorBool(VKDevice().allocateDescriptorSets(&Info, NewSets.data())))
		{
			for (uint32_t i = 0; i < Info.descriptorSetCount; ++i)
			{
				auto it = m_DescriptorSets.find(SetHashesToAllocate[i]);
				if (it != m_DescriptorSets.end())
				{
					it->second.Set = NewSets[i]; // assign newly created set
				}
			}
		}
	}

	// check if pipeline layout already exists
	auto it = m_PipelineLayouts.find(uHash);
	if (it != m_PipelineLayouts.end())
	{
		_OutPipeline = it->second;
		return uHash;
	}

	Info.pSetLayouts = Layouts.data();
	Info.setLayoutCount = static_cast<uint32_t>(Layouts.size());

	LogVKError(m_Device.createPipelineLayout(&Info, nullptr, &_OutPipeline));

	return uHash;
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
bool VulkanRenderPass::CreateDescriptorPool()
{
	HASSERT(!m_DescriptorPool, "Descriptor pool already exists!");
	if (m_DescriptorPool)
		return false;

	vk::DescriptorPoolCreateInfo Info{};
	std::vector<vk::DescriptorPoolSize> PoolSizes;

	auto AddSize = [&PoolSizes](vk::DescriptorType kType, uint32_t uCount)
	{
		PoolSizes.push_back(vk::DescriptorPoolSize(kType, uCount));
	};

	AddSize(vk::DescriptorType::eCombinedImageSampler, 64u);
	AddSize(vk::DescriptorType::eInputAttachment, 8u);
	AddSize(vk::DescriptorType::eSampledImage, 64u);
	AddSize(vk::DescriptorType::eSampler, 64u);
	AddSize(vk::DescriptorType::eStorageBuffer, 64u);
	AddSize(vk::DescriptorType::eStorageBufferDynamic, 64u);
	AddSize(vk::DescriptorType::eStorageImage, 64u);
	AddSize(vk::DescriptorType::eStorageTexelBuffer, 64u);
	AddSize(vk::DescriptorType::eUniformBuffer, 64u);
	AddSize(vk::DescriptorType::eUniformBufferDynamic, 64u);
	AddSize(vk::DescriptorType::eUniformTexelBuffer, 64u);

	Info.maxSets = 512u; // donno what makes sense here
	Info.poolSizeCount = static_cast<uint32_t>(PoolSizes.size());
	Info.pPoolSizes = PoolSizes.data();

	return LogVKErrorBool(m_Device.createDescriptorPool(&Info, nullptr, &m_DescriptorPool));
}
//---------------------------------------------------------------------------------------------------
