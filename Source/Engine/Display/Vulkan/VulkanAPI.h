#ifndef VULKANAPI_H
#define VULKANAPI_H

#if defined(_WIN32) || defined(WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <vulkan/vulkan.hpp>
#include "Logger.h"

template <class ...Args>
inline vk::Result LogVKError(const vk::Result _kResult, const wchar_t* _pFormat = nullptr, Args&& ..._Args)
{
	if (_kResult != vk::Result::eSuccess)
	{
		std::wstring sError = hlx::to_wstring(vk::to_string(_kResult));
		HERROR("VulkanError: %s [%s]", sError.c_str(), _pFormat, _Args...);
	}

	return _kResult;
}

template <class ...Args>
inline bool LogVKErrorBool(const vk::Result _kResult, const wchar_t* _pFormat = nullptr, Args&& ..._Args)
{
	return LogVKError(_kResult, _pFormat, _Args...) == vk::Result::eSuccess;
}

template <class ...Args>
inline bool LogVKErrorFailed(const vk::Result _kResult, const wchar_t* _pFormat = nullptr, Args&& ..._Args)
{
	return LogVKError(_kResult, _pFormat, _Args...) != vk::Result::eSuccess;
}

#endif // !VULKANAPI_H
