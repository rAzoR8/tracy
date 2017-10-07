#ifndef TRACY_SPIRVOPERATORIMPL_H
#define TRACY_SPIRVOPERATORIMPL_H

#include "SPIRVVariable.h"
#include "SPIRVAssembler.h"
#include <functional>

namespace Tracy
{
	//---------------------------------------------------------------------------------------------------
	template <class U, class V, class OpFunc, bool Assemble, class T = std::invoke_result_t<OpFunc, const U&, const V&>, class ...Ops >
	inline var_t<T, Assemble> make_op(const var_t<U, Assemble>& l, const var_t<V, Assemble>& r, const OpFunc& _OpFunc, const Ops ..._Ops)
	{
		var_t<T, Assemble> var(_OpFunc(l.Value, r.Value));

		if constexpr(Assemble)
		{
			LoadVariables(l, r);
			var.pAssembler = l.pAssembler;
			var.uTypeHash = SPIRVType::FromType<T>().GetHash();
			var.kStorageClass = spv::StorageClassFunction;

			spv::Op kType = OpTypeDecider<base_type_t<T>>(_Ops...);
			HASSERT(kType != spv::OpNop, "Invalid variable base type!");

			SPIRVOperation Op(kType, var.uTypeHash, // result type
			{
				SPIRVOperand(kOperandType_Intermediate, l.uResultId),
				SPIRVOperand(kOperandType_Intermediate, r.uResultId)
			});

			var.uResultId = l.pAssembler->AddOperation(Op);
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// OPERATOR IMPLEMENTATIONS
	//---------------------------------------------------------------------------------------------------

	template <class T, bool Assemble>
	inline var_t<T, Assemble> operator+(const var_t<T, Assemble>& l, const var_t<T, Assemble>& r)
	{
		return make_op(l, r, [](const T& v1, const T& v2)-> T {return v1 + v2; }, spv::OpFAdd, spv::OpIAdd);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble>
	inline var_t<T, Assemble> operator-(const var_t<T, Assemble>& l, const var_t<T, Assemble>& r)
	{
		return make_op(l, r, [](const T& v1, const T& v2)-> T {return v1 - v2; }, spv::OpFSub, spv::OpISub);
	}
	//---------------------------------------------------------------------------------------------------
	template <class U, class V, bool Assemble, class T = longer_type_t<U,V>>
	inline var_t<T, Assemble> operator*(const var_t<U, Assemble>& l, const var_t<V, Assemble>& r)
	{
		return make_op(l, r, [](const U& v1, const V& v2)-> T {return v1 * v2; }, spv::OpFMul, spv::OpIMul);
	}
	//---------------------------------------------------------------------------------------------------
	template <class U, class V, bool Assemble, class T = longer_type_t<U, V>>
	inline var_t<T, Assemble> operator/(const var_t<U, Assemble>& l, const var_t<V, Assemble>& r)
	{
		return make_op(l, r, [](const U& v1, const V& v2)-> T {return v1 / v2; }, spv::OpFDiv, spv::OpSDiv, spv::OpUDiv);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble>
	inline var_t<bool, Assemble> operator==(const var_t<T, Assemble>& l, const var_t<T, Assemble>& r)
	{
		return make_op(l, r, [](const T& v1, const T& v2)-> bool {return v1 == v2; }, spv::OpLogicalEqual);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble>
	inline var_t<bool, Assemble> operator!=(const var_t<T, Assemble>& l, const var_t<T, Assemble>& r)
	{
		return make_op(l, r, [](const T& v1, const T& v2)-> bool {return v1 != v2; }, spv::OpLogicalNotEqual);
	}
	//---------------------------------------------------------------------------------------------------
	template <bool Assemble>
	inline var_t<bool, Assemble> operator||(const var_t<bool, Assemble>& l, const var_t<bool, Assemble>& r)
	{
		return make_op(l, r, [](const T& v1, const T& v2)-> bool {return v1 || v2; }, spv::OpLogicalOr);
	}
	//---------------------------------------------------------------------------------------------------
	template <bool Assemble>
	inline var_t<bool, Assemble> operator&&(const var_t<bool, Assemble>& l, const var_t<bool, Assemble>& r)
	{
		return make_op(l, r, [](const T& v1, const T& v2)-> bool {return v1 && v2; }, spv::OpLogicalAnd);
	}
	//---------------------------------------------------------------------------------------------------

}; //!Tracy

#endif // !TRACY_SPIRVOPERATORIMPL_H
