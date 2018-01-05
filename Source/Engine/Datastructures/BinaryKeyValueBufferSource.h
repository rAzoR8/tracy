#ifndef TRACY_BINARYKEYVALUEBUFFERSOURCE_H
#define TRACY_BINARYKEYVALUEBUFFERSOURCE_H

#include "BufferSource.h"
#include "BinaryKeyValueStore.h"

namespace Tracy
{
	class BinaryKeyValueBufferSource : public BufferSource, public BinaryKeyValueStore
	{
	public:
		BinaryKeyValueBufferSource();
		BinaryKeyValueBufferSource(hlx::bytes&& _KVBlob);

		virtual ~BinaryKeyValueBufferSource();

		// load from stream
		void Read(hlx::bytestream& _Stream);
	private:

		void Initialize();
	};

} // Tracy

#endif // !TRACY_BINARYKEYVALUEBUFFERSOURCE_H
