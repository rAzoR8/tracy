#include "Scene.h"
#include "Display\RenderObject.h"
#include "Camera.h"
#include "Intersection.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

Scene::Scene()
{
}
//---------------------------------------------------------------------------------------------------

Scene::~Scene()
{
}
//---------------------------------------------------------------------------------------------------

bool Scene::Initialize(const SceneDesc & _Desc)
{
	return false;
}
//---------------------------------------------------------------------------------------------------

void Scene::Gather(Camera& _Camera)
{
	// for testing

	for (RenderObject* pObject : m_Objects)
	{
		if (pObject->CheckPass(_Camera.GetPassIDs()))
		{
			if (Intersects(_Camera.GetFrustum(), pObject->GetAABB()))
			{
				// add to camera
			}
		}
	}

}
//---------------------------------------------------------------------------------------------------
