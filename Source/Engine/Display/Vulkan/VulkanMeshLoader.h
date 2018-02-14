#ifndef TRACY_VULKANMESHLOADER_H
#define TRACY_VULKANMESHLOADER_H

#include "Display\RenderObjectDescription.h"

namespace Tracy
{
	// forward decl
	class GPUBuffer;

	class VulkanMeshLoader
	{
	public:
		static VulkanMeshLoader& Instance()
		{
			static VulkanMeshLoader Loader;
			return Loader;
		}

		VulkanMeshLoader();
		~VulkanMeshLoader();

		bool Load(const MeshDesc& _InDesc, MeshDesc& _OutDesc, GPUBuffer& _VertexBuffer, GPUBuffer& _IndexBuffer, const THandle _hDevice = 0u);

	private:

	};

} // Tracy
#endif // !TRACY_VULKANMESHLOADER_H
