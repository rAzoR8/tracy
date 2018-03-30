#ifndef TRACY_MATERIALINTERFACE_H
#define TRACY_MATERIALINTERFACE_H

#include "SPIRVVariable.h"

namespace Tracy
{
	// a material is just some entity that evaluates to some spectrum
	template <bool Assemble>
	class IMaterialInterface
	{
		virtual var_t<float3_t, Assemble, spv::StorageClassFunction> Eval() const = 0;
	};
} // Tracy

#endif // !TRACY_MATERIALINTERFACE_H
