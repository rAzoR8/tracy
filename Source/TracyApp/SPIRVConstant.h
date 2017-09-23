#ifndef TRACY_SPIRVCONSTANT_H
#define TRACY_SPIRVCONSTANT_H

#include "SPIRVType.h"
#include "FunctionalUtils.h"

namespace Tracy
{	
	class SPIRVConstant
	{
	public:
		SPIRVConstant(const spv::Op m_kConstantType = spv::OpConstantNull, const std::vector<uint32_t>& _Constants = {});
		~SPIRVConstant();

		// composite & scalar constructor
		template <class T, class... Ts>
		SPIRVConstant(T&& first, Ts&&... _args);

		size_t GetHash() const;

		const spv::Op& GetType() const;
		const SPIRVType& GetCompositeType() const;
		const std::vector<uint32_t>& GetLiterals() const;

	private:
		template <class T, class... Ts>
		void Consume(T&& _Constant, Ts&&... _args);

	private:
		spv::Op m_kConstantType = spv::OpNop;
		SPIRVType m_CompositeType;
		std::vector<uint32_t> m_Constants; // binary data
	};

	inline const spv::Op& Tracy::SPIRVConstant::GetType() const
	{
		return m_kConstantType;
	}
	inline const SPIRVType& SPIRVConstant::GetCompositeType() const
	{
		return m_CompositeType;
	}
	inline const std::vector<uint32_t>& SPIRVConstant::GetLiterals() const
	{
		return m_Constants;
	}
	//---------------------------------------------------------------------------------------------------
	template<class T, class ...Ts>
	inline SPIRVConstant::SPIRVConstant(T&& first, Ts&& ..._args)
	{
		static_assert(hlx::is_same_type<T, Ts...>(), "Composite types mismatch!");
		constexpr size_t uSize = sizeof ...(_args) + 1u;
		if constexpr (1u == uSize)
		{
			m_kConstantType = spv::OpConstant;
			m_CompositeType = SPIRVType::Primitive<T>();
		}
		else if constexpr(uSize < 5u) // 2-4
		{
			m_kConstantType = spv::OpConstantComposite;
			m_CompositeType = SPIRVType::Vec<T>(static_cast<uint32_t>(uSize));
		}
		else // matrix
		{
			uint32_t uRow = 0;
			uint32_t uCol = 0;

			switch (uSize)
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

		Consume(std::forward<T>(first), std::forward<Ts>(_args)...);
	}
	//---------------------------------------------------------------------------------------------------

	template<class T, class ...Ts>
	inline void SPIRVConstant::Consume(T&& _Constant, Ts&& ..._args)
	{
		// compute number of uint32_t chunks needed to represent the constants
		size_t uCount = std::max<size_t>(sizeof(T) / sizeof(uint32_t), 1ull);
		std::vector<uint32_t> ConstData(uCount, 0u);
		std::memcpy(ConstData.data(), &_Constant, sizeof(T));
		m_Constants.insert(m_Constants.end(), ConstData.begin(), ConstData.end());

		if constexpr(sizeof...(_args) > 0u)
			Consume(std::forward<Ts>(_args)...);
	}
	//---------------------------------------------------------------------------------------------------

}; // Tracy

#endif // !TRACY_SPIRVCONSTANT_H
