#ifndef TRACY_SPIRVTYPE_H
#define TRACY_SPIRVTYPE_H

#include <vector>
#include <stdint.h>
#include "SPIRVVariableTypes.h"

namespace Tracy
{
#pragma region type defs
#ifndef OPDEFS
#define OPDEFS(t, s, b) \
		static constexpr spv::Op type = t; \
		static constexpr bool sign = s; \
		static constexpr uint32_t bits = b;
#endif

	template <class T>
	struct optype {};

	template <>
	struct optype<bool> { OPDEFS(spv::OpTypeBool, false, 0u) };

	template <>
	struct optype<int16_t> { OPDEFS(spv::OpTypeInt, true, 16u) };

	template <>
	struct optype<uint16_t> { OPDEFS(spv::OpTypeInt, false, 16u) };

	template <>
	struct optype<float> { OPDEFS(spv::OpTypeFloat, true, 32u)};

	template <>
	struct optype<double> { OPDEFS(spv::OpTypeFloat, true, 64u) };

	template <>
	struct optype<int32_t> { OPDEFS(spv::OpTypeInt, true, 32u)};

	template <>
	struct optype<uint32_t>{ OPDEFS(spv::OpTypeInt, false, 32u) };

	template <>
	struct optype<int64_t> { OPDEFS(spv::OpTypeInt, true, 64u) };

	template <>
	struct optype<uint64_t> { OPDEFS(spv::OpTypeInt, false, 64u) };
#pragma endregion

	class SPIRVType
	{
	public:
		SPIRVType(const spv::Op _kOp = spv::OpTypeVoid, const uint32_t _uDimension = 0u, const bool _bSign = true);
		SPIRVType(const spv::Op _kOp, const SPIRVType& _SubType, const uint32_t _uDimension = 0u, const bool _bSign = true);
		SPIRVType(const spv::Op _kOp, const std::vector<SPIRVType>& _SubTypes, const uint32_t _uDimension = 0u, const bool _bSign = true);

		// image constructor
		SPIRVType(const SPIRVType& _SampledType, const spv::Dim _uDimension, const bool _bArray, const ETexDepthType _kDepthType, const bool _bMultiSampled, const ETexSamplerAccess _kSamplerAccess);
		
		~SPIRVType();

		SPIRVType& Append(const SPIRVType& _SubType);
		SPIRVType& Member(const SPIRVType& _SubType);

		size_t GetHash() const;
		const std::vector<SPIRVType>& GetSubTypes() const;
		const spv::Op& GetType() const;
		const uint32_t& GetDimension() const;
		const bool& GetSign() const;
		const bool& GetArray() const;
		const bool& GetMultiSampled() const;
		const ETexDepthType& GetTexDepthType() const;
		const ETexSamplerAccess& GetTexSamplerAccess() const;

		// type helpers
		static SPIRVType Void() { return SPIRVType(spv::OpTypeVoid, 0u, false); }
		static SPIRVType Bool() { return SPIRVType(spv::OpTypeBool, 0u, false); }
		static SPIRVType Int() { return SPIRVType(spv::OpTypeInt, 32u, true); }
		static SPIRVType UInt() { return SPIRVType(spv::OpTypeInt, 32u, false); }
		static SPIRVType Short() { return SPIRVType(spv::OpTypeInt, 16u, true); }
		static SPIRVType UShort() { return SPIRVType(spv::OpTypeInt, 16u, false); }
		static SPIRVType Float() { return SPIRVType(spv::OpTypeFloat, 32u, true); }
		static SPIRVType Sampler() { return SPIRVType(spv::OpTypeSampler); }
		static SPIRVType Struct(const std::vector<SPIRVType>& _MemberTypes = {}) { return SPIRVType(spv::OpTypeStruct, _MemberTypes); }
		static SPIRVType Function(const SPIRVType& _ReturnType = Void(), const std::vector<SPIRVType>& _ParameterTypes = {});
		static SPIRVType Pointer(const SPIRVType& _Type, const spv::StorageClass _kClass = spv::StorageClassFunction) { return SPIRVType(spv::OpTypePointer, _Type, (uint32_t)_kClass); }
		
		static SPIRVType Image(
			const SPIRVType& _SampledType = Float(), 
			const spv::Dim _kDimension = spv::Dim2D,
			const bool _bArray = false,
			const ETexDepthType _kDepthType = kTexDepthType_NonDepth,
			const bool _bMultiSampled = false,
			const ETexSamplerAccess _kSamplerAccess = kTexSamplerAccess_Sampled)
		{ return SPIRVType(_SampledType, _kDimension, _bArray, _kDepthType, _bMultiSampled, _kSamplerAccess); }

		static SPIRVType SampledImage(const SPIRVType& _ImageType) { return SPIRVType(spv::OpTypeSampledImage, _ImageType); }

		template <class T, class U = std::decay_t<T>>
		static SPIRVType Primitive() { return SPIRVType(optype<U>::type, optype<U>::bits, optype<U>::sign); }

		template <class T, uint32_t Dim = 4>
		static SPIRVType Vec()
		{
			static_assert(Dim > 1 && Dim < 5, "Invalid dimension [2,4]");
			return SPIRVType(spv::OpTypeVector, Primitive<T>(), Dim);
		}

		template <class T>
		static SPIRVType Vec(const uint32_t Dim)
		{
			return SPIRVType(spv::OpTypeVector, Primitive<T>(), Dim);
		}

		template <class T = float, uint32_t row = 4, uint32_t col = 4>
		static SPIRVType Mat()
		{
			static_assert(col > 1 && col < 5, "Invalid dimension [2,4]");
			return SPIRVType(spv::OpTypeMatrix, Vec<T, row>(), col);
		}

		template <class T>
		static SPIRVType Mat(const uint32_t row, const uint32_t col)
		{
			return SPIRVType(spv::OpTypeMatrix, Vec<T>(row), col);
		}

		template<class T, typename = std::enable_if_t<is_texture<T>> >
		static SPIRVType FromImageType() { return SPIRVType::Image(FromBaseType<base_type_t<T::TexComponentType>>(), T::Dim, T::Array, T::DepthType, T::MultiSampled, T::SamplerAccess); }

		template <class T>
		static SPIRVType FromBaseType() {static_assert(false, "Unsupported type");}

		template <class T>
		static SPIRVType FromType()
		{
			if constexpr(is_texture<T>)
			{
				return FromImageType<T>();
			}
			else
			{
				return FromBaseType<T>();
			}
		}

	private:
		std::vector<SPIRVType> m_SubTypes; // struct members etc
		spv::Op m_kBaseType = spv::OpNop;
		uint32_t m_uDimension = 0u; // OpTypeArray, dimension, bits
		bool m_bSign = true;

		// for image:
		bool m_bArray = false;
		bool m_bMultiSampled = false;
		ETexDepthType m_kTexDepthType = kTexDepthType_Unspecified;
		ETexSamplerAccess m_kSamplerAccess = kTexSamplerAccess_Runtime;
	};
	//---------------------------------------------------------------------------------------------------

	inline const std::vector<SPIRVType>& SPIRVType::GetSubTypes() const
	{
		return m_SubTypes;
	}
	inline const spv::Op& SPIRVType::GetType() const
	{
		return m_kBaseType;
	}
	inline const uint32_t& SPIRVType::GetDimension() const
	{
		return m_uDimension;
	}
	inline const bool& SPIRVType::GetSign() const
	{
		return m_bSign;
	}

	inline const bool& SPIRVType::GetArray() const
	{
		return m_bArray;
	}

	inline const bool& SPIRVType::GetMultiSampled() const
	{
		return m_bMultiSampled;
	}

	inline const ETexDepthType& SPIRVType::GetTexDepthType() const
	{
		return m_kTexDepthType;
	}

	inline const ETexSamplerAccess& SPIRVType::GetTexSamplerAccess() const
	{
		return m_kSamplerAccess;
	}

	inline SPIRVType SPIRVType::Function(const SPIRVType& _ReturnType, const std::vector<SPIRVType>& _ParameterTypes)
	{
		SPIRVType Func(spv::OpTypeFunction, _ReturnType);
		for (const SPIRVType& Param : _ParameterTypes)
		{
			Func.Member(Param);
		}
		return Func;
	}

#pragma region FromType
	template<>
	inline SPIRVType SPIRVType::FromBaseType<sampler_t>() { return SPIRVType::Sampler(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<bool>() { return SPIRVType::Bool(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<float>(){return SPIRVType::Primitive<float>();}

	template<>
	inline SPIRVType SPIRVType::FromBaseType<int32_t>(){return SPIRVType::Primitive<int32_t>();}

	template<>
	inline SPIRVType SPIRVType::FromBaseType<uint32_t>() { return SPIRVType::Primitive<uint32_t>(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<int2_t>() { return SPIRVType::Vec<int32_t, 2>(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<int3_t>() { return SPIRVType::Vec<int32_t, 3>(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<int4_t>() { return SPIRVType::Vec<int32_t, 4>(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<uint2_t>() { return SPIRVType::Vec<uint32_t, 2>(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<uint3_t>() { return SPIRVType::Vec<uint32_t, 3>(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<uint4_t>() { return SPIRVType::Vec<uint32_t, 4>(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<float2_t>() { return SPIRVType::Vec<float, 2>(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<float3_t>() { return SPIRVType::Vec<float, 3>(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<float4_t>() { return SPIRVType::Vec<float, 4>(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<float4x4_t>() { return SPIRVType::Mat<float>(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<float2x2_t>() { return SPIRVType::Mat<float, 2, 2>(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<float3x3_t>() { return SPIRVType::Mat<float, 3, 3>(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<float4x3_t>() { return SPIRVType::Mat<float, 4, 3>(); }

	template<>
	inline SPIRVType SPIRVType::FromBaseType<float3x4_t>() { return SPIRVType::Mat<float, 3, 4>(); }
#pragma endregion
} // Tracy

#endif // !TRACY_SPIRVTYPE_H
