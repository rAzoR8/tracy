#ifndef TRACY_SPIRVTYPE_H
#define TRACY_SPIRVTYPE_H

#include <vulkan\spirv.hpp>
#include <vector>
#include <stdint.h>

namespace Tracy
{
#ifndef OPDEFS
#define OPDEFS(t, s, b) \
		static constexpr spv::Op type = t; \
		static constexpr bool sign = s; \
		static constexpr uint32_t bits = b;
#endif

	template <class T>
	struct optype {};

	template <>
	struct optype<float> { OPDEFS(spv::OpTypeFloat, true, 32u)};

	template <>
	struct optype<int> { OPDEFS(spv::OpTypeInt, true, 32u)};

	template <>
	struct optype<unsigned>{ OPDEFS(spv::OpTypeInt, false, 32u) };

	template <>
	struct optype<short>{ OPDEFS(spv::OpTypeInt, true, 16u) };

	template <>
	struct optype<unsigned short>{ OPDEFS(spv::OpTypeInt, false, 16u) };

	class SPIRVType
	{
	public:
		SPIRVType(const spv::Op _kOp = spv::OpTypeVoid, const uint32_t _uDimension = 0u, const bool _bSign = true);
		SPIRVType(const spv::Op _kOp, const SPIRVType& _SubType, const uint32_t _uDimension = 0u, const bool _bSign = true);
		SPIRVType(const spv::Op _kOp, const std::vector<SPIRVType>& _SubTypes, const uint32_t _uDimension = 0u, const bool _bSign = true);

		~SPIRVType();

		SPIRVType& Append(const SPIRVType& _SubType);
		SPIRVType& Member(const SPIRVType& _SubType);

		size_t GetHash() const;
		const std::vector<SPIRVType>& GetSubTypes() const;
		const spv::Op& GetType() const;
		const uint32_t& GetDimension() const;
		const bool& GetSign() const;

		// type helpers
		static SPIRVType Int() { return SPIRVType(spv::OpTypeInt, 32u, true); }
		static SPIRVType UInt() { return SPIRVType(spv::OpTypeInt, 32u, false); }
		static SPIRVType Short() { return SPIRVType(spv::OpTypeInt, 16u, true); }
		static SPIRVType UShort() { return SPIRVType(spv::OpTypeInt, 16u, false); }
		static SPIRVType Float() { return SPIRVType(spv::OpTypeFloat, 32u, true); }
		static SPIRVType Struct(const std::vector<SPIRVType>& _MemberTypes = {}) { return SPIRVType(spv::OpTypeStruct, _MemberTypes); }
		
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

		template <class T, uint32_t row = 4, uint32_t col = 4>
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

	private:
		std::vector<SPIRVType> m_SubTypes; // struct members etc
		spv::Op m_kBaseType;
		uint32_t m_uDimension = 0u; // OpTypeArray, dimension, bits
		bool m_bSign = true;
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
} // Tracy

#endif // !TRACY_SPIRVTYPE_H
