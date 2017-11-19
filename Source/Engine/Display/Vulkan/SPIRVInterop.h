#ifndef TRACY_SPIRVINTEROP_H
#define TRACY_SPIRVINTEROP_H

#include "VulkanAPI.h"
#include "../../SPIRVGen/SPIRVModule.h"
#include "Logger.h"

namespace Tracy
{
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
			if (_InputVar.Type.GetDimension() == spv::DimSubpassData)
			{
				_Binding.descriptorType = vk::DescriptorType::eInputAttachment;
			}
			else
			{
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
}

#endif // !TRACY_SPIRVINTEROP_H