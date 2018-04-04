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
		CSGObject(const SDFObject<Assemble>* _pSource = nullptr);
		CSGObject(const CSGObject<Assemble>* _pLeft, const CSGObject<Assemble>* _pRight = nullptr);
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
		const SDFObject<Assemble>* m_pSource;
		const CSGObject<Assemble>* m_pLeft;
		const CSGObject<Assemble>* m_pRight;
	};
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	inline CSGObject<Assemble>::CSGObject(const SDFObject<Assemble>* _pSource) :
		m_pSource(_pSource), m_pLeft(nullptr), m_pRight(nullptr)
	{
	}

	template<bool Assemble>
	inline CSGObject<Assemble>::CSGObject(const CSGObject<Assemble>* _pLeft, const CSGObject<Assemble>* _pRight) :
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
	inline UnionCSGObject<Assemble> operator&(const CSGObject<Assemble>& l, const CSGObject<Assemble>& r)
	{
		return UnionCSGObject<Assemble>(&l, &r);
	}

	template <bool Assemble>
	inline DifferenceCSGObject<Assemble> operator/(const CSGObject<Assemble>& l, const CSGObject<Assemble>& r)
	{
		return DifferenceCSGObject<Assemble>(&l, &r);
	}

	template <bool Assemble>
	inline IntersectCSGObject<Assemble> operator|(const CSGObject<Assemble>& l, const CSGObject<Assemble>& r)
	{
		return IntersectCSGObject<Assemble>(&l, &r);
	}

	//---------------------------------------------------------------------------------------------------


	// Translate by offset
	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	class TranslateCSGObject : public CSGObject<Assemble>
	{
	public:
		TranslateCSGObject(const float3_t& _vOffset, const SDFObject<Assemble>* _pSource = nullptr) : CSGObject<Assemble>(_pSource), vOffset(_vOffset) {};
		TranslateCSGObject(const float3_t& _vOffset, const CSGObject<Assemble>* _pLeft, const CSGObject<Assemble>* _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), vOffset(_vOffset) {};
		
		template<spv::StorageClass C1>
		TranslateCSGObject(const var_t<float3_t, Assemble, C1>& _vOffset, const SDFObject<Assemble>* _pSource = nullptr) : CSGObject<Assemble>(_pSource), vOffset(_vOffset) {};
		template<spv::StorageClass C1>
		TranslateCSGObject(const var_t<float3_t, Assemble, C1>& _vOffset, const CSGObject<Assemble>* _pLeft, const CSGObject<Assemble>* _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), vOffset(_vOffset) {};
		
		virtual ~TranslateCSGObject(){}

		inline var_t<float3_t, Assemble, spv::StorageClassFunction> PreEval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final { return _Point - vOffset; };

	private:
		var_t<float3_t, Assemble, Class> vOffset;
	};

	//---------------------------------------------------------------------------------------------------

	// translate CSG by offset
	template <bool Assemble, spv::StorageClass C1>
	inline TranslateCSGObject<Assemble> operator+(const CSGObject<Assemble>& l, const var_t<float3_t, Assemble, C1>& r)
	{
		return TranslateCSGObject<Assemble>(r, &l);
	}

	template <bool Assemble>
	inline TranslateCSGObject<Assemble> operator+(const CSGObject<Assemble>& l, const float3_t& r)
	{
		return TranslateCSGObject<Assemble>(r, &l);
	}

	template <bool Assemble, spv::StorageClass C1>
	inline TranslateCSGObject<Assemble> operator+(const var_t<float3_t, Assemble, C1>& l, const CSGObject<Assemble>& r)
	{
		return TranslateCSGObject<Assemble>(l, &r);
	}

	template <bool Assemble>
	inline TranslateCSGObject<Assemble> operator+(const float3_t& l, const CSGObject<Assemble>& r)
	{
		return TranslateCSGObject<Assemble>(l, &r);
	}

	//---------------------------------------------------------------------------------------------------

	// SDF translate
	template <bool Assemble, spv::StorageClass C1>
	inline TranslateCSGObject<Assemble> operator+(const SDFObject<Assemble>& l, const var_t<float3_t, Assemble, C1>& r)
	{
		return TranslateCSGObject<Assemble>(r, &l);
	}

	template <bool Assemble>
	inline TranslateCSGObject<Assemble> operator+(const SDFObject<Assemble>& l, const float3_t& r)
	{
		return TranslateCSGObject<Assemble>(r, &l);
	}

	template <bool Assemble, spv::StorageClass C1>
	inline TranslateCSGObject<Assemble> operator+(const var_t<float3_t, Assemble, C1>& l, const SDFObject<Assemble>& r)
	{
		return TranslateCSGObject<Assemble>(l, &r);
	}

	template <bool Assemble>
	inline TranslateCSGObject<Assemble> operator+(const float3_t& l, const SDFObject<Assemble>& r)
	{
		return TranslateCSGObject<Assemble>(l, &r);
	}

	//---------------------------------------------------------------------------------------------------

	// Scale
	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	class UniformScaleCSGObject : public CSGObject<Assemble>
	{
	public:
		UniformScaleCSGObject(const float& _fScale, const SDFObject<Assemble>* _pSource = nullptr) : CSGObject<Assemble>(_pSource), fScale(_fScale) {};
		UniformScaleCSGObject(const float& _fScale, const CSGObject<Assemble>* _pLeft, const CSGObject<Assemble>* _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), fScale(_fScale) {};

		template <spv::StorageClass C1>
		UniformScaleCSGObject(const var_t<float, Assemble, C1>& _fScale, const SDFObject<Assemble>* _pSource = nullptr) : CSGObject<Assemble>(_pSource), fScale(_fScale) {};
		template <spv::StorageClass C1>
		UniformScaleCSGObject(const var_t<float, Assemble, C1>& _fScale, const CSGObject<Assemble>* _pLeft, const CSGObject<Assemble>* _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), fScale(_fScale) {};

		virtual ~UniformScaleCSGObject() {}

		inline var_t<float3_t, Assemble, spv::StorageClassFunction> PreEval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final { return _Point / fScale; };
		inline var_t<float, Assemble, spv::StorageClassFunction> PostEval(const var_t<float, Assemble, spv::StorageClassFunction>& _fDist) const final { return _fDist * fScale; };

	private:
		var_t<float, Assemble, Class> fScale;
	};

	//---------------------------------------------------------------------------------------------------

	// scale CSG by factor
	template <bool Assemble, spv::StorageClass C1>
	inline UniformScaleCSGObject<Assemble> operator*(const CSGObject<Assemble>& l, const var_t<float, Assemble, C1>& r)
	{
		return UniformScaleCSGObject<Assemble>(r, &l);
	}

	template <bool Assemble>
	inline UniformScaleCSGObject<Assemble> operator*(const CSGObject<Assemble>& l, const float& r)
	{
		return UniformScaleCSGObject<Assemble>(r, &l);
	}

	template <bool Assemble, spv::StorageClass C1>
	inline UniformScaleCSGObject<Assemble> operator*(const var_t<float, Assemble, C1>& l, const CSGObject<Assemble>& r)
	{
		return UniformScaleCSGObject<Assemble>(l, &r);
	}

	template <bool Assemble>
	inline UniformScaleCSGObject<Assemble> operator*(const float& l, const CSGObject<Assemble>& r)
	{
		return UniformScaleCSGObject<Assemble>(l, &r);
	}

	//---------------------------------------------------------------------------------------------------

	// SDF translate
	template <bool Assemble, spv::StorageClass C1>
	inline UniformScaleCSGObject<Assemble> operator*(const SDFObject<Assemble>& l, const var_t<float, Assemble, C1>& r)
	{
		return UniformScaleCSGObject<Assemble>(r, &l);
	}

	template <bool Assemble>
	inline UniformScaleCSGObject<Assemble> operator*(const SDFObject<Assemble>& l, const float& r)
	{
		return UniformScaleCSGObject<Assemble>(r, &l);
	}

	template <bool Assemble, spv::StorageClass C1>
	inline UniformScaleCSGObject<Assemble> operator*(const var_t<float, Assemble, C1>& l, const SDFObject<Assemble>& r)
	{
		return UniformScaleCSGObject<Assemble>(l, &r);
	}

	template <bool Assemble>
	inline UniformScaleCSGObject<Assemble> operator*(const float& l, const SDFObject<Assemble>& r)
	{
		return UniformScaleCSGObject<Assemble>(l, &r);
	}


	//---------------------------------------------------------------------------------------------------
	template <bool Assemble>
	class CSGScene
	{
	public:
		CSGScene(std::initializer_list<const CSGObject<Assemble>* > _Objects = {}) : m_Objects(_Objects) {}
		CSGScene(std::vector<const CSGObject<Assemble>* > _Objects) : m_Objects(_Objects) {}

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
		std::vector<const CSGObject<Assemble>*> m_Objects;
	};

	//---------------------------------------------------------------------------------------------------

} // Tracy

#endif // !TRACY_CSGOBJECT_H
