#ifndef TRACY_GPUBUFFER_H
#define TRACY_GPUBUFFER_H

#include "DisplayTypes.h"
#include "Datastructures\RefCounted.h"

namespace Tracy
{
	using BufferRefEntry = RefEntry<BufferDesc>;

	class GPUBuffer : public RefCounted<BufferRefEntry, true>
	{
	public:
		REFCOUNT_INTERFACE(GPUBuffer, RefCountedType);

		virtual ~GPUBuffer() {}

	protected:
		GPUBuffer(const BufferDesc& _Desc);

		inline const bool IsValidBuffer() const { return IsValidRef() && Ref.HasAPIData(); }
		inline explicit operator bool() { return IsValidBuffer(); }

	private:

	};


} // Tracy

#endif // !TRACY_GPUBUFFER_H
