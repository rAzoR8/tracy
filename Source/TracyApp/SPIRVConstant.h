#ifndef TRACY_SPIRVCONSTANT_H
#define TRACY_SPIRVCONSTANT_H

#include "SPIRVType.h"
#include "FunctionalUtils.h"
#include "Logger.h"

namespace Tracy
{	
	class SPIRVConstant
	{
	public:
		explicit SPIRVConstant(
			const spv::Op m_kConstantType = spv::OpConstantNull,
			const SPIRVType& _CompositeType = {},
			const std::vector<uint32_t>& _Constants = {});

		~SPIRVConstant();

		// composite & scalar constructor
		template<class T, class ...Ts>
		static SPIRVConstant Make(T&& first, Ts&& ..._args);

		SPIRVConstant(const SPIRVConstant& _Other);

		size_t GetHash() const;

		const spv::Op& GetType() const;
		const SPIRVType& GetCompositeType() const;
		const std::vector<uint32_t>& GetLiterals() const;

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

	inline std::vector<uint32_t> MakeLiterals(const std::string& _sString)
	{
		struct chars
		{
			char elem[sizeof(uint32_t)];
		};

		std::vector<uint32_t> Literals(_sString.size() / sizeof(uint32_t));

		uint32_t i = 0u;
		for (const char& c : _sString)
		{
			chars& chunk = reinterpret_cast<chars&>(Literals[i / sizeof(uint32_t)]);
			chunk.elem[i % sizeof(uint32_t)] = c;
			++i;
		}

		return Literals;
	}

	//---------------------------------------------------------------------------------------------------
	
	// Helper
	template<class T, class ...Ts>
	inline std::vector<uint32_t> MakeLiterals(T&& _Constant, Ts&& ..._args)
	{
		// compute number of uint32_t chunks needed to represent the constants
		size_t uCount = std::max<size_t>(sizeof(T) / sizeof(uint32_t), 1ull);
		std::vector<uint32_t> ConstData(uCount, 0u);
		std::memcpy(ConstData.data(), &_Constant, sizeof(T));

		if constexpr(sizeof...(_args) > 0u)
		{
			auto&& vec = MakeLiterals(std::forward<Ts>(_args)...);
			ConstData.insert(ConstData.end(), vec.begin(), vec.end());
		}

		return ConstData;
	}

	//---------------------------------------------------------------------------------------------------

	template<class T, class ...Ts>
	inline SPIRVConstant SPIRVConstant::Make(T&& first, Ts && ..._args)
	{
		static_assert(std::is_arithmetic<std::decay_t<T>>::value, "Invalid composite type!");
		static_assert(hlx::is_same_type<T, Ts...>(), "Composite types mismatch!");
		constexpr size_t uSize = sizeof ...(_args)+1u;

		if constexpr (1u == uSize)
		{
			return SPIRVConstant(
				spv::OpConstant,
				SPIRVType::Primitive<T>(),
				MakeLiterals(std::forward<T>(first), std::forward<Ts>(_args)...));
		}
		else if constexpr(uSize < 5u) // 2-4
		{
			return SPIRVConstant(
				spv::OpConstantComposite,
				SPIRVType::Vec<T, uSize>(),
				MakeLiterals(std::forward<T>(first), std::forward<Ts>(_args)...));
		}
		else if constexpr (uSize >= 5u)// matrix
		{
			uint32_t uRow = 0;
			uint32_t uCol = 0;

			switch (uSize)
			{
			//case 4u:
			//	uRow = uCol = 2;
			//	break;
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
				HFATAL("Unsuppored number of arguments for constant");
				break;
			}

			return SPIRVConstant(
				spv::OpConstantComposite,
				SPIRVType::Mat<T>(uRow, uCol),
				MakeLiterals(std::forward<T>(first), std::forward<Ts>(_args)...));
		}

		return SPIRVConstant(spv::OpConstantNull);
	}

}; // Tracy

#endif // !TRACY_SPIRVCONSTANT_H
