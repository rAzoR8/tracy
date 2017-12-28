#ifndef TRACY_VULKANRENDERGRAPH_H
#define TRACY_VULKANRENDERGRAPH_H

#include "VulkanRenderPass.h"

namespace Tracy
{
	class VulkanRenderGraph
	{
	public:
		VulkanRenderGraph(const RenderGraphDesc& _Desc, const THandle _hDevice = 0u);
		~VulkanRenderGraph();

		bool Initialize();

		// TODO: pass cameras with active objects
		void Render();

		template <class ... TStrings>
		uint64_t GetMaterialIds(const std::wstring _sPassName, const TStrings& ..._Strings);

	private:
		const THandle m_hDevice;
		RenderGraphDesc m_Description;
		std::unordered_map<std::wstring, uint64_t> m_MaterialIds;

		std::vector<VulkanRenderPass*> m_StartPasses;
		std::vector<VulkanRenderPass> m_RenderPasses;
	};

	template<class ...TStrings>
	inline uint64_t VulkanRenderGraph::GetMaterialIds(const std::wstring _sPassName, const TStrings & ..._Strings)
	{
		uint64_t uMat = 0u;

		auto it = m_MaterialIds.find(_sPassName);

		if (it != m_MaterialIds.end())
		{
			uMat = it->second;
		}
		else
		{
			HERROR("Renderpass %s not found for material id lookup", _sPassName.c_str());
		}

		if constexpr(sizeof...(_Strings) > 0)
		{
			uMat |= GetMaterialIds(_Strings...);
		}

		return uMat;
	}
} // Tracy

#endif // !TRACY_VULKANRENDERGRAPH_H
