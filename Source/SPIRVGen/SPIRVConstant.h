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
			const spv::Op _kConstantType = spv::OpConstantNull,
			const SPIRVType& _CompositeType = {},
			const std::vector<uint32_t>& _Constants = {});

		explicit SPIRVConstant(
			const spv::Op _kConstantType,
			const SPIRVType& _CompositeType,
			const std::vector<SPIRVConstant>& _Components);

		~SPIRVConstant();
		
		// composite & scalar constructor
		template<bool Spec, class T, class ...Ts>
		static SPIRVConstant Make(T&& first, Ts&& ..._args);

		SPIRVConstant(const SPIRVConstant& _Other);

		size_t GetHash(const bool _bParent = true) const;

		const spv::Op& GetType() const;
		const SPIRVType& GetCompositeType() const;
		const std::vector<uint32_t>& GetLiterals() const;
		const std::vector<SPIRVConstant>& GetComponents() const;

	private:
		spv::Op m_kConstantType = spv::OpNop;

		std::vector<SPIRVConstant> m_Components;

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

	inline const std::vector<SPIRVConstant>& SPIRVConstant::GetComponents() const
	{
		return m_Components;
	}

	//---------------------------------------------------------------------------------------------------

	inline size_t LiteralCount(const size_t uSizeInBytes)
	{
		if (uSizeInBytes % sizeof(uint32_t) == 0)
		{
			return uSizeInBytes / sizeof(uint32_t);
		}
		else
		{
			return (size_t)std::ceil(uSizeInBytes / (float)sizeof(uint32_t));
		}
	}

	inline std::vector<uint32_t> MakeLiteralString(const std::string& _sString)
	{
		struct chars
		{
			char elem[sizeof(uint32_t)];
		};

		std::vector<uint32_t> Literals(LiteralCount(_sString.size()), 0u);

		uint32_t i = 0u;
		for (const char& c : _sString)
		{
			chars& chunk = reinterpret_cast<chars&>(Literals[i / sizeof(uint32_t)]);
			chunk.elem[i % sizeof(uint32_t)] = c;
			++i;
		}

		// add string terminator
		if (i % sizeof(uint32_t) == 0u)
		{
			Literals.push_back(0u);
		}

		return Literals;
	}

	//---------------------------------------------------------------------------------------------------
	
	// Helper
	template<class T, class ...Ts>
	inline std::vector<uint32_t> MakeLiterals(T&& _Constant, Ts&& ..._args)
	{
		// compute number of uint32_t chunks needed to represent the constants
		size_t uCount = std::max<size_t>(LiteralCount(sizeof(T)), 1ull);
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

	template<bool Spec, class T, class ...Ts>
	inline SPIRVConstant SPIRVConstant::Make(T&& first, Ts && ..._args)
	{
		constexpr size_t uSize = sizeof ...(_args)+1u;
		constexpr bool bIsBool = std::is_same_v<T, bool> && uSize == 1u;

		static_assert(std::is_arithmetic<std::decay_t<T>>::value || bIsBool, "Invalid composite type!");
		static_assert(hlx::is_same_type<T, Ts...>() || bIsBool, "Composite types mismatch!");

		if constexpr(bIsBool)
		{
			if constexpr(Spec)
				return SPIRVConstant(first ? spv::OpSpecConstantTrue : spv::OpSpecConstantFalse);
			else
				return SPIRVConstant(first ? spv::OpConstantTrue : spv::OpConstantFalse);
		}
		else if constexpr (1u == uSize)
		{
			return SPIRVConstant(
				Spec ? spv::OpSpecConstant : spv::OpConstant,
				SPIRVType::Primitive<T>(),
				MakeLiterals(std::forward<T>(first)));
		}
		else if constexpr(uSize < 5u) // 2-4
		{
			return SPIRVConstant(
				Spec ? spv::OpSpecConstantComposite : spv::OpConstantComposite,
				SPIRVType::Vec<T, uSize>(),
				{
					Make<Spec>(std::forward<T>(first)),
					Make<Spec>(std::forward<Ts>(_args))...
				});
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
				{
					Make<Spec>(std::forward<T>(first)),
					Make<Spec>(std::forward<Ts>(_args))...
				});
		}

		return SPIRVConstant(spv::OpConstantNull);
	}

}; // Tracy

#endif // !TRACY_SPIRVCONSTANT_H
