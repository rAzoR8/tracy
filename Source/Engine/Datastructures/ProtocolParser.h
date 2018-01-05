#ifndef TRACY_PROTOCOLPARSER_H
#define TRACY_PROTOCOLPARSER_H

#include <cstdint>
#include <vector>
#include "Logger.h"

namespace Tracy
{
	struct MsgHeader
	{
		uint32_t uType = HUNDEFINED32; // this is a linear index into the MsgParser instances vector
		uint32_t uVersion = HUNDEFINED32;
		uint32_t uLength = HUNDEFINED32;
	};

	struct Message
	{
		MsgHeader Header;
		const void* pData = nullptr;
	};

	template <class TStream>
	struct MsgParser
	{
		// _Header is passed for validation, but can be ignored
		virtual bool Read(TStream& _Stream, const MsgHeader& _Header) /*const*/ = 0;

		// Message contains pData of length Header.uLength
		virtual bool Write(TStream& _Stream, const Message& Message) = 0;
	};

	// TStream Interface:
	//struct TStream
	//{
	//	TStream& operator <<(TStream&, T);
	//	TStream& operator >>(TStream&, T);
	//	void skip(const size_t uLength);
	//	size_t available() const;
	//};

	template <class TStream>
	struct ProtocolParser
	{
		using TParser = MsgParser<TStream>;

		ProtocolParser() {}
		ProtocolParser(const std::vector<TParser*>& _Parsers) : m_Parsers(_Parsers) {}
		ProtocolParser(TParser* _pParser) : m_Parsers(1u, _pParser) {}

		virtual ~ProtocolParser() {}

		void RegisterParser(uint32_t _uMsgType, TParser* _pParser);

		bool Read(TStream& _Stream) const;
		bool Write(TStream& _Stream);

		// override this function to proved proto messages to be written, return false to indicate no more messages
		virtual bool GetNextWriteMsg(Message& _WriteMsg) { return false; /*read only*/ };

	private:
		std::vector<TParser*> m_Parsers;
	};

	//---------------------------------------------------------------------------------------------------

	template<class TStream>
	inline void ProtocolParser<TStream>::RegisterParser(uint32_t _uMsgType, TParser* _pParser)
	{
		if (m_Parsers.size() <= _uMsgType)
		{
			m_Parsers.resize(_uMsgType + 1u);
		}

		m_Parsers[_uMsgType] = _pParser;
	}

	//---------------------------------------------------------------------------------------------------

	template<class TStream>
	inline bool ProtocolParser<TStream>::Write(TStream& _Stream)
	{
		Message Msg{};
		while (GetNextWriteMsg(Msg))
		{
			if (m_Parsers.size() > Msg.Header.uType) // known message type
			{
				_Stream << Msg.Header;
				if (m_Parsers[Msg.Header.uType]->Write(_Stream, Msg) == false)
					return false;
			}
			else
			{
				HERROR("Unknown protocol message type %u, write not found", Msg.Header.uType);
				return false;
			}

			Msg = {};
		}

		return true;
	}

	//---------------------------------------------------------------------------------------------------

	template<class TStream>
	inline bool ProtocolParser<TStream>::Read(TStream& _Stream) const
	{
		if (_Stream.available() >= sizeof(MsgHeader))
		{
			MsgHeader Header{};
			_Stream >> Header;

			if (m_Parsers.size() > Header.uType) // known message type
			{
				if (m_Parsers[Header.uType]->Read(_Stream, Header) == false)
					return false;  // reader failed to parse
			}
			else // unknown message type
			{
				HWARNINGD("Unknown protocol message type %u, skipping %u bytes", Header.uType, Header.uLength);

				if (_Stream.available() >= Header.uLength)
				{
					_Stream.skip(Header.uLength);				
				}
				else // unexpected end of stream
				{
					HWARNINGD("Unexpected end of stream");
					return false;
				}
			}

			return Read(_Stream); // next msg
		}

		//HWARNINGD("Unexpected end of stream");
		return true;
	}
} // Tracy

#endif // !TRACY_PROTOCOLPARSER_H
