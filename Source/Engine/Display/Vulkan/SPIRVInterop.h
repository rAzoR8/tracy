#ifndef TRACY_SPIRVINTEROP_H
#define TRACY_SPIRVINTEROP_H

#include "VulkanAPI.h"
#include "../../SPIRVGen/SPIRVModule.h"
#include "Logger.h"
#include "ByteStream.h"

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

	struct SpecConstFactory
	{
		SpecConstFactory() : m_Stream(m_Data) {}

		template <class T>
		void SetConstant(const T& _Value, const VariableInfo& _Var)
		{
			HASSERT(_Var.uSpecConstId != HUNDEFINED32, "Variable is not a specialization constant");
			HASSERT(_Var.Type.GetSize() != sizeof(T), "Variable size mismatch");

			vk::SpecializationMapEntry Entry{};
			Entry.constantID = _Var.uSpecConstId;
			Entry.offset = static_cast<uint32_t>(m_Stream.get_offset());
			Entry.size = static_cast<uint32_t>(sizeof(T));

			m_Entries.push_back(std::move(Entry));
			m_Stream.put(_Value);
		}

		template <class T>
		void UpdateConstant(const T& _Value, const VariableInfo& _Var)
		{
			HASSERT(_Var.uSpecConstId != HUNDEFINED32, "Variable is not a specialization constant");
			HASSERT(_Var.Type.GetSize() != sizeof(T), "Variable size mismatch");

			for (const vk::SpecializationMapEntry& Entry : m_Entries)
			{
				if (Entry.constantID == _Var.uSpecConstId)
				{
					HASSERT(sizeof(T) == Entry.size, "Entry size mismatch");					
					m_Stream.replace(Entry.offset, _Value);

					return;
				}
			}
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

		void Reset()
		{
			m_Entries.clear();
			m_Stream.clear();
		}
	private:
		std::vector<vk::SpecializationMapEntry> m_Entries;
		hlx::bytes m_Data;
		hlx::bytestream m_Stream;
	};

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
		friend class Constant;

		template <class T>
		Constant<T> AddConstant(const T& _Value)
		{
			const uint32_t uOffset = static_cast<uint32_t>(m_Stream.get_offset());
			SetChangedFlag(uOffset, (uint32_t)sizeof(T));

			m_Stream <<_Value;			
			return Constant<T>(*this, *reinterpret_cast<T*>(m_Stream.get_data(uOffset)), uOffset);
		}

		// to be called after vulkan uploaded the push constants
		void ResetChangedFlag() { uStartOffset = HUNDEFINED32; uEndOffset = 0u; }
		const bool HasChanged() const { return  uStartOffset != HUNDEFINED32 &&(uEndOffset-uStartOffset) > 0; }

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

		hlx::bytes m_Data;
		hlx::bytestream m_Stream;
	};
}

#endif // !TRACY_SPIRVINTEROP_H