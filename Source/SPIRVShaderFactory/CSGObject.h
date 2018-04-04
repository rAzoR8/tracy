#ifndef TRACY_CSGOBJECT_H
#define TRACY_CSGOBJECT_H

#include "SDFObject.h"

namespace Tracy
{
	// https://www.alanzucconi.com/2016/07/01/signed-distance-functions/#part6
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> IntersectSDF(const var_t<float, Assemble, C1>& _lDist, const var_t<float, Assemble, C2>& _rDist)
	{
		return Max(_lDist, _rDist);
	}

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> UnionSDF(const var_t<float, Assemble, C1>& _lDist, const var_t<float, Assemble, C2>& _rDist)
	{
		return Min(_lDist, _rDist);
	}

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> DifferenceSDF(const var_t<float, Assemble, C1>& _lDist, const var_t<float, Assemble, C2>& _rDist)
	{
		return Max(_lDist, -_rDist);
	}

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	class CSGObject
	{
	public:
		static constexpr bool AssembleParam = Assemble;

		CSGObject(const std::shared_ptr<SDFObject<Assemble>>& _pSource = nullptr);
		CSGObject(const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight = nullptr);
		virtual ~CSGObject() {};

		// override to implement offset, rotation, scale
		virtual var_t<float3_t, Assemble, spv::StorageClassFunction> PreEval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const { return _Point; };
		virtual var_t<float, Assemble, spv::StorageClassFunction> PostEval(const var_t<float, Assemble, spv::StorageClassFunction>& _Dist) const { return _Dist; };
		virtual var_t<float, Assemble, spv::StorageClassFunction> Construct(const var_t<float, Assemble, spv::StorageClassFunction>& _lDist, const var_t<float, Assemble, spv::StorageClassFunction>& _rDist) const;

		template <spv::StorageClass C1>
		var_t<float, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, C1>& _Point) const;

		template <spv::StorageClass C1, spv::StorageClass C2>
		var_t<float3_t, Assemble, spv::StorageClassFunction> Normal(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float, Assemble, C2>& _Epsilon) const;

	private:
		std::shared_ptr<SDFObject<Assemble>> m_pSource;
		std::shared_ptr<CSGObject<Assemble>> m_pLeft;
		std::shared_ptr<CSGObject<Assemble>> m_pRight;
	};
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	inline CSGObject<Assemble>::CSGObject(const std::shared_ptr<SDFObject<Assemble>>& _pSource) :
		m_pSource(_pSource), m_pLeft(nullptr), m_pRight(nullptr)
	{
	}

	template<bool Assemble>
	inline CSGObject<Assemble>::CSGObject(const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight) :
		m_pSource(nullptr), m_pLeft(_pLeft), m_pRight(_pRight)
	{
		HASSERT(m_pLeft != nullptr || m_pRight != nullptr, "At least one child object must be valid!");
	}
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template <spv::StorageClass C1>
	inline var_t<float, Assemble, spv::StorageClassFunction> CSGObject<Assemble>::Eval(const var_t<float3_t, Assemble, C1>& _Point) const
	{
		auto vPoint = PreEval(make_intermediate(_Point));

		if (m_pLeft != nullptr && m_pRight != nullptr)
		{
			return PostEval(Construct(m_pLeft->Eval(vPoint), m_pRight->Eval(vPoint)));
		}
		else if (m_pLeft != nullptr && m_pRight == nullptr)
		{
			return PostEval(m_pLeft->Eval(vPoint)); // identity node
		}
		else if (m_pLeft == nullptr && m_pRight != nullptr)
		{
			return PostEval(m_pRight->Eval(vPoint)); // identity node
		}
		else if (m_pSource != nullptr)
		{
			return PostEval(m_pSource->Eval(vPoint)); // root / source node
		}
		else
		{
			return make_const<Assemble>(0.f); // invalid config
		}
	}

	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template<spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> CSGObject<Assemble>::Normal(const var_t<float3_t, Assemble, C1>& p, const var_t<float, Assemble, C2>& e) const
	{
		return ForwardDiffNormal(p, e, [&](const auto& v) {return this->Eval(v); });
	}

	//---------------------------------------------------------------------------------------------------
	// user has to override this function:

	template<bool Assemble>
	inline var_t<float, Assemble, spv::StorageClassFunction> CSGObject<Assemble>::Construct(const var_t<float, Assemble, spv::StorageClassFunction>& _lDist, const var_t<float, Assemble, spv::StorageClassFunction>& _rDist) const
	{
		return UnionSDF(_lDist, _rDist); // default to union impl
	}
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	using UnionCSGObject = CSGObject<Assemble>;

	// Intersection
	template <bool Assemble>
	class IntersectCSGObject : public CSGObject<Assemble>
	{
	public:
		using CSGObject::CSGObject;
		virtual ~IntersectCSGObject() {}

		inline var_t<float, Assemble, spv::StorageClassFunction> Construct(const var_t<float, Assemble, spv::StorageClassFunction>& _lDist, const var_t<float, Assemble, spv::StorageClassFunction>& _rDist) const final
		{
			return IntersectSDF(_lDist, _rDist);
		}
	};
	//---------------------------------------------------------------------------------------------------

	// Difference
	template <bool Assemble>
	class DifferenceCSGObject : public CSGObject<Assemble>
	{
	public:
		using CSGObject::CSGObject;
		virtual ~DifferenceCSGObject() {}

		inline var_t<float, Assemble, spv::StorageClassFunction> Construct(const var_t<float, Assemble, spv::StorageClassFunction>& _lDist, const var_t<float, Assemble, spv::StorageClassFunction>& _rDist) const final
		{
			return DifferenceSDF(_lDist, _rDist);
		}
	};
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	using TCSGObj = std::shared_ptr<CSGObject<Assemble>>;

	template <bool Assemble>
	using TUnionCSG = std::shared_ptr<CSGObject<Assemble>>;

	template <bool Assemble>
	using TIntersectionCSG = std::shared_ptr<IntersectCSGObject<Assemble>>;

	template <bool Assemble>
	using TDifferenceCSG = std::shared_ptr<DifferenceCSGObject<Assemble>>;

	// helper traits
	template<class T>
	constexpr bool derive_from_csg = std::is_base_of_v<CSGObject<true>, T> || std::is_base_of_v<CSGObject<false>, T>;

	template<class T>
	constexpr bool derive_from_sdf = std::is_base_of_v<SDFObject<true>, T> || std::is_base_of_v<SDFObject<false>, T>;

	template<class T>
	constexpr bool derive_from_obj = derive_from_sdf<T> || derive_from_csg<T>;

	//---------------------------------------------------------------------------------------------------

	template <class U, class V, typename = std::enable_if_t<derive_from_obj<U> && derive_from_obj<V>>>
	inline TUnionCSG<U::AssembleParam> operator&(const std::shared_ptr<U>& l, const std::shared_ptr<V>& r)
	{
		static_assert(U::AssembleParam == V::AssembleParam, "Assemble parameter mismatch");
		return std::make_shared<CSGObject<U::AssembleParam>>(l, r);
	}

	template <class U, class V, typename = std::enable_if_t<derive_from_obj<U> && derive_from_obj<V>>>
	inline TDifferenceCSG<U::AssembleParam> operator/(const std::shared_ptr<U>& l, const std::shared_ptr<V>& r)
	{
		static_assert(U::AssembleParam == V::AssembleParam, "Assemble parameter mismatch");
		return std::make_shared<DifferenceCSGObject<U::AssembleParam>>(l, r);
	}

	template <class U, class V, typename = std::enable_if_t<derive_from_obj<U> && derive_from_obj<V>>>
	inline TIntersectionCSG<U::AssembleParam> operator|(const std::shared_ptr<U>& l, const std::shared_ptr<V>& r)
	{
		static_assert(U::AssembleParam == V::AssembleParam, "Assemble parameter mismatch");
		return std::make_shared<IntersectCSGObject<U::AssembleParam>>(l, r);
	}

	//---------------------------------------------------------------------------------------------------

	// Translate by offset
	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	class TranslateCSGObject : public CSGObject<Assemble>
	{
	public:
		TranslateCSGObject(const float3_t& _vOffset, const std::shared_ptr<SDFObject<Assemble>>& _pSource = nullptr) : CSGObject<Assemble>(_pSource), vOffset(_vOffset) {};
		TranslateCSGObject(const float3_t& _vOffset, const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), vOffset(_vOffset) {};
		
		template<spv::StorageClass C1>
		TranslateCSGObject(const var_t<float3_t, Assemble, C1>& _vOffset, const std::shared_ptr<SDFObject<Assemble>>& _pSource = nullptr) : CSGObject<Assemble>(_pSource), vOffset(_vOffset) {};
		template<spv::StorageClass C1>
		TranslateCSGObject(const var_t<float3_t, Assemble, C1>& _vOffset, const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), vOffset(_vOffset) {};
		
		virtual ~TranslateCSGObject(){}

		inline var_t<float3_t, Assemble, spv::StorageClassFunction> PreEval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final { return _Point - vOffset; };

	private:
		var_t<float3_t, Assemble, Class> vOffset;
	};

	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	using TTranslateCSG = std::shared_ptr<TranslateCSGObject<Assemble, Class>>;

	//---------------------------------------------------------------------------------------------------

	// translate CSG by offset
	template <bool Assemble, spv::StorageClass C1, class T, typename = std::enable_if_t<std::is_base_of_v<CSGObject<Assemble>, T> || std::is_base_of_v<SDFObject<Assemble>, T>>>
	inline TTranslateCSG<Assemble> operator+(const std::shared_ptr<T>& l, const var_t<float3_t, Assemble, C1>& r)
	{
		return std::make_shared<TranslateCSGObject<Assemble>>(r, l);
	}

	template <class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TTranslateCSG<T::AssembleParam> operator+(const std::shared_ptr<T>& l, const float3_t& r)
	{
		return std::make_shared<TranslateCSGObject<T::AssembleParam>>(r, l);
	}

	template <bool Assemble, spv::StorageClass C1, class T, typename = std::enable_if_t<std::is_base_of_v<CSGObject<Assemble>, T> || std::is_base_of_v<SDFObject<Assemble>, T>>>
	inline TTranslateCSG<Assemble> operator+(const var_t<float3_t, Assemble, C1>& l, const std::shared_ptr<T>& r)
	{
		return std::make_shared<TranslateCSGObject<Assemble>>(l, r);
	}

	template <class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TTranslateCSG<T::AssembleParam> operator+(const float3_t& l, const std::shared_ptr<T>& r)
	{
		return std::make_shared<TranslateCSGObject<T::T::AssembleParam>>(l, r);
	}

	//---------------------------------------------------------------------------------------------------

	// Scale
	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	class UniformScaleCSGObject : public CSGObject<Assemble>
	{
	public:
		UniformScaleCSGObject(const float& _fScale, const std::shared_ptr<SDFObject<Assemble>>& _pSource = nullptr) : CSGObject<Assemble>(_pSource), fScale(_fScale) {};
		UniformScaleCSGObject(const float& _fScale, const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), fScale(_fScale) {};

		template <spv::StorageClass C1>
		UniformScaleCSGObject(const var_t<float, Assemble, C1>& _fScale, const std::shared_ptr<SDFObject<Assemble>>& _pSource = nullptr) : CSGObject<Assemble>(_pSource), fScale(_fScale) {};
		template <spv::StorageClass C1>
		UniformScaleCSGObject(const var_t<float, Assemble, C1>& _fScale, const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), fScale(_fScale) {};

		virtual ~UniformScaleCSGObject() {}

		inline var_t<float3_t, Assemble, spv::StorageClassFunction> PreEval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final { return _Point / fScale; };
		inline var_t<float, Assemble, spv::StorageClassFunction> PostEval(const var_t<float, Assemble, spv::StorageClassFunction>& _fDist) const final { return _fDist * fScale; };

	private:
		var_t<float, Assemble, Class> fScale;
	};

	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	using TUniformScaleCSG = std::shared_ptr<UniformScaleCSGObject<Assemble, Class>>;

	//---------------------------------------------------------------------------------------------------

	// scale CSG by factor
	template <bool Assemble, spv::StorageClass C1, class T, typename = std::enable_if_t<std::is_base_of_v<CSGObject<Assemble>, T> || std::is_base_of_v<SDFObject<Assemble>, T>>>
	inline TUniformScaleCSG<Assemble> operator*(const std::shared_ptr<T>& l, const var_t<float, Assemble, C1>& r)
	{
		return std::make_shared<UniformScaleCSGObject<Assemble>>(r, l);
	}

	template <class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TUniformScaleCSG<T::AssembleParam> operator*(const std::shared_ptr<T>& l, const float& r)
	{
		return std::make_shared<UniformScaleCSGObject<T::AssembleParam>>(r, l);
	}

	template <bool Assemble, spv::StorageClass C1, class T, typename = std::enable_if_t<std::is_base_of_v<CSGObject<Assemble>, T> || std::is_base_of_v<SDFObject<Assemble>, T>>>
	inline TUniformScaleCSG<Assemble> operator*(const var_t<float, Assemble, C1>& l, const std::shared_ptr<T>& r)
	{
		return std::make_shared<UniformScaleCSGObject<Assemble>>(l, r);
	}

	template <class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TUniformScaleCSG<T::AssembleParam> operator*(const float& l, const std::shared_ptr<T>& r)
	{
		return std::make_shared<UniformScaleCSGObject<T::AssembleParam>>(l, r);
	}

	//---------------------------------------------------------------------------------------------------

	// Rotation
	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	class RotationCSGObject : public CSGObject<Assemble>
	{
	public:
		RotationCSGObject(const float4_t& _vRotation, const std::shared_ptr<SDFObject<Assemble>>& _pSource = nullptr) : CSGObject<Assemble>(_pSource), vRotation(_vRotation) {};
		RotationCSGObject(const float4_t& _vRotation, const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), vRotation(_vRotation) {};

		template <spv::StorageClass C1>
		RotationCSGObject(const SPIRVQuaternion<Assemble, C1>& _vRotation, const std::shared_ptr<SDFObject<Assemble>>& _pSource = nullptr) : CSGObject<Assemble>(_pSource), vRotation(_vRotation) {};
		template <spv::StorageClass C1>
		RotationCSGObject(const SPIRVQuaternion<Assemble, C1>& _vRotation, const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), vRotation(_vRotation) {};

		virtual ~RotationCSGObject() {}

		inline var_t<float3_t, Assemble, spv::StorageClassFunction> PreEval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final { return vRotation.InverseRotateUnit(_Point); };

	private:
		SPIRVQuaternion<Assemble, Class> vRotation;
	};

	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	using TRotationCSG = std::shared_ptr<RotationCSGObject<Assemble, Class>>;

	//---------------------------------------------------------------------------------------------------

	// rotate CSG by unit quaternion
	template <bool Assemble, spv::StorageClass C1, class T, typename = std::enable_if_t<std::is_base_of_v<CSGObject<Assemble>, T> || std::is_base_of_v<SDFObject<Assemble>, T>>>
	inline TRotationCSG<Assemble> operator*(const std::shared_ptr<T>& l, const SPIRVQuaternion<Assemble, C1>& r)
	{
		return std::make_shared<RotationCSGObject<Assemble>>(r, l);
	}

	template <class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TRotationCSG<T::AssembleParam> operator*(const std::shared_ptr<T>& l, const float4_t& r)
	{
		return std::make_shared<RotationCSGObject<T::AssembleParam>>(r, l);
	}

	template <bool Assemble, spv::StorageClass C1, class T, typename = std::enable_if_t<std::is_base_of_v<CSGObject<Assemble>, T> || std::is_base_of_v<SDFObject<Assemble>, T>>>
	inline TRotationCSG<Assemble> operator*(const SPIRVQuaternion<Assemble, C1>& l, const std::shared_ptr<T>& r)
	{
		return std::make_shared<RotationCSGObject<Assemble>>(l, r);
	}

	template <class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TRotationCSG<T::AssembleParam> operator*(const float4_t& l, const std::shared_ptr<T>& r)
	{
		return std::make_shared<RotationCSGObject<T::AssembleParam>>(l, r);
	}
	
	//---------------------------------------------------------------------------------------------------
	// CSG SCENE
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	class CSGScene
	{
	public:
		CSGScene(std::initializer_list<std::shared_ptr<CSGObject<Assemble>>> _Objects = {}) : m_Objects(_Objects) {}
		CSGScene(const std::vector<std::shared_ptr<CSGObject<Assemble>>>& _Objects) : m_Objects(_Objects) {}

		virtual ~CSGScene() {}

		template <spv::StorageClass C1>
		inline var_t<float, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, C1>& _Point) const
		{
			HASSERT(m_Objects.empty() == false, "CSGScene is empty, nothing to be evaluated");

			auto dist = m_Objects.front()->Eval(_Point);

			for (uint32_t i = 1u; i < m_Objects.size(); ++i)
			{
				dist = UnionSDF(m_Objects[i]->Eval(_Point), dist);
			}

			return dist;
		}

		template <spv::StorageClass C1, spv::StorageClass C2>
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> Normal(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float, Assemble, C2>& _Epsilon) const
		{
			return ForwardDiffNormal(_Point, _Epsilon, [&](const auto& v) {return this->Eval(v); })
		}

	private:
		std::vector<std::shared_ptr<CSGObject<Assemble>>> m_Objects;
	};

	//---------------------------------------------------------------------------------------------------

} // Tracy

#endif // !TRACY_CSGOBJECT_H
