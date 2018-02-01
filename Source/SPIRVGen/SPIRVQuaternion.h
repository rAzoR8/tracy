#ifndef TRACY_SPIRVQUATERNION_H
#define TRACY_SPIRVQUATERNION_H

#include "SPIRVOperatorImpl.h"

namespace Tracy
{
	template <bool Assemble = true, spv::StorageClass Class = spv::StorageClassFunction>
	struct SPIRVQuaternion : public var_t<quaternion_t, Assemble, Class>
	{
		using var_t::var_t;

		//template <spv::StorageClass C1>
		//SPIRVQuaternion& operator*=(const SPIRVQuaternion<Assemble, C1>& _Other) const;
	};

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline SPIRVQuaternion<Assemble, spv::StorageClassFunction> operator*(const SPIRVQuaternion<Assemble, C1>& q1, const SPIRVQuaternion<Assemble, C2>& q2)
	{
		auto var = SPIRVQuaternion<Assemble, spv::StorageClassFunction>(TIntermediate());
		if constexpr(Assemble == false)
		{
			var.Value = q1.Value; //glm
			//var.Value *= q2.Value;
		}
		else
		{
			//auto q1axis = q1.xyz;auto q1angle = q1.w;
			//auto q2axis = q2.xyz; auto q2angle = q2.w;
			//var.xyz = q2axis * q1angle + q1axis * q2angle + cross(q1axis, q2axis);
			//var.w = q1angle * q2angle - dot(q1axis, q2axis);
			//https://gist.github.com/mattatz/40a91588d5fb38240403f198a938a593
			//var.xyz = q2.xyz * q1.w + q1.xyz * q2.w + cross(q1.xyz, q2.xyz);
			//var.w = q1.w * q2.w - dot(q1.xyz, q2.xyz);
		}

		return var;
	}

	//template<bool Assemble, spv::StorageClass Class>
	//template<spv::StorageClass C1>
	//inline SPIRVQuaternion& SPIRVQuaternion<Assemble, Class>::operator*=(const SPIRVQuaternion<Assemble, C1>& _Other) const
	//{
	//	if constexpr(Assemble == false)
	//	{
	//		 
	//	}
	//	else
	//	{
	//	
	//	}

	//	return *this;
	//}
}//

#endif // !TRACY_SPIRVQUATERNION_H
