#ifndef _TRACY_BASETYPES_H_
#define _TRACY_BASETYPES_H_

#include <cstdint>
#include <string>

namespace Tracy
{
	using u8 = unsigned char;
	using s8 = char;
	
	using u16 = uint16_t;
	using s16 = int16_t;
	
	using u32 = uint32_t;
	using s32 = int32_t;

	using u64 = uint64_t;
	using s64 = int64_t;

	using f32 = float;

	using str = std::string;
	using wstr = std::wstring;
}

#endif // !_TRACY_BASETYPES_H_