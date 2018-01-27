#ifndef TRACY_TRANSFORM_H
#define TRACY_TRANSFORM_H

#include "Logger.h"
#include "MathTypes.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace Tracy
{
	template <class TNestedType>
	class Transform
	{
	public:
		Transform(
			const float3_t& _vPosition = {0.f, 0.f, 0.f},
			const quaternion_t& _vOrientation = {0.f, 0.f, 0.f, 0.f,},
			const float3_t& _vScale = {1.f, 1.f, 1.f}) :
		m_vPosition(_vPosition),
		m_vOrientation(_vOrientation),
		m_vScale(_vScale)
		{
			static_assert(std::is_base_of_v<Transform, TNestedType>, "Template argument must be derived type");
		};

		virtual ~Transform() {};

		// needs to be called before rendering
		const float4x4_t& ComputeTransform();

		// all in local space!
		inline const float3_t& GetPosition() const { return m_vPosition; };
		inline const float3_t& GetScale() const { return m_vScale; };
		inline const quaternion_t& GetOrientation() const { return m_vOrientation; };

		inline void SetPosition(const float3_t& _vPosition) { m_vPosition = _vPosition; }
		inline void SetScale(const float3_t& _vScale) { m_vScale = _vScale; }
		inline void SetOrientation(const quaternion_t& _vOrientation) { m_vOrientation = _vOrientation; }

		void AddChild(TNestedType* _pObject);
		const std::vector<TNestedType*>& GetChildren() const { return m_Children; };

	private:
		void SetParent(TNestedType* _pObject);

	protected:
		TNestedType* m_pParent = nullptr; // use for transform hierarchy
		std::vector<TNestedType*> m_Children;

		float3_t m_vPosition;
		float3_t m_vScale;
		quaternion_t m_vOrientation;

		float4x4_t m_mTransform;
	};

	//---------------------------------------------------------------------------------------------------

	template <class TNestedType>
	inline const float4x4_t& Transform<TNestedType>::ComputeTransform()
	{
		m_mTransform = glm::translate(m_vPosition) * glm::mat4_cast(m_vOrientation) * glm::scale(m_vScale);

		if (m_pParent != nullptr)
		{
			m_mTransform *= m_pParent->m_mTransform;
		}

		for (TNestedType* pChild : m_Children)
		{
			pChild->ComputeTransform();
		}

		return m_mTransform;
	}
	//---------------------------------------------------------------------------------------------------
	template <class TNestedType>
	inline void Transform<TNestedType>::AddChild(TNestedType* _pObject)
	{
		_pObject->SetParent(this);
		m_Children.push_back(_pObject);
	}
	//---------------------------------------------------------------------------------------------------
	template <class TNestedType>
	inline void Transform<TNestedType>::SetParent(TNestedType* _pObject)
	{
		HASSERT(m_pParent == nullptr, "Object already has a parent!");
		m_pParent = _pObject;
	}
	//---------------------------------------------------------------------------------------------------

} // Tracy

#endif // !TRACY_TRANSFORM_H
