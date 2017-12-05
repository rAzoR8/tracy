#ifndef TRACY_SHADERFACTORY_H
#define TRACY_SHADERFACTORY_H

#include "SPIRVModule.h"

#ifdef COMPILE_SHADERFACTROY_DLL
#define DLLINTERFACE  __declspec(dllexport) 
#else
#define DLLINTERFACE  __declspec(dllimport) 
#endif

namespace Tracy
{
	enum EShaderType : uint8_t
	{
		kShaderType_Vertex = 0,
		kShaderType_TessellationControl = 1,
		kShaderType_TessellationEvaluation = 2,
		kShaderType_Geometry = 3,
		kShaderType_Fragment = 4,
		kShaderType_GLCompute = 5,
		kShaderType_Kernel = 6,
		kShaderType_NumOf,
	};

	struct ShaderID 
	{
		ShaderID(const uint64_t _uID = 0u) : uID(_uID) {}
		ShaderID(const EShaderType _kType, const uint8_t _uCompileFlags, const uint16_t _uShader, const uint32_t _uVariant) :
			kType(_kType), uCompileFlags(_uCompileFlags), uShader(_uShader), uVariant(_uVariant){}
		ShaderID(const ShaderID& _Other) : uID(_Other.uID) {}

		union
		{
			struct
			{
				EShaderType kType; // 8
				uint8_t uCompileFlags; // debug, optimization etc
				uint16_t uShader; // which shader
				uint32_t uVariant; // which permutation of the shader
			};
			uint64_t uID;
		};

		operator uint64_t() const { return uID; }
	};

	class DLLINTERFACE IShaderFactory
	{
	public:
		IShaderFactory() {};
		virtual ~IShaderFactory() {};

		// TODO: maybe provide some info like: is threadsafe & caches modules

		virtual std::string GetIdentifier() const = 0;
		virtual SPIRVModule GetModule(const ShaderID _uShaderIdentifier, const void* _pUserData = nullptr, const size_t _uSize = 0u) = 0;

		virtual void Release() = 0;
	};
} // Tracy

#endif // !TRACY_SHADERFACTORY_H
