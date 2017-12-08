#ifndef TRACY_VULKANRENDERPASS_H
#define TRACY_VULKANRENDERPASS_H

#include "IShaderFactoryConsumer.h"

namespace Tracy
{
	class VulkanRenderPass : public IShaderFactoryConsumer
	{
	public:
		VulkanRenderPass(const std::wstring& _sPassName, const std::wstring& _sLibName, const std::wstring& _sFactory, const THandle _hDevice = 0);
		~VulkanRenderPass();

	private:
		void OnFactoryLoaded() final {}
		void OnFactoryUnloaded() final {}

		void CreatePipeline();

	private:
		const std::wstring m_sPassName;
	};

} // Tracy

#endif // !TRACY_VULKANRENDERPASS_H
