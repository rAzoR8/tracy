#ifndef TRACY_SPIRVINTEROP_H
#define TRACY_SPIRVINTEROP_H

// TODO: use <vulkan/vulkan.hpp> instead to be independant of our vulkan implementation
// maybe move this file to the SPIRVProject
#include "VulkanAPI.h"
#include "../../SPIRVGen/SPIRVModule.h"
#include "Logger.h"
#include "ByteStream.h"

namespace Tracy
{
	//---------------------------------------------------------------------------------------------------
	inline vk::ShaderStageFlagBits GetShaderStage(const SPIRVModule& _Module)
	{
		switch (_Module.GetExectionModel())
		{
		case spv::ExecutionModelVertex: return vk::ShaderStageFlagBits::eVertex;
		case spv::ExecutionModelTessellationControl: return vk::ShaderStageFlagBits::eTessellationControl;
		case spv::ExecutionModelTessellationEvaluation: return vk::ShaderStageFlagBits::eTessellationEvaluation;
		case spv::ExecutionModelGeometry: return vk::ShaderStageFlagBits::eGeometry;
		case spv::ExecutionModelFragment: return vk::ShaderStageFlagBits::eFragment;
		case spv::ExecutionModelGLCompute: return vk::ShaderStageFlagBits::eCompute;
		case spv::ExecutionModelKernel: return vk::ShaderStageFlagBits::eCompute;
		default:
			return vk::ShaderStageFlagBits::eAll;
		}
	}
	//---------------------------------------------------------------------------------------------------

	// Element of a descriptor set (input)
	inline void CreateDescriptorSetLayoutBinding(vk::DescriptorSetLayoutBinding& _Binding, const VariableInfo& _InputVar)
	{
		_Binding.binding = _InputVar.uBinding;
		_Binding.descriptorCount = _InputVar.Type.GetType() == spv::OpTypeArray ? _InputVar.Type.GetDimension() : 1u;
		// Missing: CombinedImageSampler
		switch (_InputVar.Type.GetType())
		{
		case spv::OpTypeSampler:
			_Binding.descriptorType = vk::DescriptorType::eSampler;
			break;
		case spv::OpTypeImage:
			switch (_InputVar.Type.GetDimension())
			{
			case spv::DimSubpassData:
				_Binding.descriptorType = vk::DescriptorType::eInputAttachment;
				break;
			case spv::DimBuffer:
				// TODO: texel buffers
				break;
			default: // dim1d 2d 3d etc
				switch (_InputVar.Type.GetTexSamplerAccess())
				{
				case kTexSamplerAccess_Runtime:
					_Binding.descriptorType = _InputVar.bTexSampled ? vk::DescriptorType::eSampledImage : vk::DescriptorType::eStorageImage;
					break;
				case kTexSamplerAccess_Sampled:
					_Binding.descriptorType = vk::DescriptorType::eSampledImage;
					break;
				case kTexSamplerAccess_Storage:
					_Binding.descriptorType = vk::DescriptorType::eStorageImage;
					break;
				}
				break;
			}
			break;
		case spv::OpTypeSampledImage:
			break; // skip
		default: // assume this is a buffer
			switch (_InputVar.kStorageClass)
			{
			case spv::StorageClassUniform:
			case spv::StorageClassUniformConstant:
				_Binding.descriptorType = vk::DescriptorType::eUniformBuffer;
				break;
			case spv::StorageClassStorageBuffer:
				_Binding.descriptorType = vk::DescriptorType::eStorageBuffer;
				break;
			default:
				HFATAL("Unsupported storage class");
				break;
			}
			break;
		}
	}

	//---------------------------------------------------------------------------------------------------
	// TODO: add override shaderstage flag to be able to change allowed stages ignoring the Module stage 
	inline vk::DescriptorSetLayout CreateDescriptorSetLayout(const std::vector<VariableInfo>& _SetVars, const vk::ShaderStageFlags _kStageFlags, vk::Device _hDevice, const vk::AllocationCallbacks* _pAllocators)
	{
		vk::DescriptorSetLayoutCreateInfo Info{};
		std::vector<vk::DescriptorSetLayoutBinding> Bindings;
		
		// todo: use hash of variables and stage flags to avoid creating an existing layouts

		for (const VariableInfo& Var : _SetVars)
		{
			switch (Var.kStorageClass)
			{
			case spv::StorageClassInput:
			case spv::StorageClassOutput:
			case spv::StorageClassMax:
				continue; // skip non resource classes (incomplete list)
			default:
				break;
			}

			Bindings.emplace_back();
			vk::DescriptorSetLayoutBinding& Binding = Bindings.back();
			Binding.stageFlags = _kStageFlags;
			CreateDescriptorSetLayoutBinding(Binding, Var);
		}

		Info.bindingCount = static_cast<uint32_t>(Bindings.size());
		Info.pBindings = Bindings.data();
		
		return _hDevice.createDescriptorSetLayout(Info, _pAllocators);
	}
	//---------------------------------------------------------------------------------------------------

	constexpr size_t uMaxDescriptorSets = 16u; // Per layout
	inline std::vector<vk::DescriptorSetLayout> CreateDescriptorSetLayouts(const SPIRVModule& _Module, const vk::ShaderStageFlags _kStageFlags, vk::Device _hDevice, const vk::AllocationCallbacks* _pAllocators = nullptr)
	{
		using TVarSet = std::vector<VariableInfo>;
		std::array<TVarSet, uMaxDescriptorSets> DescriptorSets;

		for (const VariableInfo& Var : _Module.GetVariables())
		{
			HASSERT(Var.uDescriptorSet < uMaxDescriptorSets, "Invalid descriptor set index");
			DescriptorSets[Var.uDescriptorSet].push_back(Var);
		}

		std::vector<vk::DescriptorSetLayout> Layouts;
		for (const TVarSet& Set : DescriptorSets)
		{
			if (Set.empty() == false)
			{
				Layouts.push_back(CreateDescriptorSetLayout(Set, _kStageFlags, _hDevice, _pAllocators));
			}
		}
	}
	//---------------------------------------------------------------------------------------------------

	struct SpecConstFactory
	{
		SpecConstFactory() : m_Stream(m_Data) {}

		// TODO: compute hash over stream and entries to avoid recompiling the same shader

		template <class T>
		struct Constant
		{
			friend class SpecConstFactory;

			Constant& operator=(const T& _Value)
			{
				if (_Value != Value)
				{
					Parent.SetChangedFlag();
					Value = _Value;
				}
			}

			const T& operator T() { return Value; }
		private:

			Constant(SpecConstFactory& _Parent) : Value(_Value), Parent(_Parent) {}
		private:
			T& Value;
			SpecConstFactory& Parent;
		};

		template <class T>
		friend struct Constant;

		template <class T>
		Constant<T> SetConstant(const T& _Value, const VariableInfo& _Var)
		{
			HASSERT(_Var.uSpecConstId != HUNDEFINED32, "Variable is not a specialization constant");
			HASSERT(_Var.Type.GetSize() != sizeof(T), "Variable size mismatch");

			vk::SpecializationMapEntry Entry{};
			Entry.constantID = _Var.uSpecConstId;
			Entry.offset = static_cast<uint32_t>(m_Stream.get_offset());
			Entry.size = static_cast<uint32_t>(sizeof(T));

			m_Entries.push_back(std::move(Entry));
			m_Stream << _Value;

			m_bChanged = true;

			return Constant<T>(*this, *reinterpret_cast<T*>(m_Stream.get_data(Entry.offset)));
		}

		vk::SpecializationInfo GetInfo() const
		{
			vk::SpecializationInfo Info{};
			Info.dataSize = static_cast<uint32_t>(m_Data.size());
			Info.mapEntryCount = static_cast<uint32_t>(m_Entries.size());
			Info.pData = m_Data.data();
			Info.pMapEntries = m_Entries.data();

			return Info;
		}

		// Make sure to destruct all Constant<T> instances before calling this
		void Reset()
		{
			m_Entries.clear();
			m_Stream.clear();
			m_bChanged = false;
		}

		const bool HasChanged() const { m_bChanged; }

	private:
		void SetChangedFlag() { m_bChanged = true; }
	private:
		bool m_bChanged = false;
		std::vector<vk::SpecializationMapEntry> m_Entries;
		hlx::bytes m_Data;
		hlx::bytestream m_Stream;
	};
	//---------------------------------------------------------------------------------------------------

	struct PushConstantFactory
	{
		PushConstantFactory() : m_Stream(m_Data){}

		template <class T>
		struct Constant
		{
			friend class PushConstantFactory;

			Constant& operator=(const T& _Value)
			{
				if (_Value != Value)
				{
					Parent.SetChangedFlag(uOffset, (uint32_t)sizeof(T));
					Value = _Value;
				}
			}

			const T& operator T() { return Value; }
		private:

			Constant(PushConstantFactory& _Parent, T& _Value , const uint32_t _uOffset) :
				Value(_Value), Parent(_Parent), uOffset(_uOffset) {}
		private:
			const uint32_t uOffset;
			T& Value;
			PushConstantFactory& Parent;
		};

		template <class T>
		friend struct Constant;

		template <class T>
		Constant<T> AddConstant(const T& _Value, const vk::ShaderStageFlags _kStages)
		{
			const uint32_t uOffset = static_cast<uint32_t>(m_Stream.get_offset());
			SetChangedFlag(uOffset, (uint32_t)sizeof(T));

			// here we create a range for each variable T since T can be a struct too

			vk::PushConstantRange Range{};
			Range.offset = uOffset;
			Range.stageFlags = _kStages;
			Range.size = (uint32_t)sizeof(T);
			m_Ranges.push_back(std::move(Range));

			m_Stream <<_Value;			
			return Constant<T>(*this, *reinterpret_cast<T*>(m_Stream.get_data(uOffset)), uOffset);
		}

		// to be called after vulkan uploaded the push constants
		void ResetChangedFlag() { uStartOffset = HUNDEFINED32; uEndOffset = 0u; }
		const bool HasChanged() const { return  uStartOffset != HUNDEFINED32 &&(uEndOffset-uStartOffset) > 0; }

		const uint32_t GetRangeCount() const { return static_cast<uint32_t>(m_Ranges.size()); }
		const vk::PushConstantRange* GetRanges() const { return m_Ranges.data(); }
		const void* GetValues() const { return m_Data.data(); }

		// Make sure to destruct all Constant<T> instances before calling this
		void Reset()
		{
			ResetChangedFlag();
			m_Ranges.clear();
			m_Stream.clear();
		}

	private:
		void SetChangedFlag(const uint32_t _uOffset, const uint32_t _uSize)
		{
			uStartOffset = std::min(uStartOffset, _uOffset);
			uEndOffset = std::max(uEndOffset, _uOffset + _uSize);
		}

	private:
		// range
		uint32_t uStartOffset = HUNDEFINED32;
		uint32_t uEndOffset = 0u;

		std::vector<vk::PushConstantRange> m_Ranges;
		hlx::bytes m_Data;
		hlx::bytestream m_Stream;
	};

	//---------------------------------------------------------------------------------------------------

	inline vk::PipelineLayout CreatePipelineLayout(const SPIRVModule& _Module, const vk::ShaderStageFlags _kStageFlags, vk::Device _hDevice, const vk::AllocationCallbacks* _pAllocators = nullptr, const PushConstantFactory* _pPushConstants = nullptr)
	{
		vk::PipelineLayoutCreateInfo Info{};

		Info.pPushConstantRanges = _pPushConstants != nullptr ? _pPushConstants->GetRanges() : nullptr;
		Info.pushConstantRangeCount = _pPushConstants != nullptr ? _pPushConstants->GetRangeCount() : 0u;
		std::vector<vk::DescriptorSetLayout> Layouts(CreateDescriptorSetLayouts(_Module, _kStageFlags, _hDevice, _pAllocators));

		Info.pSetLayouts = Layouts.data();
		Info.setLayoutCount = static_cast<uint32_t>(Layouts.size());

		return _hDevice.createPipelineLayout(Info, _pAllocators);
	}
	//---------------------------------------------------------------------------------------------------

	template <class Selector, class Element>
	inline Element Select(const Selector _kSelector, const std::initializer_list<Selector>& _Selectors, const std::initializer_list<Element>& _Elements)
	{
		for (auto sit = _Selectors.begin(), auto eit = _Elements.begin(); sit != _Selectors.end(); ++sit, ++eit)
		{
			if (*sit == _kSelector)
				return *eit;
		}

		return {};
	}
	//---------------------------------------------------------------------------------------------------

	// converts variable type (vertex shader input) to vk format, images etc not supported
	// not all types are supported (e.g. unorm, snorm, scaled, compressed etc)
	inline vk::Format TypeToFormat(const SPIRVType& _Type)
	{
		const spv::Op kType = _Type.GetType();
		const spv::Op kSubType = _Type.GetSubTypes().empty() ? spv::OpNop : _Type.GetSubTypes().front().GetType();
		const uint32_t uDim = _Type.GetDimension();

		switch (kType)
		{
		case spv::OpTypeInt:
			if (_Type.GetSign()) // signed
				return Select(uDim, {8u, 16u, 32u}, { vk::Format::eR8Sint, vk::Format::eR16Sint, vk::Format::eR32Sint }); // bitdepth
			else
				return Select(uDim, { 8u, 16u, 32u }, { vk::Format::eR8Uint, vk::Format::eR16Uint, vk::Format::eR32Uint }); // bitdepth
		case spv::OpTypeFloat:
			return Select(uDim, { 16u, 32u }, { vk::Format::eR16Sfloat, vk::Format::eR32Sfloat }); // bitdepth
		case spv::OpTypeVector:
			HASSERT(kSubType != spv::OpNop, "Invalid subtype");
			switch (kSubType) // 32 bit format assumed
			{
			case spv::OpTypeInt:
				if (_Type.GetSign()) // signed
					return Select(uDim, { 2u, 3u, 4u }, { vk::Format::eR32G32Sint, vk::Format::eR32G32B32Sint, vk::Format::eR32G32B32A32Sint});
				else
					return Select(uDim, { 2u, 3u, 4u }, { vk::Format::eR32G32Uint, vk::Format::eR32G32B32Uint, vk::Format::eR32G32B32A32Uint});
			case spv::OpTypeFloat:
				return Select(uDim, { 2u, 3u, 4u }, { vk::Format::eR32G32Sfloat, vk::Format::eR32G32B32Sfloat, vk::Format::eR32G32B32A32Sfloat});
			default: break;
			}			
			break;
		default: break;
		}

		return vk::Format::eUndefined;
	}

	//---------------------------------------------------------------------------------------------------

	struct VertexLayoutFactory
	{
		// valid as long as VertexLayoutFactory is valid and GetVertexLayout() has not been called again
		vk::PipelineVertexInputStateCreateInfo GetVertexLayout(const std::vector<VariableInfo>& _Vars)
		{
			m_Attributes.resize(0);
			m_Bindings.resize(0); // clean data
		
			for (const VariableInfo& Var : _Vars)
			{
				if (Var.kStorageClass == spv::StorageClassInput)
				{
					HASSERT(Var.uBinding < 16u, "Invalid binding (to high)");

					auto it = std::find_if(m_Bindings.begin(), m_Bindings.end(), [&](const vk::VertexInputBindingDescription& _Binding) {return _Binding.binding == Var.uBinding; });
					if (it == m_Bindings.end())
					{
						it = m_Bindings.insert(m_Bindings.end(), {});
					}

					vk::VertexInputBindingDescription& Binding = *it;
					Binding.binding = Var.uBinding;
					// variables with the same binding should be forced to have the same inputrate
					Binding.inputRate = Var.bInstanceData ? vk::VertexInputRate::eInstance : vk::VertexInputRate::eVertex;

					vk::VertexInputAttributeDescription Attrib{};
					Attrib.binding = Var.uBinding;
					Attrib.location = Var.uLocation;
					Attrib.format = TypeToFormat(Var.Type);
					Attrib.offset = Binding.stride;

					Binding.stride += Var.Type.GetSize();

					HASSERT(Attrib.format != vk::Format::eUndefined, "Unknown vertex attribute format");

					m_Attributes.push_back(std::move(Attrib));
				}
			}

			vk::PipelineVertexInputStateCreateInfo Layout{};
			Layout.pNext = nullptr;
			Layout.vertexAttributeDescriptionCount = static_cast<uint32_t>(m_Attributes.size());
			Layout.vertexBindingDescriptionCount = static_cast<uint32_t>(m_Bindings.size());
			Layout.pVertexAttributeDescriptions = m_Attributes.data();
			Layout.pVertexBindingDescriptions = m_Bindings.data();

			return Layout;
		}

	private:
		std::vector<vk::VertexInputAttributeDescription> m_Attributes;
		std::vector<vk::VertexInputBindingDescription> m_Bindings; // buffer slots
	};

	//---------------------------------------------------------------------------------------------------

	vk::ShaderModuleCreateInfo GetShaderModuleInfo(const SPIRVModule& _Module)
	{
		vk::ShaderModuleCreateInfo Info{};
		Info.codeSize = static_cast<uint32_t>(_Module.GetCode().size());
		Info.pCode = _Module.GetCode().data();
		return Info;
	}

	vk::ShaderModule CreateShaderModule(vk::Device _hDevice, const SPIRVModule& _Module, vk::AllocationCallbacks* _pAllocCallbacks = nullptr)
	{
		vk::ShaderModuleCreateInfo Info(GetShaderModuleInfo(_Module));
		vk::ShaderModule vkModule{};
		vk::Result kResult = vk::Result::eSuccess;
		if ((kResult = _hDevice.createShaderModule(&Info, _pAllocCallbacks, &vkModule)) != vk::Result::eSuccess)
		{
			HERROR("Failed to create shader module %s [%s]", _Module.GetEntryPoint().c_str(), vk::to_string(kResult).c_str());
		}

		return vkModule;
	}

	inline vk::PipelineShaderStageCreateInfo CreateShaderStage(vk::Device _hDevice, const SPIRVModule& _Module, const vk::SpecializationInfo* _pSpecInfo = nullptr, vk::AllocationCallbacks* _pAllocCallbacks = nullptr)
	{
		vk::PipelineShaderStageCreateInfo ShaderStage{};

		ShaderStage.stage = GetShaderStage(_Module);
		ShaderStage.module = CreateShaderModule(_hDevice, _Module, _pAllocCallbacks);
		ShaderStage.pName = _Module.GetEntryPoint().c_str();
		ShaderStage.pSpecializationInfo = _pSpecInfo;

		return ShaderStage;
	}

	//---------------------------------------------------------------------------------------------------

}

#endif // !TRACY_SPIRVINTEROP_H