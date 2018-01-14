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

		const uint64_t& GetIdentifier() const;

	protected:
		GPUBuffer(const BufferDesc& _Desc);

	private:

	};

	inline const uint64_t& GPUBuffer::GetIdentifier() const
	{
		return Get().Data.uIdentifier;
	}
} // Tracy

#endif // !TRACY_GPUBUFFER_H
