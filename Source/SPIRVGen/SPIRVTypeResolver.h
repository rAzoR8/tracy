#ifndef TRACY_SPIRVTYPERESOLVER_H
#define TRACY_SPIRVTYPERESOLVER_H

#include <stdint.h>
#include <unordered_map>

#include "SPIRVInstruction.h"

namespace Tracy
{
	// forward decl
	class SPIRVType;
	class SPIRVConstant;

	class SPIRVTypeResolver
	{
	public:
		SPIRVTypeResolver(uint32_t& _uCurrentId, std::vector<SPIRVInstruction>& _Instructions);
		~SPIRVTypeResolver();

		uint32_t Resolve(const SPIRVType& _Type);

		uint32_t Resolve(const SPIRVConstant& _Constant);

		uint32_t GetTypeId(const size_t& _uHash) const;
		uint32_t GetConstantId(const size_t& _uHash) const;

		void Reset();

	private:
		uint32_t& m_uCurrentId;

		std::vector<SPIRVInstruction>& m_Instructions;
		// type hash -> id
		std::unordered_map<size_t, uint32_t> m_TypeIds;
		// constant hash -> id
		std::unordered_map<size_t, uint32_t> m_ConstantIds;

	};
}; // Tracy

#endif // !TRACY_SPIRVTYPERESOLVER_H
