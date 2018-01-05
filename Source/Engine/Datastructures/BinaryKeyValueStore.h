#ifndef TRACY_BINARYKEYVALUESTORE_H
#define TRACY_BINARYKEYVALUESTORE_H

#include "ByteStream.h"
#include <unordered_map>
#include "..\SPIRVGen\SPIRVVariableTypes.h"
#include <glm\glm.hpp>

namespace Tracy
{
	template <class T, uint8_t i>
	constexpr uint16_t Eval = i | (sizeof(T) << 8);

	enum EPrimitiveType : uint16_t
	{
		kPrimitiveType_Char = Eval<char, 0>,
		kPrimitiveType_Int8 = kPrimitiveType_Char,
		kPrimitiveType_UInt8 = Eval<uint8_t, 1>,
		kPrimitiveType_Int16 = Eval<int16_t, 2>,
		kPrimitiveType_UInt16 = Eval<uint16_t, 3>,
		kPrimitiveType_Int32 = Eval<int32_t, 4>,
		kPrimitiveType_UInt32 = Eval<uint32_t, 5>,
		kPrimitiveType_Int64 = Eval<int64_t, 6>,
		kPrimitiveType_UInt64 = Eval<uint64_t, 7>,
		kPrimitiveType_Float = Eval<float, 8>,
		kPrimitiveType_Double = Eval<double, 9>,

		kPrimitiveType_Float2 = Eval<float2_t, 10>,
		kPrimitiveType_Float3 = Eval<float3_t, 11>,
		kPrimitiveType_Float4 = Eval<float4_t, 12>,

		kPrimitiveType_Float2x2 = Eval<float2x2_t, 13>,
		kPrimitiveType_Float3x3 = Eval<float3x3_t, 14>,
		kPrimitiveType_Float3x4 = Eval<float3x4_t, 15>,
		kPrimitiveType_Float4x3 = Eval<float4x3_t, 16>,
		kPrimitiveType_Float4x4 = Eval<float4x4_t, 17>,

		kPrimitiveType_NumOf = 18,
		kPrimitiveType_Unknown = kPrimitiveType_NumOf
	};

	constexpr uint8_t TypeSize(const EPrimitiveType kType) { return kType >> 8; }

	struct SerializableType
	{
		EPrimitiveType kType = kPrimitiveType_Unknown;
		uint16_t uCount = 0u; // > 1 means array

		uint32_t GetSize() const { return TypeSize(kType) * std::min(1u, (uint32_t)uCount); }
	};

	enum EBinaryKeyValueVersion
	{
		kBinaryKeyValueVersion_0 = 0,
		kBinaryKeyValueVersion_Unknown
	};

	class BinaryKeyValueStore
	{
	public:
		struct Value
		{
			size_t uOffset = 0u;
			SerializableType Type;
		};

		static constexpr uint32_t kBKVMagic = 0xa8b9c10d;

		struct Header
		{
			uint32_t uMagic = 0u;
			uint32_t uVersion = 0u;
			uint32_t uLength = 0u; // payload size in bytes (without header)
			uint32_t uKeyValues = 0u; // count
		};

		using TKeyValues = std::unordered_map<uint64_t, Value>;

		BinaryKeyValueStore();
		BinaryKeyValueStore(hlx::bytes&& _KVBlob);
		virtual ~BinaryKeyValueStore();

		bool Read(hlx::bytestream& _Stream);
		void Write(hlx::bytestream& _Stream);

		template <class T>
		T* GetValue(const uint64_t& _uHash) const;

	private:
		bool Read(const Header& _Header);

	private:
		hlx::bytes m_Data;
		hlx::bytestream m_Stream;

		bool m_bCanWrite = true;
		uint32_t m_uSizeInBytes = 0u;

		std::unordered_map<uint64_t, Value> m_KeyValues;
	};

	template<class T>
	inline T* BinaryKeyValueStore::GetValue(const uint64_t& _uHash) const
	{
		auto it = m_KeyValues.find(_uHash);

		if (it != m_KeyValues.end())
		{
			const Value& Val = it->second;
			const uint32_t uSize = Val.GetSize();

			if (uSize == sizeof(T) && Val.uOffset + uSize <= m_Data.size())
			{
				return reinterpret_cast<T*>(&m_Data[Val.uOffset]);
			}
		}

		return nullptr;
	}
} // Tracy

#endif // !TRACY_BINARYKEYVALUESTORE_H

