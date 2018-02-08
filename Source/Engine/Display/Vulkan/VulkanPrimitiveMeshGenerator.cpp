#include "VulkanPrimitiveMeshGenerator.h"
#include "Display\PrimitiveVertices.h"
#include "VulkanBuffer.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------

Mesh VulkanPrimitiveMeshGenerator::TriangleVertPos(const THandle _hDevice)
{
	BufferDesc Desc{};
	Desc.hDevice = _hDevice;
	Desc.kUsageFlag = kBufferUsage_Vertex;
	Desc.uSize = sizeof(TrianglePos);
	Desc.uInitialDataSize = sizeof(TrianglePos);
	Desc.pInitialData = TrianglePos;
	Desc.kAccessFlag = kResourceAccess_CPUVisible;

	return Mesh(std::move(VulkanBuffer(Desc)), 3u);
}
//---------------------------------------------------------------------------------------------------
