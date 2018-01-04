#include "BinaryKeyValueParser.h"

using namespace Tracy;
//---------------------------------------------------------------------------------------------------

BinaryKeyValueParser::BinaryKeyValueParser(hlx::bytestream& _Stream) :
	m_Parser(m_KeyValues),
	ProtocolParser(&m_Parser), // only one parser
	m_Stream(_Stream)
{
}
//---------------------------------------------------------------------------------------------------
BinaryKeyValueParser::~BinaryKeyValueParser()
{
}
//---------------------------------------------------------------------------------------------------
bool BinaryKeyValueParser::Write()
{
	m_bCanWrite = true;
	return ProtocolParser::Write(m_Stream);
}
//---------------------------------------------------------------------------------------------------
bool BinaryKeyValueParser::Parser::Read(hlx::bytestream& _Stream, const MsgHeader& _Header)
{
	if (_Header.uType == kMsgType && _Header.uVersion < kBinaryKeyValueVersion_Unknown)
	{
		size_t uStart = _Stream.get_offset();

		uint32_t uKeyValues = 0u;
		_Stream >> uKeyValues;

		uint64_t uKey = HUNDEFINED64;
		Value Val{};

		for (uint32_t i = 0; i < uKeyValues; ++i)
		{
			_Stream >> uKey;
			_Stream >> Val.Type;

			Val.uOffset = _Stream.get_offset();
			_Stream.skip(Val.Type.GetSize());

			if (m_KeyValues.insert_or_assign(uKey, Val).second == false)
			{
				HERROR("Duplicate key %llu", uKey);
			}
		}

		size_t uLength  = _Stream.get_offset() - uStart;
		return uLength == _Header.uLength;
	}

	return false;
}
//---------------------------------------------------------------------------------------------------

bool BinaryKeyValueParser::Parser::Write(hlx::bytestream& _Stream, const Message& Message)
{
	return false;
}
//---------------------------------------------------------------------------------------------------

bool BinaryKeyValueParser::GetNextWriteMsg(Message& _WriteMsg)
{
	bool bRet = m_bCanWrite;
	m_bCanWrite = false;
	return bRet;
}
//---------------------------------------------------------------------------------------------------
