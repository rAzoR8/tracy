#include "Mesh.h"
#include "Vulkan\VulkanMeshLoader.h"
#include "Platform\IApplication.h"
#include "Logger.h"

using namespace Tracy;

Mesh::Mesh(const MeshDesc& _Desc)
{
	Load(_Desc);
}
//---------------------------------------------------------------------------------------------------

Mesh::~Mesh()
{ 
	Reset();
}
//---------------------------------------------------------------------------------------------------

void Mesh::Reset()
{
	m_IndexBuffer.Reset();
	m_VertexBuffer.Reset();
}
//---------------------------------------------------------------------------------------------------

bool Mesh::Load(const MeshDesc& _Desc, const THandle _hDevice)
{
	MeshDesc LoadedDesc;

	bool bSuccess = false;
	switch (ApplicationInfo::Instance().GetGfxAPI())
	{
	case kGraphicsAPI_Vulkan:
		bSuccess = VulkanMeshLoader::Instance().Load(_Desc, LoadedDesc, m_VertexBuffer, m_IndexBuffer, _hDevice);
		break;

	case kGraphicsAPI_D3D12:
	default:
		HFATAL("MeshLoader not implemented for this API");
		break;
	}

	if (bSuccess)
	{
		m_kDrawMode = LoadedDesc.kDrawMode;
		m_uVertexCount = LoadedDesc.uVertexCount;
		m_uFirstVertex = LoadedDesc.uFirstVertex;
		m_uVertexOffset = LoadedDesc.uVertexOffset;
		m_uIndexCount = LoadedDesc.uIndexCount;
		m_uFirstIndex = LoadedDesc.uFirstIndex;
		m_kIndexType = LoadedDesc.kIndexType;
		m_uIndexOffset = LoadedDesc.uIndexOffset;
		m_uInstanceCount = LoadedDesc.uInstanceCount;
		m_uFirstInstance = LoadedDesc.uFirstInstance;
	}

	return bSuccess;
}
//---------------------------------------------------------------------------------------------------
