#ifndef TRACY_SHADERFACTORYLOADER_H
#define TRACY_SHADERFACTORYLOADER_H

#ifdef STANDARD_DLL
#include <dll>
namespace dll = std::dll;
#else
#include <boost\dll.hpp>
namespace dll = boost::dll;
#endif

#include "..\SPIRVShaderFactory\ShaderFactory.h"
#include <unordered_map>

namespace Tracy
{
	class ShaderFactoryLoader
	{
	public:
		ShaderFactoryLoader();
		~ShaderFactoryLoader();

		bool Load(const std::string& _sLibPath);

	private:
		std::unordered_map<std::string, TGetFactoryRetType> m_ShaderFactories;
	};
} // Tracy

#endif // !TRACY_SHADERFACTORYLOADER_H
