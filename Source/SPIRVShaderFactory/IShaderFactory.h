#ifndef SPEAR_ISHADERFACTORY_H
#define SPEAR_ISHADERFACTORY_H

#include "IPlugin.h"
#include "..\SPIRVGen\SPIRVModule.h"
#include "ShaderID.h"

namespace Spear
{
    class IShaderFactory : public hlx::IPlugin
    {
    public:
        virtual SPIRVModule GetModule(const ShaderID _uShaderIdentifier, const void* _pUserData = nullptr, const size_t _uSize = 0u) = 0;
    };
} // Spear

#endif // !SPEAR_ISHADERFACTORY_H
