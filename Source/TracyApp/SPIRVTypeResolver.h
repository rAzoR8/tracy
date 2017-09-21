#ifndef TRACY_SPIRVTYPERESOLVER_H
#define TRACY_SPIRVTYPERESOLVER_H

#include <stdint.h>
#include <unordered_map>

#include <SPIRVInstruction.h>

namespace Tracy
{
	// forward decl
	class SPIRVType;

	class SPIRVTypeResolver
	{
	public:
		SPIRVTypeResolver(uint32_t& _uCurrentId);
		~SPIRVTypeResolver();

		uint32_t Resolve(const SPIRVType& _Type);

	private:
		uint32_t& m_uCurrentId;

		std::vector<SPIRVInstruction> m_TypeDefines;
		// type hash -> id
		std::unordered_map<size_t, uint32_t> m_TypeIds;
	};
}; // Tracy

#endif // !TRACY_SPIRVTYPERESOLVER_H
