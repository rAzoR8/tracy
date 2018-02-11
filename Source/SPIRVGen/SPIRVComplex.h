#ifndef TRACY_SPIRVCOMPLEX_H
#define TRACY_SPIRVCOMPLEX_H

#include "SPIRVOperatorImpl.h"

namespace Tracy
{
	// z = a + bi
	// a = real, b = imag
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

		float Conjugate() const;
		float Norm() const;
		SPIRVComplex<Assemble, spv::StorageClassFunction> Inverse() const;

		// operators
		template <spv::StorageClass C1>
		const SPIRVComplex& operator*=(const SPIRVComplex<Assemble, C1>& _Other) const;
		template <spv::StorageClass C1>
		const SPIRVComplex& operator*=(const var_t<float, Assemble, C1>& _fScalar) const;

		template <spv::StorageClass C1>
		const SPIRVComplex& operator+=(const SPIRVComplex<Assemble, C1>& _Other) const;

		template <spv::StorageClass C1>
		const SPIRVComplex& operator-=(const SPIRVComplex<Assemble, C1>& _Other) const;

		template <spv::StorageClass C1>
		const SPIRVComplex& operator/=(const SPIRVComplex<Assemble, C1>& _Other) const;
	};

	//---------------------------------------------------------------------------------------------------
	template<bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1, spv::StorageClass C2>
	inline SPIRVComplex<Assemble, Class>::SPIRVComplex(const var_t<float, Assemble, C1>& _rReal, const var_t<float, Assemble, C2>& _rImaginary)
	{
		x = _rReal;
		y = _rImaginary;
	}

	//---------------------------------------------------------------------------------------------------
	template<bool Assemble, spv::StorageClass Class>
	inline float SPIRVComplex<Assemble, Class>::Conjugate() const
	{
		return x*x + y*y;
	}

	template<bool Assemble, spv::StorageClass Class>
	inline float SPIRVComplex<Assemble, Class>::Norm() const
	{
		return std::sqrtf(x*x + y*y);
	}

	template<bool Assemble, spv::StorageClass Class>
	inline SPIRVComplex<Assemble, spv::StorageClassFunction> SPIRVComplex<Assemble, Class>::Inverse() const
	{
		auto COut = SPIRVComplex<Assemble, spv::StorageClassFunction>();
		const float fRcpConj = 1.0f / Conjugate();
		COut.x = x * fRcpConjugate;
		COut.y = -1.0f * (y * fRcpCnjugate);
		return COut;
	}

	//---------------------------------------------------------------------------------------------------
	// Complex Multiplication
	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline void CMul(const SPIRVComplex<Assemble, C1>& _c1, const SPIRVComplex<Assemble, C2>& _c2, const SPIRVComplex<Assemble, C3>& _cOut)
	{
		// z1z2 = (a1 + b1i)(a2 + b2i) =
		//		= (a1a2 - b1b2)(a1b2 + b1a2)i
		const auto A1 = _c1.x; const auto B1 = _c2.y;
		const auto A2 = _c2.x; const auto B2 = _c2.y;
		_cOut.x = A1 * A2 - B1 * B2;
		_cOut.y = A1 * B2 + B1 * A2;
	}

	template<bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const SPIRVComplex<Assemble, Class>& SPIRVComplex<Assemble, Class>::operator*=(const SPIRVComplex<Assemble, C1>& _Other) const
	{
		CMul(*this, _Other, *this);
		return *this;
	}

	template<bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const SPIRVComplex<Assemble, Class>& SPIRVComplex<Assemble, Class>::operator*=(const var_t<float, Assemble, C1>& _fScalar) const
	{
		x *= _fScalar;
		y *= _fScalar;
		return *this;
	}

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline const SPIRVComplex<Assemble, spv::StorageClassFunction> operator*(const SPIRVComplex<Assemble, C1>& _c1, const SPIRVComplex<Assemble, C2>& _c2)
	{
		auto COut = SPIRVComplex<Assemble, spv::StorageClassFunction>();
		CMul(_c1, _c2, COut);
		return COut;
	}

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline const SPIRVComplex<Assemble, spv::StorageClassFunction> operator*(const SPIRVComplex<Assemble, C1>& _c1, const var_t<float, Assemble, C2>& _fScalar)
	{
		auto COut = SPIRVComplex<Assemble, spv::StorageClassFunction>();
		COut.x = _c1.x * _fScalar;
		COut.y = _c1.y * _fScalar;
		return COut;
	}

	//---------------------------------------------------------------------------------------------------
	// Complex Sum
	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline void CAdd(const SPIRVComplex<Assemble, C1>& _c1, const SPIRVComplex<Assemble, C2>& _c2, SPIRVComplex<Assemble, C3>& _cOut)
	{
		// z1+z2 = (a1 + b1i)+(a2 + b2i) =
		//		 = (a1+a2)+(b1+b2)i
		const auto A1 = _c1.x; const auto B1 = _c2.y;
		const auto A2 = _c2.x; const auto B2 = _c2.y;
		_cOut.x = A1 + A2;
		_cOut.y = B1 + B2;
	}

	template<bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const SPIRVComplex<Assemble, Class>& SPIRVComplex<Assemble, Class>::operator+=(const SPIRVComplex<Assemble, C1>& _Other) const
	{
		CAdd(*this, _Other, *this);
		return *this;
	}

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline const SPIRVComplex<Assemble, spv::StorageClassFunction> operator+(const SPIRVComplex<Assemble, C1>& _c1, const SPIRVComplex<Assemble, C2>& _c2)
	{
		auto COut = SPIRVComplex<Assemble, spv::StorageClassFunction>();
		CAdd(_c1, _c2, COut);
		return COut;
	}

	//---------------------------------------------------------------------------------------------------
	// Complex Subtraction
	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline void CSub(const SPIRVComplex<Assemble, C1>& _c1, const SPIRVComplex<Assemble, C2>& _c2, SPIRVComplex<Assemble, C3>& _cOut)
	{
		// z1+z2 = (a1 + b1i)-(a2 + b2i) =
		//		 = (a1-a2)+(b1-b2)i
		const auto A1 = _c1.x; const auto B1 = _c2.y;
		const auto A2 = _c2.x; const auto B2 = _c2.y;
		_cOut.x = A1 - A2;
		_cOut.y = B1 - B2;
	}

	template<bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const SPIRVComplex<Assemble, Class>& SPIRVComplex<Assemble, Class>::operator-=(const SPIRVComplex<Assemble, C1>& _Other) const
	{
		CSub(*this, _Other, *this);
		return *this;
	}

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline const SPIRVComplex<Assemble, spv::StorageClassFunction> operator-(const SPIRVComplex<Assemble, C1>& _c1, const SPIRVComplex<Assemble, C2>& _c2)
	{
		auto COut = SPIRVComplex<Assemble, spv::StorageClassFunction>();
		CSub(_c1, _c2, COut);
		return COut;
	}

	//---------------------------------------------------------------------------------------------------
	// Complex Division
	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline void CDiv(const SPIRVComplex<Assemble, C1>& _c1, const SPIRVComplex<Assemble, C2>& _c2, SPIRVComplex<Assemble, C3>& _cOut)
	{
		// z1+z2 = (a1 + b1i)/(a2 + b2i) =
		//		 = (a1a2+b1b2)/(a2^2+b2^2) + (b1a2-a1b2)/(a2^2+b2^2)i
		const auto A1 = _c1.x; const auto B1 = _c2.y;
		const auto A2 = _c2.x; const auto B2 = _c2.y;
		const float fRcpDenom = 1.0f / (A2 * A2 + B2 * B2);
		_cOut.x = (A1*A2 + B1*B2) * fRcpDenom;
		_cOut.y = (B1*A2 - A1*B2) * fRcpDenom;
	}

	template<bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const SPIRVComplex<Assemble, Class>& SPIRVComplex<Assemble, Class>::operator/=(const SPIRVComplex<Assemble, C1>& _Other) const
	{
		CDiv(*this, _Other, *this);
		return *this;
	}

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline const SPIRVComplex<Assemble, spv::StorageClassFunction> operator/(const SPIRVComplex<Assemble, C1>& _c1, const SPIRVComplex<Assemble, C2>& _c2)
	{
		auto COut = SPIRVComplex<Assemble, spv::StorageClassFunction>();
		CDiv(_c1, _c2, COut);
		return COut;
	}
}


#endif // !TRACY_SPIRVCOMPLEX_H