#ifndef TRACY_SPIRVPROGRAM_H
#define TRACY_SPIRVPROGRAM_H

#include "SPIRVConstant.h"
#include "SPIRVVariable.h"
#include "SPIRVOperation.h"

#include <unordered_map>
#include <variant>

namespace Tracy
{
	template <bool Assemble>
	class SPIRVProgram
	{
	public:
		SPIRVProgram();
		~SPIRVProgram();

		void Execute();

		// does not work as member:
		//float operator+(const float& l, const float& r);

		uint32_t NextId() { return m_uId++; }

		template <class T>
		var<T, Assemble>& make_var(
			const T& _Val = {},
			const spv::StorageClass _kClass = spv::StorageClassFunction,
			const std::string& _sName = {}); // creates a new variable

	private:
		size_t AddConstant(const SPIRVConstant& _Const);

	private:
		uint32_t m_uId = 0u;// internal instruction id

		// todo: add vector and matrix types
		using spv_types = std::variant<var<int32_t, Assemble>, var<uint32_t, Assemble>, var<float, Assemble>>;
		std::vector<spv_types> m_Variables;

		std::unordered_map<size_t, SPIRVType> m_Types; // types that are NOT used with constants
		std::unordered_map<size_t, SPIRVConstant> m_Constants;

		std::vector<SPIRVOperation> m_Instructions; // unresolved local instruction stream
	};

	template <bool Assemble>
	SPIRVProgram<Assemble>::SPIRVProgram()
	{
		m_Variables.reserve(4096);
	}

	template <bool Assemble>
	SPIRVProgram<Assemble>::~SPIRVProgram()
	{
	}

	// currently just test code
	template <bool Assemble>
	void SPIRVProgram<Assemble>::Execute()
	{
		auto& f1 = make_var<float>(1.f);
		auto& f2 = make_var<float>(2.f);

		auto f3 = f1 + f2;
	}

	template<bool Assemble>
	inline size_t SPIRVProgram<Assemble>::AddConstant(const SPIRVConstant& _Const)
	{
		const size_t uHash = _Const.GetHash();
		if (m_Constants.count(uHash) == 0ull)
		{
			m_Constants.insert({ uHash, _Const });
		}

		return uHash;
	}

	// problems to solve:
	// Structs! this function only handles fundamental types (int, float, vec, mat)
	// Global struct names are omited (for CBuffers / uniforms):
	// Struct SType { float member1;}
	// SType CBStuff;
	// void func(...) { return color * member1;}

	// also vectors etc: var<float3>, SPIRVConstant::Make(_Val) does not work with that 
	// Solutions:
	//	1)	make overloads for common types? SPIRVConstant::Make<float3>(const float3& vec)
	//		->Not good, does not make use of variadic arguments
	//	2) create a constexpr / SFINAE that converts Ts... to one type:

	template<bool Assemble>
	template<class T>
	inline var<T, Assemble>& SPIRVProgram<Assemble>::make_var(
		const T& _Val, const spv::StorageClass _kClass,
		const std::string& _sName)
	{
		// Allocate an object in memory, resulting in a pointer to it, which can be used with OpLoad and OpStore.
		// Result Type must be an OpTypePointer. Its Type operand is the type of object in memory.
		// Storage Class is the Storage Class of the memory holding the object. It cannot be Generic.
		// Initializer is optional. If Initializer is present, it will be the initial value of the variable’s memory content.
		// Initializer must be an <id> from a constant instruction or a global(module scope) OpVariable instruction.
		// Initializer must havethe same type as the type pointed to by Result Type.

		var<T, Assemble> new_var(this, _sName, _Val);

		SPIRVConstant Constant(SPIRVConstant::Make(_Val));
		const size_t uConstHash = AddConstant(Constant);
		//const size_t uTypeHash = Constant.GetCompositeType().GetHash();

		if constexpr(Assemble)
		{
			new_var.kStorageClass = _kClass;
			//new_var.uVarId = ResultId of OpLoad
		}

		// TODO: create OpTypePointer instr
		// TODO: create OpVariable instr
		m_Variables.push_back(std::move(new_var));
		return std::get<var<T, Assemble>>(m_Variables.back());
	}

	template <bool Assemble>
	inline var<float, Assemble> operator+(const var<float, Assemble>& l, const var<float, Assemble>& r)
	{
		float val = l.Value + r.Value;
		// intermediate values?
		if constexpr(Assemble)
		{
			auto v = l.pParent->make_var<float, true>(l.pParent, "imm", val);
			v.uImmediateId = l.pParent->NextId();
			// TODO: create instruction etc
			// operands: l.immediateId != HUNDEFINED32 ? l.immediateId : l.VarId, same for r
			return v;
		}
		else
		{
			return var<float, false>(val);
		}
	}

}; // !Tracy

#endif // !TRACY_SPIRVPROGRAM_H
