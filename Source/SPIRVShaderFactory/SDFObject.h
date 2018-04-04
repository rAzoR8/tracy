#ifndef TRACY_SDFOBJECT_H
#define TRACY_SDFOBJECT_H

#include "SPIRVOperatorImpl.h"

namespace Tracy
{
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class EvalFunc>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> ForwardDiffNormal(const var_t<float3_t, Assemble, C1>& p, const var_t<float, Assemble, C2>& e, const EvalFunc& _Eval)
	{
		using vec3 = var_t<float3_t, Assemble, spv::StorageClassFunction>;

		return Normalize(
			vec3(
				_Eval(vec3(p.x + e, p.y, p.z)) - _Eval(vec3(p.x - e, p.y, p.z)),
				_Eval(vec3(p.x, p.y + e, p.z)) - _Eval(vec3(p.x, p.y - e, p.z)),
				_Eval(vec3(p.x, p.y, p.z + e)) - _Eval(vec3(p.x, p.y, p.z - e))
			)
		);
	}

	//---------------------------------------------------------------------------------------------------

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> SphereDist(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float, Assemble, C2>& _Radius)
	{
		return Length(_Point) - _Radius;
	}

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> CubeDist(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float3_t, Assemble, C2>& _vExtents)
	{
		auto d = Abs(_Point) - _vExtents;
		return Min(0.f, Max(d.x, d.y, d.z)) + Length(Max(d, make_const<Assemble>(float3_t(0.f, 0.f, 0.f))));
	}

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	struct SDFObject
	{
		using vec3 = var_t<float3_t, Assemble, spv::StorageClassFunction>;

		SDFObject() {};
		virtual ~SDFObject() {};

		// user has to override this function:
		virtual var_t<float, Assemble, spv::StorageClassFunction> Distance(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const = 0;

		template <spv::StorageClass C1>
		inline var_t<float, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, C1>& _Point) const { return Distance(make_intermediate(_Point)); };

		template <spv::StorageClass C1, spv::StorageClass C2>
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> Normal(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float, Assemble, C2>& _Epsilon) const
		{
			return ForwardDiffNormal(_Point, _Epsilon, [&](const auto& v) {return this->Eval(v); });
		};	
	};

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	struct SphereSDF : public SDFObject<Assemble>
	{
		var_t<float, Assemble, Class> fRadius;
		SphereSDF(const float& _fRadius = 1.f) : fRadius(_fRadius) {}

		template <spv::StorageClass C1>
		SphereSDF(const var_t<float, Assemble, C1>& _fRadius) : fRadius(_fRadius) {}

		inline var_t<float, Assemble, spv::StorageClassFunction> Distance(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final
		{
			return SphereDist(_Point, fRadius); 
		}
	};

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	struct CubeSDF : public SDFObject<Assemble>
	{
		var_t<float3_t, Assemble, Class> vExtent;
		CubeSDF(const float3_t _vExtents = {1.f, 1.f, 1.f}) : vExtent(_vExtents) {}

		template <spv::StorageClass C1>
		CubeSDF(const var_t<float3_t, Assemble, C1>& _fRadius) : vExtent(_vExtents) {}

		inline var_t<float, Assemble, spv::StorageClassFunction> Distance(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final
		{
			return CubeDist(_Point, vExtent);
		}
		//---------------------------------------------------------------------------------------------------

	};
} // Tracy

#endif // !TRACY_SDFOBJECT_H
