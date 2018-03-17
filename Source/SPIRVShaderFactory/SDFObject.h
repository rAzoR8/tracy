#ifndef TRACY_SDFOBJECT_H
#define TRACY_SDFOBJECT_H

#include "SPIRVOperatorImpl.h"

namespace Tracy
{
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class EvalFunc>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> ForwardDiffNormal(const var_t<float3_t, Assemble, C1>& p, const var_t<float, Assemble, C2>& e, const EvalFunc& _Eval) const
	{
		using vec3 = var_t<float3_t, Assemble, spv::StorageClassFunction>;

		// use simple forward diff
		auto x = _Eval(vec3(p.x + e, p.y, p.z)) - _Eval(vec3(p.x - e, p.y, p.z));
		auto y = _Eval(vec3(p.x, p.y + e, p.z)) - _Eval(vec3(p.x, p.y - e, p.z));
		auto z = _Eval(vec3(p.x, p.y, p.z + e)) - _Eval(vec3(p.x, p.y, p.z - e));

		return Normalize(vec3(x, y, z));
	}

	//---------------------------------------------------------------------------------------------------

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> Sphere(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float, Assemble, C2>& _Radius)
	{
		return Dot(_Point, _Point) - _Radius * _Radius;
	}
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	class SDFObject
	{
	public:
		using vec3 = var_t<float3_t, Assemble, spv::StorageClassFunction>;

		SDFObject() {};
		virtual ~SDFObject() {};

		template <spv::StorageClass C1>
		var_t<float, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, C1>& _Point) const;

		template <spv::StorageClass C1, spv::StorageClass C2>
		var_t<float3_t, Assemble, spv::StorageClassFunction> Normal(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float, Assemble, C2>& _Epsilon) const;

	protected:
		// user has to override this function:
		virtual var_t<float, Assemble, spv::StorageClassFunction> Distance(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const
		{
			return Sphere(_Point, make_const<Assemble>(1.f)); // default impl unit sphere
		}
	};
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template<spv::StorageClass C1>
	inline var_t<float, Assemble, spv::StorageClassFunction> SDFObject<Assemble>::Eval(const var_t<float3_t, Assemble, C1>& _Point) const
	{
		return Distance(make_intermediate(_Point))
	}

	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template<spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> SDFObject<Assemble>::Normal(const var_t<float3_t, Assemble, C1>& p, const var_t<float, Assemble, C2>& e) const
	{
		const auto EvalFunc = [&](const vec3& v) {return this->Eval(v); };

		return ForwardDiffNormal(p, e, EvalFunc);

		//// use simple forward diff
		//auto x = Eval(vec3(p.x + e, p.y, p.z)) - Eval(vec3(p.x - e, p.y, p.z));
		//auto y = Eval(vec3(p.x, p.y + e, p.z)) - Eval(vec3(p.x, p.y - e, p.z));
		//auto z = Eval(vec3(p.x, p.y, p.z + e)) - Eval(vec3(p.x, p.y, p.z - e));

		//return Normalize(vec3(x, y , z));
	}

} // Tracy

#endif // !TRACY_SDFOBJECT_H
