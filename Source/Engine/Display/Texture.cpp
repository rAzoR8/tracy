#include "Texture.h"

using namespace Tracy;

//---------------------------------------------------------------------------------------------------
//Tracy::Texture::Texture(
//	const THandle _hDevice,
//	const ETextureType _kType, 
//	const uint16_t _uWidth, 
//	const uint16_t _uHeight, 
//	const uint16_t _uDepth, 
//	const EFormat _kFormat, 
//	const EUsageFlag _kUsageFlag, 
//	const std::string& _sName)
//{
//	m_Data.kType = _kType;
//	m_Data.uWidth = _uWidth;
//	m_Data.uHeight = _uHeight;
//	m_Data.uDepth = _uDepth;
//	m_Data.kFormat = _kFormat;
//	m_Data.kUsageFlag = _kUsageFlag;
//	m_Data.sName = _sName;
//
//	m_hDevice = _hDevice;
//}

//---------------------------------------------------------------------------------------------------
Texture::Texture(const TextureDesc& _Desc) : RefCountedType(CreateRefCountedTag{}, _Desc)
{
}
//---------------------------------------------------------------------------------------------------
