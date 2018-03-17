#ifndef TRACY_CSGOBJECT_H
#define TRACY_CSGOBJECT_H

#include "SDFObject.h"

namespace Tracy
{
	// https://www.alanzucconi.com/2016/07/01/signed-distance-functions/#part6
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> IntersectSDF(const var_t<float, AssemblC1>& _lDist, const var_t<float, Assemble, C2>& _rDist) const
	{
		return Max(_lDist, _RDist);
	}

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> UnionSDF(const var_t<float, AssemblC1>& _lDist, const var_t<float, Assemble, C2>& _rDist) const
	{
		return Min(_lDist, _RDist);
	}

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> DifferenceSDF(const var_t<float, AssemblC1>& _lDist, const var_t<float, Assemble, C2>& _rDist) const
	{
		return Max(_lDist, _RDist * -1.f);
	}

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	class CSGObject
	{
	public:
		CSGObject(const SDFObject<Assemble>* _pSource = nullptr);
		CSGObject(const CSGObject<Assemble>* _pLeft, const CSGObject<Assemble>* _pRight = nullptr);
		virtual ~CSGObject() {};

		template <spv::StorageClass C1>
		var_t<float, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, C1>& _Point) const;

		template <spv::StorageClass C1, spv::StorageClass C2>
		var_t<float3_t, Assemble, spv::StorageClassFunction> Normal(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float, Assemble, C2>& _Epsilon) const;

	protected:
		virtual var_t<float, Assemble, spv::StorageClassFunction> Construct(const var_t<float, Assemble, spv::StorageClassFunction>& _lDist, const var_t<float, Assemble, spv::StorageClassFunction>& _rDist) const;

	private:
		const SDFObject<Assemble>* m_pSource;
		const CSGObject<Assemble>* m_pLeft;
		const CSGObject<Assemble>* m_pRight;

	};

	//---------------------------------------------------------------------------------------------------
	template <bool Assemble>
	class CSGScene
	{
		CSGScene(std::initializer_list<const CSGObject<Assemble*>> _Objects) : m_Objects(_Objects) {}
		CSGScene(std::vector<const CSGObject<Assemble*>> _Objects) : m_Objects(_Objects) {}

		virtual ~CSGScene() {}

		template <spv::StorageClass C1>
		inline var_t<float, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, C1>& _Point) const
		{
			var_t<float, Assemble, spv::StorageClassFunction> dist = 0.f;

			for (const auto pObj : _Objects)
			{
				dist = UnionSDF(pObj->Eval(_Point), dist);
			}

			return dist;
		}

		template <spv::StorageClass C1, spv::StorageClass C2>
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> Normal(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float, Assemble, C2>& _Epsilon) const
		{
			return ForwardDiffNormal(_Point, _Epsilon, [&](const auto& v) {return this->Eval(v); })
		}

	private:
		std::vector<const CSGObject<Assemble*>> m_Objects;
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
		if (m_pLeft != nullptr && m_pRight != nullptr)
		{
			return Construct(m_pLeft->Eval(_Point), m_pRight->Eval(_Point));
		}
		else if (m_pLeft != nullptr && m_pRight == nullptr)
		{
			return m_pLeft->Eval(_Point); // identity node
		}
		else if (m_pLeft == nullptr && m_pRight != nullptr)
		{
			return m_pRight->Eval(_Point); // identity node
		}
		else if (m_pSource != nullptr)
		{
			return m_pSource->Eval(_Point); // root / source node
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

} // Tracy

#endif // !TRACY_CSGOBJECT_H
