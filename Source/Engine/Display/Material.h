#ifndef TRACY_MATERIAL_H
#define TRACY_MATERIAL_H

#include "ImageSource.h"
#include "Datastructures\BinaryKeyValueBufferSource.h"

namespace Tracy
{
	struct MaterialRefEntry
	{
		uint64_t uPassIds = 0u; // renderpasses this material uses

		BinaryKeyValueBufferSource Values;
		ImageSource Images;
	};

	class Material : public RefCounted<MaterialRefEntry, true>
	{
	public:
		Material() {};
		virtual ~Material() {};

		REFCOUNT_INTERFACE(Material, RefCountedType);

	private:
		
	};
} // Tracy

#endif // !TRACY_MATERIAL_H
