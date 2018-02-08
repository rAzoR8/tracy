#ifndef TRACY_SPIRVCOMPLEX_H
#define TRACY_SPIRVCOMPLEX_H

#include "SPIRVOperatorImpl.h"

namespace Tracy
{
	template <bool Assemble = true, spv::StorageClass Class = spv::StorageClassFunction>
	struct SPIRVComplex : public var_t<float2_t, Assemble, Class>
	{
		using var_t::var_t;

		//SPRIVComplex() {};

		// construct from real & imaginary
		template <spv::StorageClass C1, spv::StorageClass C2>
		SPIRVComplex(const var_t<float, Assemble, C1>& _rReal, const var_t<float, Assemble, C2>& _rImaginary);

		// construct from float2
		//template <spv::StorageClass C1>
		//SPRIVComplex(const var_t<float2_t, Assemble, C1>& _vComplex);

		// operators
		// TODO : implement all available in the doc
		template <spv::StorageClass C1>
		const SPIRVComplex& operator*=(const SPIRVComplex<Assemble, C1>& _Other) const;
	};

	//---------------------------------------------------------------------------------------------------
	template<bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1, spv::StorageClass C2>
	inline SPIRVComplex<Assemble, Class>::SPIRVComplex(const var_t<float, Assemble, C1>& _rReal, const var_t<float, Assemble, C2>& _rImaginary)
	{
		x = _rReal;
		y = _rImaginary;
	}

	template<bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const SPIRVComplex<Assemble, Class>& SPIRVComplex<Assemble, Class>::operator*=(const SPIRVComplex<Assemble, C1>& _Other) const
	{
		// z = a + bi, a = real, b = imag
		// z1z2 = (a1 + b1i)(a2 + b2i) =
		// = (a1a2 - b1b2)(a1b2 + b1a2)i
		const auto R1 = x; const auto I1 = y;
		const auto R2 = _Other.x; const auto I2 = _Other.y;
		x = R1 * R2 - I1 * I2;
		y = R1 * I2 + I1 * R2;

		return *this;
	}
}


#endif // !TRACY_SPIRVCOMPLEX_H