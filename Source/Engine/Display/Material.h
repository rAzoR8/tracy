#ifndef TRACY_MATERIAL_H
#define TRACY_MATERIAL_H

#include "ImageSource.h"
#include "Datastructures\BinaryKeyValueBufferSource.h"
#include <array>

namespace Tracy
{
	struct MaterialRefEntry
	{
		uint64_t uPassId = 0u; // renderpasse this material uses

		// not sure if this is the right place
		std::array<ShaderID, kShaderType_NumOf> Shaders; // todo userdata

		BinaryKeyValueBufferSource Values;
		ImageSource Images;
	};

	class Material : public RefCounted<MaterialRefEntry, true>
	{
	public:
		//Material() {};
		virtual ~Material() {};

		REFCOUNT_INTERFACE(Material, RefCountedType);

	private:
		
	};

	inline bool MaterialEntryCompare(const MaterialRefEntry& l, const MaterialRefEntry& r)
	{
		if (l.uPassId == r.uPassId)
		{
			for (size_t i = 0; i < kShaderType_NumOf; ++i)
			{
				if (l.Shaders[i].uID < r.Shaders[i].uID)
					return true;
			}

			return false;
		}

		return l.uPassId < r.uPassId;
	}

	//default compare
	inline bool MaterialCompare(const Material& l, const Material& r)
	{
		if (l && r)
		{
			return MaterialEntryCompare(l.Get(), r.Get());
		}

		// l is leser if r is valid but l is not
		return r && !l;
	}
} // Tracy

#endif // !TRACY_MATERIAL_H
