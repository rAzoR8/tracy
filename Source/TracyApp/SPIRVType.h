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
		SPIRVType(const spv::Op _kOp, const uint32_t _uArraySize = 0u, const bool _bSign = true);
		SPIRVType(const spv::Op _kOp, const SPIRVType& _SubType, const uint32_t _uArraySize = 0u, const bool _bSign = true);

		~SPIRVType();

		SPIRVType& Append(const SPIRVType& _SubType);
		SPIRVType& Add(const SPIRVType& _SubType);

		template <class T, uint32_t Dim = 4>
		static SPIRVType Vec()
		{
			static_assert(Dim > 1 && Dim < 5, "Invalid dimension [2,4]");
			return SPIRVType(spv::OpTypeVector, SPIRVType(optype<T>::type, optype<T>::bits, optype<T>::sign), Dim);
		}

		template <class T, uint32_t row = 4, uint32_t col = 4>
		static SPIRVType Mat()
		{
			static_assert(col > 1 && col < 5, "Invalid dimension [2,4]");
			return SPIRVType(spv::OpTypeMatrix, Vec<T, row>(), col);
		}

		size_t GetHash() const;

	private:
		std::vector<SPIRVType> m_SubTypes; // struct members etc
		spv::Op m_kBaseType;
		uint32_t m_uArraySize = 0u; // OpTypeArray
		bool m_bSign = true;
	};
} // Tracy

#endif // !TRACY_SPIRVTYPE_H
