#include "BinaryKeyValueBufferSource.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

BinaryKeyValueBufferSource::BinaryKeyValueBufferSource()
{
}
//---------------------------------------------------------------------------------------------------

BinaryKeyValueBufferSource::BinaryKeyValueBufferSource(const hlx::bytes& _KVBlob) :
	BinaryKeyValueStore(_KVBlob)
{
	Initialize();
}
//---------------------------------------------------------------------------------------------------

BinaryKeyValueBufferSource::BinaryKeyValueBufferSource(hlx::bytes&& _KVBlob) :
	BinaryKeyValueStore(std::forward<hlx::bytes>(_KVBlob))
{
	Initialize();
}
//---------------------------------------------------------------------------------------------------

BinaryKeyValueBufferSource::~BinaryKeyValueBufferSource()
{
}
//---------------------------------------------------------------------------------------------------

void BinaryKeyValueBufferSource::Read(hlx::bytestream& _Stream)
{
	if (BinaryKeyValueStore::Read(_Stream))
	{
		Initialize();
	}
}
//---------------------------------------------------------------------------------------------------

void BinaryKeyValueBufferSource::Initialize()
{
	for (const auto&[key, value] : m_KeyValues)
	{
		const Value& Val = value;
		const uint32_t uSize = Val.Type.GetSize();

		if (Val.uOffset + uSize <= m_Data.size())
		{
			AddVar(&m_Data[Val.uOffset], uSize, key);
		}
	}

	Finalize();
}
//---------------------------------------------------------------------------------------------------
