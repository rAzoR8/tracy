#include "Camera.h"
#include "Display\RenderObject.h"
#include <algorithm>

using namespace Tracy;

void Camera::SortObjects()
{
	std::sort(m_Objects.begin(), m_Objects.end(), [&](const RenderObject* pObj1, const RenderObject* pObj2)
	{
		const float fD1 = glm::distance(pObj1->GetPosition(), m_vPosition);
		const float fD2 = glm::distance(pObj2->GetPosition(), m_vPosition);

		return MaterialCompare(pObj1->GetNode().Material, fD1, pObj2->GetNode().Material, fD2);
	});
}