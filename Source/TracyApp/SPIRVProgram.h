#ifndef TRACY_SPIRVPROGRAM_H
#define TRACY_SPIRVPROGRAM_H

#include "SPIRVConstant.h"
#include "SPIRVVariable.h"
#include "SPIRVOperation.h"
#include "GLM.h"
#include "glm\glm.hpp"

#include "Logger.h"
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

		template <class... Ts, class T = va_type_t<Ts...>>
		var<T, Assemble>& make_var(const Ts& ..._Val);

		uint32_t AddInstruction(const SPIRVOperation& _Instr);

	private:
		size_t AddConstant(const SPIRVConstant& _Const);
		size_t AddType(const SPIRVType& _Type);

	private:
		uint32_t m_uId = 0u;// internal instruction id

		// todo: add int matrix types
		using spv_types = std::variant<
			var<int32_t, Assemble>,
			var<uint32_t, Assemble>,
			var<float, Assemble>,
			var<float2, Assemble>,
			var<float3, Assemble>,
			var<float4, Assemble>,
			var<int2, Assemble>,
			var<int3, Assemble>,
			var<int4, Assemble>,
			var<uint2, Assemble>,
			var<uint3, Assemble>,
			var<uint4, Assemble>,
			var<matrix, Assemble>,
			var<float2x2, Assemble>,
			var<float3x3, Assemble>,
			var<float3x4, Assemble>,
			var<float4x3, Assemble>
		>;

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
		auto& f1 = make_var(1.f, 1.f);
		auto& f2 = make_var(2.f, 3.f);

		auto f3 = f1 + f2;
	}

	template<bool Assemble>
	inline uint32_t SPIRVProgram<Assemble>::AddInstruction(const SPIRVOperation& _Instr)
	{
		m_Instructions.push_back(_Instr);
		
		switch (_Instr.GetOpCode())
		{
			// instructions that don't create a result id (incomplete list)
		//case spv::OpTypeVoid:
		//case spv::OpTypeBool:
		//case spv::OpTypeInt:
		//case spv::OpTypeFloat:
		//case spv::OpTypeVector:
		//case spv::OpTypeMatrix:
		//case spv::OpTypeImage:
		//case spv::OpTypeSampler:
		//case spv::OpTypeSampledImage:
		//case spv::OpTypeArray:
		//case spv::OpTypeRuntimeArray:
		//case spv::OpTypeStruct:
		//case spv::OpTypeOpaque:
		//case spv::OpTypePointer:
		//case spv::OpTypeFunction:
		//case spv::OpTypeEvent:
		//case spv::OpTypeDeviceEvent:
		//case spv::OpTypeReserveId:
		//case spv::OpTypeQueue:
		//case spv::OpTypePipe:
		//case spv::OpTypeForwardPointer:

		case spv::OpStore:
		case spv::OpSelectionMerge:
		case spv::OpBranchConditional:
		case spv::OpBranch:
		case spv::OpLoopMerge:
		case spv::OpReturn:
		case spv::OpFunctionEnd:
			return m_uId;
		default:
			return m_uId++;
		}
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

	template<bool Assemble>
	inline size_t SPIRVProgram<Assemble>::AddType(const SPIRVType& _Type)
	{
		const size_t uHash = _Type.GetHash();
		if (m_Types.count(uHash) == 0ull)
		{
			m_Types.insert({ uHash, _Type });
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
	//	2) create a constexpr / SFINAE that converts Ts... to one type: va_type_t<Ts...>

	template<bool Assemble>
	template<class ...Ts, class T>
	inline var<T, Assemble>& SPIRVProgram<Assemble>::make_var(const Ts& ..._Val)
	{
		var<T, Assemble> new_var(_Val...);

		if constexpr(Assemble)
		{
			new_var.pParent = this;
			//new_var.kStorageClass = _kClass;

			// create variable constant
			SPIRVConstant Constant(SPIRVConstant::Make(_Val...));
			const size_t uConstHash = AddConstant(Constant);
			//SPIRVOperation OpConst(Constant.GetType(), { SPIRVOperand(kOperandType_Constant, uConstHash) });
			//const uint32_t uConstId = AddInstruction(OpConst);

			// composite type
			const SPIRVType& Type(Constant.GetCompositeType());
			const size_t uTypeHash = Type.GetHash();
			// SPIRVOperation OpType(Type.GetType(), { SPIRVOperand(kOperandType_Type, uTypeHash) });
			// const uint32_t uTypeId = AddInstruction(OpType);
			// no need to add this type since its embedded in the constant, for now

			// pointer type
			SPIRVType PointerType(spv::OpTypePointer); 
			PointerType.Append(Type);
			const size_t uPtrTypeHash = AddType(PointerType);
			//SPIRVOperation OpPtrType(PointerType.GetType(),{ SPIRVOperand(kOperandType_Type, uPtrTypeHash) });
			//const uint32_t uPtrId = AddInstruction(OpPtrType);

			// OpVariable:
			// Allocate an object in memory, resulting in a pointer to it, which can be used with OpLoad and OpStore.
			// Result Type must be an OpTypePointer. Its Type operand is the type of object in memory.
			// Storage Class is the Storage Class of the memory holding the object. It cannot be Generic.
			// Initializer is optional. If Initializer is present, it will be the initial value of the variable’s memory content.
			// Initializer must be an <id> from a constant instruction or a global(module scope) OpVariable instruction.
			// Initializer must havethe same type as the type pointed to by Result Type.

			SPIRVOperation OpVar(spv::OpVariable, 
			{ 
				SPIRVOperand(kOperandType_Type, uPtrTypeHash), // SPIRVOperand(kOperandType_Intermediate, uPtrId),
				SPIRVOperand(kOperandType_Constant, uConstHash)//SPIRVOperand(kOperandType_Intermediate, uConstId)
			});

			const uint32_t uVarId = AddInstruction(OpVar);

			// OpLoad:
			// Result Type is the type of the loaded object.
			// Pointer is the pointer to load through. Its type must be an OpTypePointer whose Type operand is the same as ResultType.
			// Memory Access must be a Memory Access literal. If not present, it is the same as specifying None.
			// bsp: None, Volatile, Aligned, Nontemporal

			SPIRVOperation OpLoad(spv::OpLoad,
			{
				SPIRVOperand(kOperandType_Type, uTypeHash), //SPIRVOperand(kOperandType_Intermediate, uTypeId)
				SPIRVOperand(kOperandType_Intermediate, uVarId)
			});

			new_var.uResultId = AddInstruction(OpLoad);
		}

		m_Variables.push_back(std::move(new_var)); // maybe put this in constexpr if too and return just new_var and changing return type to auto?
		return std::get<var<T, Assemble>>(m_Variables.back());
	}


	template <class T, bool Assemble>
	inline var<T, Assemble> operator+(const var<T, Assemble>& l, const var<T, Assemble>& r)
	{
		var<T, Assemble> var(l.Value + r.Value);

		// intermediate values?
		if constexpr(Assemble)
		{
			HASSERT(l.pParent == r.pParent, "Variables from different programs not supported, yet");
			var.pParent = l.pParent;
			
			//Floating - point addition of Operand 1 and	Operand 2.
			//Result Type	must be a scalar or vector of floating - point type.
			//The types of Operand 1 and Operand 2 both must be the same as Result Type.

			// todo: get fundamental type from T value
			SPIRVOperation Op(spv::OpFAdd, { SPIRVOperand(kOperandType_Intermediate, l.uResultId),SPIRVOperand(kOperandType_Intermediate, r.uResultId) });
			var.uResultId = l.pParent->AddInstruction(Op);
			
			// operands: l.immediateId != HUNDEFINED32 ? l.immediateId : l.VarId, same for r
		}
		
		return var;
	}

}; // !Tracy

#endif // !TRACY_SPIRVPROGRAM_H
