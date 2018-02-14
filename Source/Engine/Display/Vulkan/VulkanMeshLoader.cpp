#include "VulkanMeshLoader.h"
#include "VulkanBuffer.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

VulkanMeshLoader::VulkanMeshLoader()
{
}
//---------------------------------------------------------------------------------------------------

VulkanMeshLoader::~VulkanMeshLoader()
{
}
//---------------------------------------------------------------------------------------------------

bool VulkanMeshLoader::Load(const MeshDesc& _InDesc, MeshDesc& _OutDesc, GPUBuffer& _VertexBuffer, GPUBuffer& _IndexBuffer, const THandle _hDevice)
{
	// TODO: load from file & caching etc
	if (_InDesc.bLoadByFile)
	{
		// todo: lookup mesh in unordered map, create if not loaded yet, return reference
	}
	else
	{
		if (_InDesc.pVBuffer != nullptr)
		{
			BufferDesc VDesc{};
			VDesc.hDevice = _hDevice;
			VDesc.kAccessFlag = kResourceAccess_CPUVisible; // todo: staging buffer
			VDesc.kUsageFlag = kBufferUsage_Vertex;
			VDesc.uInitialDataOffset = 0u;
			VDesc.uInitialDataSize = static_cast<uint32_t>(_InDesc.pVBuffer->size());
			VDesc.pInitialData = _InDesc.pVBuffer->data();
			VDesc.uSize = VDesc.uInitialDataSize;
			_VertexBuffer = std::move(VulkanBuffer(VDesc));

			if (!_VertexBuffer)
				return false;
		}

		if (_InDesc.pIBuffer != nullptr)
		{
			BufferDesc IDesc{};
			IDesc.hDevice = _hDevice;
			IDesc.kAccessFlag = kResourceAccess_CPUVisible; // todo: staging buffer
			IDesc.kUsageFlag = kBufferUsage_Index;
			IDesc.uInitialDataOffset = 0u;
			IDesc.uInitialDataSize = static_cast<uint32_t>(_InDesc.pIBuffer->size());
			IDesc.pInitialData = _InDesc.pIBuffer->data();
			IDesc.uSize = IDesc.uInitialDataSize;
			_IndexBuffer = std::move(VulkanBuffer(IDesc));

			if (!_IndexBuffer)
				return false;
		}

		_OutDesc.kDrawMode = _InDesc.kDrawMode;
		_OutDesc.uVertexCount = _InDesc.uVertexCount;
		_OutDesc.uFirstVertex = _InDesc.uFirstVertex;
		_OutDesc.uVertexOffset = _InDesc.uVertexOffset;
		_OutDesc.uIndexCount = _InDesc.uIndexCount;
		_OutDesc.uFirstIndex = _InDesc.uFirstIndex;
		_OutDesc.kIndexType = _InDesc.kIndexType;
		_OutDesc.uIndexOffset = _InDesc.uIndexOffset;
		_OutDesc.uInstanceCount = _InDesc.uInstanceCount;
		_OutDesc.uFirstInstance = _InDesc.uFirstInstance;

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------
