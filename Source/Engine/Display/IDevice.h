#ifndef TRACY_IDEVICE_H
#define TRACY_IDEVICE_H

#include "DeviceInfo.h"

#include <vector>

namespace Tracy
{
	class IDevice
	{
	public:
		virtual ~IDevice();

		const DeviceInfo& GetInfo() const;

	protected:
		const EVendorID ToVendorID(const uint32_t _ID) const;

		DeviceInfo m_Info;

	private:
		static const std::vector<EVendorID> m_KnownIDs;
	};

	inline const DeviceInfo& IDevice::GetInfo() const { return m_Info; }
}

#endif // !TRACY_IDEVICE_H