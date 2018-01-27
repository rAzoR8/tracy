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

bool Scene::Initialize(const SceneDesc& _Desc)
{
	// we need to initialize static transforms once
	UpdateTransforms(false);
	return true;
}

//---------------------------------------------------------------------------------------------------

void Scene::Update()
{
	UpdateTransforms();

	// todo: update octree and stuff
}
//---------------------------------------------------------------------------------------------------

inline void Scene::AddObject(RenderObject* _pObject, Camera& _Camera, const bool _bAddChildObjects)
{
	if (_pObject->CheckFlag(kRenderObjectFlag_Invisible) == false &&
		_pObject->GetNode().Material &&
		_pObject->CheckPass(_Camera.GetPassIDs()))
	{
		if (Intersects(_Camera.GetFrustum(), _pObject->GetAABB()))
		{
			_Camera.AddObject(_pObject);

			if (_bAddChildObjects)
			{
				for (RenderObject* pChild : _pObject->GetChildren())
				{
					AddObject(pChild, _Camera, _bAddChildObjects);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------------------------------

void Scene::Gather(Camera& _Camera)
{
	// if we want multiple scenes to be gathered in one camera, this needs to be removed
	_Camera.ClearObjects();
	
	// for testing
	for (RenderObject* pObject : m_Objects)
	{
		AddObject(pObject, _Camera);
	}

	_Camera.SortObjects();
}
//---------------------------------------------------------------------------------------------------

void Scene::UpdateTransforms(const bool _bSkipStaticTransforms)
{
	// todo: parallel
	std::for_each(m_Objects.begin(), m_Objects.end(), [_bSkipStaticTransforms](RenderObject* _pObject)
	{
		if (_bSkipStaticTransforms == false || _pObject->CheckFlag(kRenderObjectFlag_StaticTransform) == false)
		{
			_pObject->ComputeTransform();
		}
	});
}

//---------------------------------------------------------------------------------------------------
