#ifndef TRACY_SPIRVQUATERNION_H
#define TRACY_SPIRVQUATERNION_H

#include "SPIRVOperatorImpl.h"
//http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/
namespace Tracy
{
	template <bool Assemble = true, spv::StorageClass Class = spv::StorageClassFunction>
	struct SPIRVQuaternion : public var_t<quaternion_t, Assemble, Class>
	{
		using var_t::var_t;

		SPIRVQuaternion() {};

		//template <spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3, spv::StorageClass C4>
		//SPIRVQuaternion(const var_t<float, Assemble, C1>& x, const var_t<float, Assemble, C2>& y, const var_t<float, Assemble, C3>& z, const var_t<float, Assemble, C3>& w);

		// construct from rotation axis & radian angle
		template <spv::StorageClass C1, spv::StorageClass C2>
		SPIRVQuaternion(const var_t<float3_t, Assemble, C1>& _vAxis, const var_t<float, Assemble, C2>& _fAngleRad);

		template <spv::StorageClass C1>
		const SPIRVQuaternion& operator*=(const SPIRVQuaternion<Assemble, C1>& _Other) const;
	};

	//template<bool Assemble, spv::StorageClass Class>
	//template<spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3, spv::StorageClass C4>
	//inline SPIRVQuaternion<Assemble, Class>::SPIRVQuaternion(const var_t<float, Assemble, C1>& x, const var_t<float, Assemble, C2>& y, const var_t<float, Assemble, C3>& z, const var_t<float, Assemble, C3>& w) :
	//{
	//}

	//---------------------------------------------------------------------------------------------------
	template<bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1, spv::StorageClass C2>
	inline SPIRVQuaternion<Assemble, Class>::SPIRVQuaternion(const var_t<float3_t, Assemble, C1>& _vAxis, const var_t<float, Assemble, C2>& _fAngleRad)
	{
		if constexpr(Assemble == false)
		{
			Value = glm::angleAxis(_fAngleRad.Value, _vAxis.Value); //glm::degrees(_fAngleRad)
		}
		else
		{
			const auto a = _fAngleRad * 0.5f;
			xyz = _vAxis * Sin(a);
			w = Cos(a);
		}
	}

	//---------------------------------------------------------------------------------------------------
	// Helper function

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline void QMul(const SPIRVQuaternion<Assemble, C1>& q1, const SPIRVQuaternion<Assemble, C2>& q2, const SPIRVQuaternion<Assemble, C3>& qout)
	{
		if constexpr(Assemble == false)
		{
			qout.Value = q1.Value * q2.Value; //glm
		}
		else
		{
			//https://gist.github.com/mattatz/40a91588d5fb38240403f198a938a593
			//var.xyz = q2.xyz * q1.w + q1.xyz * q2.w + cross(q1.xyz, q2.xyz);
			//var.w = q1.w * q2.w - dot(q1.xyz, q2.xyz);

			const auto q1axis = q1.xyz; const auto q1angle = q1.w;
			const auto q2axis = q2.xyz; const auto q2angle = q2.w;
			qout.xyz = q2axis * q1angle + q1axis * q2angle + Cross(q1axis, q2axis);
			qout.w = q1angle * q2angle - Dot(q1axis, q2axis);
		}
	}
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline SPIRVQuaternion<Assemble, spv::StorageClassFunction> operator*(const SPIRVQuaternion<Assemble, C1>& q1, const SPIRVQuaternion<Assemble, C2>& q2)
	{
		auto var = SPIRVQuaternion<Assemble, spv::StorageClassFunction>();	
		QMul(q1, q2, var);
		return var;
	}
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const SPIRVQuaternion<Assemble, Class>& SPIRVQuaternion<Assemble, Class>::operator*=(const SPIRVQuaternion<Assemble, C1>& _Other) const
	{
		QMul(*this, _Other, *this);
		return *this;
	}
}//

#endif // !TRACY_SPIRVQUATERNION_H
