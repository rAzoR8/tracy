#ifndef TRACY_DEVICEINFO_H
#define TRACY_DEVICEINFO_H

#include "StandardDefines.h"
#include <cstdint>

namespace Tracy
{
	enum EVendorID
	{
		kVendorID_Nvidia = 0x10DE,
		kVendorID_AMD = 0x1022,
		kVendorID_ATI = 0x1002,
		kVendorID_Intel = 0x8086,
		kVendorID_Nintendo = 0x12E1,
		kVendorID_Sony = 0x104D,
		kVendorID_Microsoft = 0x1414,

		kVendorID_Unknown = 0xFFFF
	};

	/*static std::vector<EVendorID> VendorIDs = {
		kVendorID_Nvidia,
		kVendorID_AMD,
		kVendorID_ATI,
		kVendorID_Intel,
		kVendorID_Nintendo,
		kVendorID_Sony,
		kVendorID_Microsoft
	};*/

	/*enum EDeviceType
	{
		kDeviceType_Discrete = 0,
		kDeviceType_Integrated,
		kDeviceType_Console,
		kDeviceType_Software
	};*/

	struct DeviceInfo
	{
		uint64_t uTotalMemory = 0u;
		EVendorID VendorID = kVendorID_Unknown;
		THandle hHandle = kUndefinedSizeT;
		//EDeviceType Type;
	};
}

#endif // !TRACY_DEVICEINFO_H