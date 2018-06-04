#include "RenderObject.h"
#include "..\SPIRVShaderFactory\CommonBufferSourceNames.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

RenderObject::RenderObject(const TRenderObjectFlags _kFlags) :
	BufferSource(m_mTransform, Spear::BufferSources::kObjectWorldMatrix),
	TRenderObjectFlags(_kFlags),
	m_BufferSources(1u, this)
{
}
//---------------------------------------------------------------------------------------------------

RenderObject::~RenderObject()
{
	Reset();
}
//---------------------------------------------------------------------------------------------------

void RenderObject::Reset()
{
	m_Node.Material.Reset();
	m_Node.Mesh.Reset();
	m_BufferSources = { this };
	ResetFlag();

	// todo reset buffer sources
}
//---------------------------------------------------------------------------------------------------
bool RenderObject::Initialize(const RenderObjectDesc& _Desc, const THandle _hDevice)
{
	// todo: load from file
	if (_Desc.bLoadByFile)
	{
	
	}
	else
	{
		SetFlag(_Desc.kRenderFlags);

		if (m_Node.Material.Load(_Desc.Material, _hDevice) == false)
			return false;

		if (m_Node.Mesh.Load(_Desc.Mesh, _hDevice) == false)
			return false;

		m_AABB = _Desc.BoundingBox;
		m_vPosition = _Desc.vPosition;
		m_vScale = _Desc.vScale;
		m_vOrientation = _Desc.vOrientation;
	}

	// finalize buffer source
	// Finalize();

	return true;
}
//---------------------------------------------------------------------------------------------------
void RenderObject::AddBufferSource(BufferSource* _pSource)
{
	m_BufferSources.push_back(_pSource);
}
//---------------------------------------------------------------------------------------------------
