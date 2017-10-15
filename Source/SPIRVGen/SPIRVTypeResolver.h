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
		using TIdMap = std::unordered_map<size_t, uint32_t>;

		SPIRVTypeResolver(uint32_t& _uCurrentId, std::vector<SPIRVInstruction>& _Instructions);
		~SPIRVTypeResolver();

		uint32_t Resolve(const SPIRVType& _Type);

		uint32_t Resolve(const SPIRVConstant& _Constant);

		uint32_t GetTypeId(const size_t& _uHash) const;
		uint32_t GetConstantId(const size_t& _uHash) const;

		// does not check for child types consitency
		bool RemoveType(const size_t& _uHash);
		bool RemoveConstant(const size_t& _uHash);

		void GetTypes(std::vector<size_t>& _OutHashes) const;
		void GetConstants(std::vector<size_t>& _OutHashes) const;

		void Reset();

	private:
		uint32_t& m_uCurrentId;

		std::vector<SPIRVInstruction>& m_Instructions;
		// type hash -> id
		TIdMap m_TypeIds;
		// constant hash -> id
		TIdMap m_ConstantIds;

	};
}; // Tracy

#endif // !TRACY_SPIRVTYPERESOLVER_H
