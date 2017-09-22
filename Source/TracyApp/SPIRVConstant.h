#ifndef TRACY_SPIRVCONSTANT_H
#define TRACY_SPIRVCONSTANT_H

#include "SPIRVType.h"

namespace Tracy
{
	class SPIRVConstant
	{
	public:
		SPIRVConstant(const spv::Op m_kConstantType = spv::OpConstantNull, const std::vector<uint32_t>& _Constants = {});
		~SPIRVConstant();

		// composite & scalar constructor
		template <class T>
		SPIRVConstant(const std::initializer_list<T>& _Constants);

	private:
		spv::Op m_kConstantType = spv::OpNop;
		SPIRVType m_CompositeType;
		std::vector<uint32_t> m_Constants; // binary data
	};

	template<class T>
	inline SPIRVConstant::SPIRVConstant(const std::initializer_list<T>& _Constants)
	{
		if (_Constants.size() == 1u)
		{
			m_kConstantType = spv::OpConstant;
			m_CompositeType = SPIRVType::Primitive<T>();
		}
		else if  (_Constants.size() > 1u && _Constants.size() < 5u)
		{
			m_kConstantType = spv::OpConstantComposite;
			//m_CompositeType = SPIRVType(spv::OpTypeVector, _Constants.size()).Append(SPIRVType::Primitive<T>());
			m_CompositeType = SPIRVType::Vec<T>(static_cast<uint32_t>(_Constants.size()));
		}
		else // matrix
		{
			uint32_t uRow = 0;
			uint32_t uCol = 0;

			switch (_Constants.size())
			{
			case 4u:
				uRow = uCol = 2;
				break;
			case 9u:
				uRow = uCol = 3;
				break;
			case 12u:
				uRow = 4; uCol = 3; // always assuming 4x3 matrix
				break;
			case 16u:
				uRow = 4; uCol = 4;
				break;
			default:
				break;
			}

			m_kConstantType = spv::OpConstantComposite;
			m_CompositeType = SPIRVType::Mat<T>(uRow, uCol);			
		}

		// compute number of uint32_t chunks needed to represent the constants
		size_t uCount = _Constants.size() * (std::max<size_t>(sizeof(T) / sizeof(uint32_t), 1ull));
		m_Constants.resize(uCount);

		uint8_t* pData = reinterpret_cast<uint8_t*>(m_Constants.data());

		for (const T& spvconst : _Constants)
		{
			std::memcpy(pData, &spvconst, sizeof(T));
			pData += sizeof(T);
		}
	}
}; // Tracy

#endif // !TRACY_SPIRVCONSTANT_H
