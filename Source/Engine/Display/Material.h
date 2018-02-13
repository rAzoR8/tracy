#ifndef TRACY_MATERIAL_H
#define TRACY_MATERIAL_H

#include "ImageSource.h"
#include "Datastructures\BinaryKeyValueBufferSource.h"
#include "RenderObjectDescription.h"
#include <array>

namespace Tracy
{
	struct MaterialRefEntry
	{
		MaterialRefEntry() {}
		virtual ~MaterialRefEntry() {}
		uint64_t uPassId = 0u; // renderpasses this material uses

		// not sure if this is the right place
		std::array<ShaderID, kShaderType_NumOf> Shaders; // todo userdata

		BinaryKeyValueBufferSource Values;
		ImageSource Images;
	};

	class Material : public RefCounted<MaterialRefEntry, true>
	{
	public:
		Material(const MaterialDesc& _Desc);
		virtual ~Material() {};

		REFCOUNT_INTERFACE(Material, RefCountedType);

	private:
		bool Load(const MaterialDesc& _Desc);
		
	};

	inline bool MaterialEntryCompare(const MaterialRefEntry& l, const float& _fLDist, const MaterialRefEntry& r, const float& _fRDist)
	{
		if (l.uPassId == r.uPassId)
		{
			for (size_t i = 0; i < kShaderType_NumOf; ++i)
			{
				if (l.Shaders[i].uID < r.Shaders[i].uID)
					return true;
			}

			return _fLDist < _fRDist;
		}

		return l.uPassId < r.uPassId;
	}

	//default compare
	inline bool MaterialCompare(const Material& l, const float& _fLDist, const Material& r, const float& _fRDist)
	{
		if (l && r)
		{
			return MaterialEntryCompare(l.Get(), _fLDist, r.Get(), _fRDist);
		}

		// l is leser if r is valid but l is not
		return r && !l;
	}
} // Tracy

#endif // !TRACY_MATERIAL_H
