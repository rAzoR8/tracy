#include "Scene.h"
#include "Display/RenderObject.h"
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
	FreeObjects();
}

//---------------------------------------------------------------------------------------------------
void Scene::FreeObjects()
{
	for (RenderObject* pObject : m_Objects)
	{
		m_pObjectAllocator->Free(pObject);
	}

	m_Objects.resize(0);
}

//---------------------------------------------------------------------------------------------------

bool Scene::Initialize(const SceneDesc& _Desc, const THandle _hDevice)
{
	m_Objects.resize(0); //FreeObjects(); not needed, we create a new allocator anyways

	const uint32_t uBlockSize = 1024u;
	const uint32_t uBlockCount = std::max(static_cast<uint32_t>(std::ceil((_Desc.Objects.size() + _Desc.uMaxDynamicObjects) / uBlockSize)), 1u);
	const uint32_t uPreAllocedBlocks = 1u;
	m_pObjectAllocator = std::make_unique<TObjAllocator>(uBlockSize, uBlockCount, uPreAllocedBlocks);

	m_Objects.reserve(_Desc.Objects.size() + _Desc.uMaxDynamicObjects);

	for (const RenderObjectDesc& ObjDesc : _Desc.Objects)
	{
		RenderObject* pObject = m_pObjectAllocator->Alloc();
		if (pObject == nullptr)
		{
			HERROR("Failed to allocate renderobject %s", WCSTR(ObjDesc.sIdentifier));
			return false;
		}

		// TODO: init with custom functor
		if (pObject->Initialize(ObjDesc, _hDevice) == false)
		{
			HERROR("Failed to load renderobject %s", WCSTR(ObjDesc.sIdentifier));
			return false;
		}
	}

	// TODO: resovle transform hierachry

	// we need to initialize static transforms once
	UpdateTransforms(false);
	return true;
}

//---------------------------------------------------------------------------------------------------

void Scene::Update(const bool _bGatherCameras)
{
	UpdateTransforms();

	// todo: update octree and stuff

	if (_bGatherCameras)
	{
		// TODO: in parallel
		for (const std::shared_ptr<Camera>& pCamera : m_Cameras)
		{
			Gather(*pCamera);
		}
	}
}
//---------------------------------------------------------------------------------------------------

inline void Scene::AddObject(RenderObject* _pObject, Camera& _Camera, const bool _bAddChildObjects) const
{
	if (_pObject->CheckFlag(kRenderObjectFlag_Invisible) == false &&
		_pObject->GetNode().Material &&
		_pObject->CheckPass(_Camera.GetPassIDs()))
	{
		if (_pObject->CheckFlag(kRenderObjectFlag_SkipCulling) || 
			Intersects(_Camera.GetFrustum(), _pObject->GetAABB()))
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

void Scene::Gather(Camera& _Camera) const
{
	// if we want multiple scenes to be gathered in one camera, this needs to be removed
	_Camera.ClearObjects();
	_Camera.Update(); // generates frustum

	// for testing
	for (RenderObject* pObject : m_Objects)
	{
		AddObject(pObject, _Camera);
	}

	_Camera.SortObjects();
}
//---------------------------------------------------------------------------------------------------

void Scene::AddCamera(const std::shared_ptr<Camera>& _pCamera)
{
	m_Cameras.push_back(_pCamera);
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
