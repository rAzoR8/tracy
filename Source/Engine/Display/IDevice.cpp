#include "IDevice.h"

using namespace Tracy;

const std::vector<EVendorID> IDevice::m_KnownIDs =
{
	kVendorID_Nvidia,
	kVendorID_AMD,
	kVendorID_ATI,
	kVendorID_Intel,
	kVendorID_Nintendo,
	kVendorID_Sony,
	kVendorID_Microsoft
};

IDevice::~IDevice()
{
}

const EVendorID IDevice::ToVendorID(const uint32_t _ID) const
{
	for (const EVendorID& ID : m_KnownIDs)
	{
		if (ID == _ID)
		{
			return ID;
		}
	}

	return kVendorID_Unknown;
}