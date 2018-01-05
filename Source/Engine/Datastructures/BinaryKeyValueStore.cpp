#include "BinaryKeyValueStore.h"
#include "Logger.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

BinaryKeyValueStore::BinaryKeyValueStore() :
	m_Stream(m_Data)
{
}
//---------------------------------------------------------------------------------------------------

BinaryKeyValueStore::BinaryKeyValueStore(hlx::bytes&& _KVBlob) :
	m_Data(std::forward<hlx::bytes>(_KVBlob)),
	m_Stream(m_Data)
{
	Header header{};
	m_Stream >> header;

	Read(header);
}
//---------------------------------------------------------------------------------------------------
BinaryKeyValueStore::~BinaryKeyValueStore()
{
}
//---------------------------------------------------------------------------------------------------
bool BinaryKeyValueStore::Read(const Header& _Header)
{
	const size_t uStart = m_Stream.get_offset();

	if (_Header.uMagic == kBKVMagic &&
		_Header.uVersion < kBinaryKeyValueVersion_Unknown &&
		m_Stream.available() >= _Header.uLength)
	{
		uint64_t uKey = HUNDEFINED64;
		Value Val{};

		for (uint32_t i = 0; i < _Header.uKeyValues; ++i)
		{
			m_Stream >> uKey;
			m_Stream >> Val.Type;

			Val.uOffset = m_Stream.get_offset();
			m_Stream.skip(Val.Type.GetSize());

			if (m_KeyValues.insert_or_assign(uKey, Val).second == false)
			{
				HERROR("Duplicate key %llu", uKey);
			}
		}

		size_t uLength = m_Stream.get_offset() - uStart;
		return uLength == _Header.uLength;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------

bool BinaryKeyValueStore::Read(hlx::bytestream& _Stream)
{
	Header header{};
	_Stream >> header;

	// copy header
	m_Stream << header;

	// copy key values
	m_Stream << _Stream.get<hlx::bytes>(header.uLength);
	m_Stream.set_offset(-(int32_t)header.uLength, std::ios::cur);

	return Read(header);
}
//---------------------------------------------------------------------------------------------------

void BinaryKeyValueStore::Write(hlx::bytestream& _Stream)
{
	size_t uStart = _Stream.get_offset();

	Header header{};
	header.uMagic = kBKVMagic;
	header.uVersion = kBinaryKeyValueVersion_0;
	header.uLength = 0u; // place holder
	header.uKeyValues = (uint32_t)m_KeyValues.size();

	_Stream << header;
	Header* pModHeader = reinterpret_cast<Header*>(_Stream.get_data(uStart));

	for (const auto& [key, value] : m_KeyValues)
	{
		_Stream << (uint64_t)key;
		_Stream << value.Type;
		_Stream << m_Data.substr(value.uOffset, value.Type.GetSize());
	}

	pModHeader->uLength = uint32_t(_Stream.get_offset() - uStart) - sizeof(Header);
}
//---------------------------------------------------------------------------------------------------
