#ifndef TRACY_SPIRVOPERATORIMPL_H
#define TRACY_SPIRVOPERATORIMPL_H

#include "SPIRVVariable.h"
#include "SPIRVAssembler.h"
#include <vulkan\GLSL.std.450.h>

namespace Tracy
{
	//---------------------------------------------------------------------------------------------------
	// create operation with no operands
	template <bool Assemble, class OpFunc, class T = std::invoke_result_t<OpFunc>, class ...Ops>
	inline var_t<T, Assemble, spv::StorageClassFunction> make_op0(const OpFunc& _OpFunc, const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc();
		}
		else // Assemble
		{
			spv::Op kOpCode = (spv::Op)OpTypeDecider<base_type_t<T>>(_Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			SPIRVOperation Op(kOpCode, var.uTypeId); // result type

			var.uResultId = GlobalAssembler.AddOperation(Op);
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// create operation with one operand
	template <class U, class OpFunc, bool Assemble, spv::StorageClass C1, class T = std::invoke_result_t<OpFunc, const U&>, class ...Ops>
	inline var_t<T, Assemble, spv::StorageClassFunction> make_op1(const var_t<U, Assemble, C1>& l, const OpFunc& _OpFunc, const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc(l.Value);
		}
		else // Assemble
		{
			LoadVariables(l);

			spv::Op kOpCode = (spv::Op)OpTypeDecider<base_type_t<U>>(_Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			SPIRVOperation Op(kOpCode, var.uTypeId); // result type
			Op.AddIntermediate(l.uResultId); // operand1

			var.uResultId = GlobalAssembler.AddOperation(Op);
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// create operation with two operands
	template <class U, class V, class OpFunc, bool Assemble, spv::StorageClass C1, spv::StorageClass C2,  class T = std::invoke_result_t<OpFunc, const U&, const V&>, class ...Ops>
	inline var_t<T, Assemble, spv::StorageClassFunction> make_op2(const var_t<U, Assemble, C1>& l, const var_t<V, Assemble, C2>& r, const OpFunc& _OpFunc, const EOpTypeBase _kOpTypeBase, const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());
		
		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc(l.Value, r.Value);		
		}
		else // Assemble
		{
			LoadVariables(l, r);

			spv::Op kOpCode = (spv::Op)OpTypeDeciderEx<T, U, V>(_kOpTypeBase, _Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			SPIRVOperation Op(kOpCode, var.uTypeId); // result type
			Op.AddIntermediate(l.uResultId); // operand1
			Op.AddIntermediate(r.uResultId); // operand2

			var.uResultId = GlobalAssembler.AddOperation(Op);
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// create operation with three operands
	template <class U, class V, class W, class OpFunc, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3, class T = std::invoke_result_t<OpFunc, const U&, const V&, const W&>, class ...Ops>
	inline var_t<T, Assemble, spv::StorageClassFunction> make_op3(
		const var_t<U, Assemble, C1>& v1,
		const var_t<V, Assemble, C2>& v2,
		const var_t<W, Assemble, C3>& v3,
		const OpFunc& _OpFunc,
		const EOpTypeBase _kOpTypeBase,
		const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc(l.Value, r.Value);
		}
		else // Assemble
		{
			LoadVariables(v1, v2, v3);

			spv::Op kOpCode = (spv::Op)OpTypeDeciderEx<T, U, V, W>(_kOpTypeBase, _Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			SPIRVOperation Op(kOpCode, var.uTypeId); // result type
			Op.AddIntermediate(v1.uResultId); // operand1
			Op.AddIntermediate(v2.uResultId); // operand2
			Op.AddIntermediate(v3.uResultId); // operand3

			var.uResultId = GlobalAssembler.AddOperation(Op);
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// extension operation with no operands
	template <bool Assemble, class OpFunc, class T = std::invoke_result_t<OpFunc>, class ...Ops >
	inline var_t<T, Assemble, spv::StorageClassFunction> make_ext_op0(const OpFunc& _OpFunc, const std::string& _sExt, const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc();
		}
		else
		{
			uint32_t kOpCode = OpTypeDecider<base_type_t<T>>(_Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			uint32_t uExtId = GlobalAssembler.GetExtensionId(_sExt);
			HASSERT(uExtId != HUNDEFINED32, "Invalid extension");

			SPIRVOperation Op(spv::OpExtInst, var.uTypeId, // result type
				{
					SPIRVOperand(kOperandType_Intermediate, uExtId),
					SPIRVOperand(kOperandType_Literal, kOpCode) // instr opcode
				});

			var.uResultId = GlobalAssembler.AddOperation(Op);
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// extension operation with one operand
	template <class U, class OpFunc, bool Assemble, spv::StorageClass C1, class T = std::invoke_result_t<OpFunc, const U&>, class ...Ops >
	inline var_t<T, Assemble, spv::StorageClassFunction> make_ext_op1(const var_t<U, Assemble, C1>& l, const OpFunc& _OpFunc, const std::string& _sExt, const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc(l.Value);
		}
		else
		{
			l.Load();

			uint32_t kOpCode = OpTypeDecider<base_type_t<U>>(_Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			uint32_t uExtId = GlobalAssembler.GetExtensionId(_sExt);
			HASSERT(uExtId != HUNDEFINED32, "Invalid extension");

			SPIRVOperation Op(spv::OpExtInst, var.uTypeId, // result type
			{
				SPIRVOperand(kOperandType_Intermediate, uExtId),
				SPIRVOperand(kOperandType_Literal, kOpCode), // instr opcode
				SPIRVOperand(kOperandType_Intermediate, l.uResultId),
			});

			var.uResultId = GlobalAssembler.AddOperation(Op);
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// extension operation with two operands
	template <class U, class V, class OpFunc, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class T = std::invoke_result_t<OpFunc, const U&, const V&>, class ...Ops >
	inline var_t<T, Assemble, spv::StorageClassFunction> make_ext_op2(const var_t<U, Assemble, C1>& l, const var_t<V, Assemble, C2>& r, const OpFunc& _OpFunc, const std::string& _sExt, const EOpTypeBase _kOpTypeBase, const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc(l.Value, r.Value);
		}
		else
		{
			LoadVariables(l, r);

			spv::Op kOpCode = (spv::Op)OpTypeDeciderEx<T, U, V>(_kOpTypeBase, _Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			uint32_t uExtId = GlobalAssembler.GetExtensionId(_sExt);
			HASSERT(uExtId != HUNDEFINED32, "Invalid extension");

			SPIRVOperation Op(spv::OpExtInst, var.uTypeId, // result type
			{
				SPIRVOperand(kOperandType_Intermediate, uExtId),
				SPIRVOperand(kOperandType_Literal, kOpCode), // instr opcode
				SPIRVOperand(kOperandType_Intermediate, l.uResultId),
				SPIRVOperand(kOperandType_Intermediate, r.uResultId)
			});

			var.uResultId = GlobalAssembler.AddOperation(Op);
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// extension operation with three operands
	template <class U, class V, class W, class OpFunc, bool Assemble,
		spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3,
		class T = std::invoke_result_t<OpFunc, const U&, const V&, const W&>, class ...Ops>
	inline var_t<T, Assemble, spv::StorageClassFunction> make_ext_op3(
		const var_t<U, Assemble, C1>& v1,
		const var_t<V, Assemble, C2>& v2,
		const var_t<W, Assemble, C3>& v3,
		const OpFunc& _OpFunc, const std::string& _sExt, const EOpTypeBase _kOpTypeBase, const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc(v1.Value, v2.Value, v3.Value);
		}
		else
		{
			LoadVariables(v1, v2, v3);

			spv::Op kOpCode = (spv::Op)OpTypeDeciderEx<T, U, V, W>(_kOpTypeBase, _Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			uint32_t uExtId = GlobalAssembler.GetExtensionId(_sExt);
			HASSERT(uExtId != HUNDEFINED32, "Invalid extension");

			SPIRVOperation Op(spv::OpExtInst, var.uTypeId); // result type
			Op.AddIntermediate(uExtId);
			Op.AddLiteral(kOpCode); // instr opcode
			Op.AddIntermediate(v1.uResultId);
			Op.AddIntermediate(v2.uResultId);
			Op.AddIntermediate(v3.uResultId);

			var.uResultId = GlobalAssembler.AddOperation(Op);
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// OPERATOR IMPLEMENTATIONS
	//---------------------------------------------------------------------------------------------------

	// ADD
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator+(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> T {return v1 + v2; }, kOpTypeBase_Result, spv::OpFAdd, spv::OpIAdd);
	}
	// add with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_convertible<V, T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator+(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) + r;
	}
	// add with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_convertible<V, T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator+(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l + var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}
	//---------------------------------------------------------------------------------------------------
	// SUB
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator-(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> T {return v1 - v2; }, kOpTypeBase_Result, spv::OpFSub, spv::OpISub);
	}
	// sub with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_convertible<V, T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator-(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) - r;
	}
	// sub with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_convertible<V, T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator-(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l - var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// MUL
	template <class U, class V, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class T = mul_result_t<U,V>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator*(const var_t<U, Assemble, C1>& l, const var_t<V, Assemble, C2>& r)
	{
		if constexpr(is_vector<U> && is_scalar<V>)
			return make_op2(l, r, [](const U& v1, const V& v2) -> T {return v1 * v2; }, kOpTypeBase_Result, spv::OpVectorTimesScalar);
		else if constexpr(is_vector<V> && is_scalar<U>)
			return make_op2(r, l, [](const V& v1, const U& v2) -> T {return v1 * v2; }, kOpTypeBase_Result, spv::OpVectorTimesScalar);
		else if constexpr(is_matrix<V> || is_matrix<U>)
			return Mul(l, r); // implementation below
		else
			return make_op2(l, r, [](const U& v1, const V& v2) -> T {return v1 * v2; }, kOpTypeBase_Result, spv::OpFMul, spv::OpIMul);
	}

	// mul with constant left
	template <class U, class V, bool Assemble, spv::StorageClass C1, class BaseType = base_type_t<V>, typename = std::enable_if_t<is_convertible<U, BaseType>>>
	inline var_t<V, Assemble, spv::StorageClassFunction> operator*(const U& l, const var_t<V, Assemble, C1>& r)
	{
		return var_t<BaseType, Assemble, spv::StorageClassFunction>((BaseType)l) *  r;
	}

	// mul with constant right
	template <class U, class V, bool Assemble, spv::StorageClass C1, class BaseType = base_type_t<U>, typename = std::enable_if_t<is_convertible<V, BaseType>>>
	inline var_t<U, Assemble, spv::StorageClassFunction> operator*(const var_t<U, Assemble, C1>& l, const V& r)
	{
		return l * var_t<BaseType, Assemble, spv::StorageClassFunction>((BaseType)r);
	}

	// vector * matrix
	template <class M, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_matrix<M>>>
	inline var_t<row_type_t<M>, Assemble, spv::StorageClassFunction> Mul(
		const var_t<col_type_t<M>, Assemble, C1>& l,
		const var_t<M, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const col_type_t<M>& v, const M& m)-> row_type_t<M> {return v * m; }, kOpTypeBase_Result, spv::OpVectorTimesMatrix);
	}

	// matrix * vector
	template <class M, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_matrix<M>>>
	inline var_t<col_type_t<M>, Assemble, spv::StorageClassFunction> Mul(
		const var_t<M, Assemble, C1>& l,
		const var_t<row_type_t<M>, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const M& m, const row_type_t<M>& v)-> col_type_t<M> {return m * v; }, kOpTypeBase_Result, spv::OpMatrixTimesVector);
	}

	// matrix * matrix
	template <bool Assemble,
		spv::StorageClass C1, spv::StorageClass C2,
		class M, class N,
		class MRow = row_type_t<M>,
		class MCol = col_type_t<M>,
		class NRow = row_type_t<N>,
		class NCol = col_type_t<N>,
		class R = mat_type_t<NRow, MCol>,
		typename = std::enable_if_t<std::is_same_v<MRow, NCol>>>
		inline var_t<R, Assemble, spv::StorageClassFunction> Mul(
			const var_t<M, Assemble, C1>& l,
			const var_t<N, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const M& m, const N& n)-> R {return m * n; }, kOpTypeBase_Result, spv::OpMatrixTimesMatrix);
	}

	//---------------------------------------------------------------------------------------------------
	// DIV
	template <class U, class V, bool Assemble, spv::StorageClass C1, spv::StorageClass C2,
		class T = longer_type_t<U, V>,
		class BaseType = base_type_t<V>,
		typename = std::enable_if_t<std::is_same_v<V, base_type_t<U>> || std::is_same_v<U, V>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator/(const var_t<U, Assemble, C1>& l, const var_t<V, Assemble, C2>& r)
	{
		//The types of Operand 1 and Operand 2 both must be the same as Result Type
		if constexpr(std::is_same_v<U, V>)
		{
			return make_op2(l, r, [](const U& v1, const V& v2)-> T {return v1 / v2; }, kOpTypeBase_Result, spv::OpFDiv, spv::OpSDiv, spv::OpUDiv);
		}
		else // if right operand is a scalar, multiply with inverse
		{
			return l * var_t<BaseType, Assemble, spv::StorageClassFunction>((BaseType)1 / r);
		}
	}
	// div with constant left
	template <class U, class V, bool Assemble, spv::StorageClass C1, class BaseType = base_type_t<V>, typename = std::enable_if_t<is_convertible<U, BaseType>>>
	inline var_t<V, Assemble, spv::StorageClassFunction> operator/(const U& l, const var_t<V, Assemble, C1>& r)
	{
		return var_t<BaseType, Assemble, spv::StorageClassFunction>((BaseType)l) / r;
	}
	// div with constant right
	template <class U, class V, bool Assemble, spv::StorageClass C1, class BaseType = base_type_t<U>, typename = std::enable_if_t<is_convertible<V, BaseType>>>
	inline var_t<U, Assemble, spv::StorageClassFunction> operator/(const var_t<U, Assemble, C1>& l, const V& r)
	{
		return l * var_t<BaseType, Assemble, spv::StorageClassFunction>((BaseType)1 / (BaseType)r);
	}

	//---------------------------------------------------------------------------------------------------
	// EQUAL
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator==(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> bool {return v1 == v2; }, kOpTypeBase_Result, spv::OpLogicalEqual);
	}
	// equal with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1/*, typename = std::enable_if_t<is_convertible<T,V>>*/>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator==(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) == r;
	}
	// equal with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1/*, typename = std::enable_if_t<is_convertible<T, V>>*/>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator==(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l == var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}
	//---------------------------------------------------------------------------------------------------
	// UNEQUAL
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator!=(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> bool {return v1 != v2; }, kOpTypeBase_Result, spv::OpLogicalNotEqual);
	}
	// unequal with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator!=(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) != r;
	}
	// unequal with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator!=(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l != var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// LOGICAL OR
	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator||(const var_t<bool, Assemble, C1>& l, const var_t<bool, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const bool& v1, const bool& v2)-> bool {return v1 || v2; }, kOpTypeBase_Result, spv::OpLogicalOr);
	}
	// logical or with constant left
	template <bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator||(const bool& l, const var_t<bool, Assemble, C1>& r)
	{
		return var_t<bool, Assemble, spv::StorageClassFunction>(l) || r;
	}
	// logical or with constant right
	template <bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator||(const var_t<bool, Assemble, C1>& l, const bool& r)
	{
		return l || var_t<bool, Assemble, spv::StorageClassFunction>(r);
	}

	//---------------------------------------------------------------------------------------------------
	// LOGICAL AND
	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator&&(const var_t<bool, Assemble, C1>& l, const var_t<bool, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const bool& v1, const bool& v2)-> bool {return v1 && v2; }, kOpTypeBase_Result, spv::OpLogicalAnd);
	}
	// logical and with constant left
	template <bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator&&(const bool& l, const var_t<bool, Assemble, C1>& r)
	{
		return var_t<bool, Assemble, spv::StorageClassFunction>(l) && r;
	}
	// logical and with constant right
	template <bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator&&(const var_t<bool, Assemble, C1>& l, const bool& r)
	{
		return l && var_t<bool, Assemble, spv::StorageClassFunction>(r);
	}

	//---------------------------------------------------------------------------------------------------
	// BITWISE OR
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator|(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> T {return v1 | v2; }, kOpTypeBase_Result, spv::OpBitwiseOr);
	}
	// bitwise or with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator|(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) | r;
	}
	// bitwise or with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator|(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l | var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// BITWISE XOR
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator^(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> T {return v1 ^ v2; }, kOpTypeBase_Result, spv::OpBitwiseXor);
	}
	// bitwise xor with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator^(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) ^ r;
	}
	// bitwise xor with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator^(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l ^ var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// BITWISE AND
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator&(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> T {return v1 & v2; }, kOpTypeBase_Result, spv::OpBitwiseAnd);
	}
	// bitwise and with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator&(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) & r;
	}
	// bitwise and with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator&(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l & var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// Less
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator<(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> bool {return v1 < v2; }, kOpTypeBase_Operand1, spv::OpFOrdLessThan, spv::OpSLessThan, spv::OpULessThan);
	}
	// Less with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator<(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) < r;
	}
	// Less with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator<(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l < var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// Less then equal
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator<=(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> bool {return v1 <= v2; }, kOpTypeBase_Operand1, spv::OpFOrdLessThanEqual, spv::OpSLessThanEqual, spv::OpULessThanEqual);
	}
	// Less then equal with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator<=(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) <= r;
	}
	// Less then equal with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator<=(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l <= var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// GREATER
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator>(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> bool {return v1 > v2; }, kOpTypeBase_Operand1, spv::OpFOrdGreaterThan, spv::OpSGreaterThan, spv::OpUGreaterThan);
	}
	// greater with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator>(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) > r;
	}
	// greater with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator>(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l > var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// Greater then equal
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator>=(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> bool {return v1 >= v2; }, kOpTypeBase_Operand1, spv::OpFOrdGreaterThanEqual, spv::OpSGreaterThanEqual, spv::OpUGreaterThanEqual);
	}
	// Greater then equal with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator>=(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) >= r;
	}
	// Greater then equal with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator>=(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l >= var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// Logical Shift Right
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator>>(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> T {return v1 >> v2; }, kOpTypeBase_Result, spv::OpShiftRightLogical);
	}
	// logical shift right with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator>>(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) >> r;
	}
	// logical shift right with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator>>(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l >> var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// Logical Shift left
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator<<(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> T {return v1 << v2; }, kOpTypeBase_Result, spv::OpShiftLeftLogical);
	}
	// logical shift left with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator<<(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) << r;
	}
	// logical shift left with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator<<(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l << var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// DOT
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_float<T>>>
	inline var_t<base_type_t<T>, Assemble, spv::StorageClassFunction> Dot(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& u, const T& v)-> base_type_t<T> {return glm::dot(u, v); }, kOpTypeBase_Result, spv::OpDot);
	}

	//---------------------------------------------------------------------------------------------------
	// Transpose Matrix
	template <class M, bool Assemble, spv::StorageClass C1,
		class RowT = row_type_t<M>, class ColT = col_type_t<M>, class R = mat_type_t<ColT, RowT>,
		typename = std::enable_if_t<is_matrix<M>>>
	inline var_t<R, Assemble, spv::StorageClassFunction> Transpose(const var_t<M, Assemble, C1>& _Mat)
	{
		return make_op1(_Mat, [](const M& m)-> R {return glm::transpose(m); }, spv::OpTranspose);
	}

	//---------------------------------------------------------------------------------------------------
	// Fragment derivative ddx
	template <class T, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_base_float<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Ddx(const var_t<T, Assemble, C1>& P)
	{
		// TODO: DDX not implemented for CPU execution
		return make_op1(P, [](const T& p)-> T {return p; }, spv::OpDPdx);
	}

	//---------------------------------------------------------------------------------------------------
	// Fragment derivative ddy
	template <class T, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_base_float<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Ddy(const var_t<T, Assemble, C1>& P)
	{
		// TODO: DDY not implemented for CPU execution
		return make_op1(P, [](const T& p)-> T {return p; }, spv::OpDPdy);
	}

	//---------------------------------------------------------------------------------------------------
	// Select from two objects
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3, size_t N = Dimension<T>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Select(const var_t<vec_type_t<bool, N>, Assemble, C1>& Condition, const var_t<T, Assemble, C2>& TrueVar, const var_t<T, Assemble, C3>& FalseVar)
	{
		if constexpr(N > 1)
		{
			const auto select = [](const CondT& cond, const T& t, const T& f)->T
			{
				T ret;
				for (size_t = i; i < N; ++i)
				{
					ret[i] = cond[i] ? t[i] : f[i];
				}
				return ret;
			};

			return make_op3(Condition, TrueVar, FalseVar, select, kOpTypeBase_Result, spv::OpSelect);
		}
		else
		{
			return make_op3(Condition, TrueVar, FalseVar, [](const bool& cond, const T& t, const T& f)-> T {return cond ? t : f;}, kOpTypeBase_Result, spv::OpSelect);
		}
	}

	//---------------------------------------------------------------------------------------------------
	// GLSLstd450 EXTENSION
	//---------------------------------------------------------------------------------------------------
	// https://www.khronos.org/registry/spir-v/specs/unified1/GLSL.std.450.pdf

	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Radians(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::radians(v1); }, ExtGLSL450, GLSLstd450Radians);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Degrees(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::degrees(v1); }, ExtGLSL450, GLSLstd450Degrees);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Sin(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::sin(v1); }, ExtGLSL450, GLSLstd450Sin);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Cos(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::cos(v1); }, ExtGLSL450, GLSLstd450Cos);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Tan(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::tan(v1); }, ExtGLSL450, GLSLstd450Tan);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Asin(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::asin(v1); }, ExtGLSL450, GLSLstd450Asin);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Acos(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::acos(v1); }, ExtGLSL450, GLSLstd450Acos);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Atan(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::atan(v1); }, ExtGLSL450, GLSLstd450Atan);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Sinh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::sinh(v1); }, ExtGLSL450, GLSLstd450Sinh);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Cosh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::cos(v1); }, ExtGLSL450, GLSLstd450Cosh);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Tanh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::tan(v1); }, ExtGLSL450, GLSLstd450Tanh);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Asinh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::asinh(v1); }, ExtGLSL450, GLSLstd450Asinh);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Acosh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::acosh(v1); }, ExtGLSL450, GLSLstd450Acosh);
	}
	//---------------------------------------------------------------------------------------------------
	// Result is undefined if abs x >= 1. Results are computed per component.
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Atanh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::atanh(v1); }, ExtGLSL450, GLSLstd450Atanh);
	}
	//---------------------------------------------------------------------------------------------------
	// Arc tangent. Result is an angle, in radians, whose tangent is y / x. The signs of x and y are used
	// to determine what quadrant the angle is in. The range of result values is[-pi,pi].
	// Result is undefined if x	and	y are both 0.
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> Atan2(const var_t<T, Assemble, C1>& x, const var_t<T, Assemble, C2>& y)
	{
		return make_ext_op2(x, y, [](const T& _x, const T& _y) {return glm::atan(_x, _y); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Atan2);
	}
	//---------------------------------------------------------------------------------------------------
	// Exponential function x^y Results are computed per componen
	// Result is undefined if x	< 0. Result is undefined if	x = 0 and y <= 0
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> Pow(const var_t<T, Assemble, C1>& x, const var_t<T, Assemble, C2>& y)
	{
		return make_ext_op2(x, y, [](const T& v1, const T& v2) {return glm::pow(v1, v2); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Pow);
	}
	//---------------------------------------------------------------------------------------------------
	// Log Results are computed per componen
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> Log(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::log(v1); }, ExtGLSL450, GLSLstd450Log);
	}	
	//---------------------------------------------------------------------------------------------------
	// Log2 Base 2 Results are computed per componen
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> Log2(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::log2(v1); }, ExtGLSL450, GLSLstd450Log2);
	}
	//---------------------------------------------------------------------------------------------------
	// Exponential function e^x
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> Exp(const var_t<T, Assemble, Class>& x)
	{
		return make_ext_op1(x, [](const T& v1) {return glm::exp(v1); }, ExtGLSL450, GLSLstd450Exp);
	}
	//---------------------------------------------------------------------------------------------------
	// Exponential function base 2 2^x
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> Exp2(const var_t<T, Assemble, Class>& x)
	{
		return make_ext_op1(x, [](const T& v1) {return glm::exp2(v1); }, ExtGLSL450, GLSLstd450Exp2);
	}
	//---------------------------------------------------------------------------------------------------
	// SquareRoot Results are computed per component.
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> Sqrt(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::sqrt(v1); }, ExtGLSL450, GLSLstd450Sqrt);
	}
	//---------------------------------------------------------------------------------------------------
	// InverseSqrt Results are computed per component.
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> InvSqrt(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::inversesqrt(v1); }, ExtGLSL450, GLSLstd450InverseSqrt);
	}

	//---------------------------------------------------------------------------------------------------
	// Normalize
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> Normalize(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::normalize(v1); }, ExtGLSL450, GLSLstd450Normalize);
	}
	//---------------------------------------------------------------------------------------------------
	// Length
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<base_type_t<T>, Assemble, spv::StorageClassFunction> Length(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::length(v1); }, ExtGLSL450, GLSLstd450Length);
	}
	//---------------------------------------------------------------------------------------------------
	// Distance
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<base_type_t<T>, Assemble, spv::StorageClassFunction> Distance(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_ext_op2(l, r, [](const T& v1, const T& v2) {return glm::distance(v1, v2); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Distance);
	}
	//---------------------------------------------------------------------------------------------------
	// Cross product
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2/*, class T = vec_type_t<FloatT, 3>*/>
	inline var_t<T, Assemble, spv::StorageClassFunction> Cross(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_ext_op2(l, r, [](const T& v1, const T& v2) -> T{return glm::cross(v1, v2); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Cross);
	}
	//---------------------------------------------------------------------------------------------------
	// FMA fused multiply add
	template <class A, class B, class C, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3,
		typename = std::enable_if_t<is_base_float<A> && is_base_float<B> && is_base_float<C>>>
	inline auto Fma(const var_t<A, Assemble, C1>& va, const var_t<B, Assemble, C2>& vb, const var_t<C, Assemble, C3>& vc)
	{
		return make_ext_op3(va, vb, vc, [](const A& a, const B& b, const C& c) {return a * b + c; }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Fma);
	}
	//---------------------------------------------------------------------------------------------------
	// MatrixInverse
	//template <bool Assemble, spv::StorageClass Class, uint32_t Dim, class Mat = mat_type_dim_t<float, Dim, Dim>>
	template <
		class M, bool Assemble, spv::StorageClass Class,
		class Row = row_type_t<M>, class Col = col_type_t<M>,
		typename = std::enable_if_t<std::is_same_v<Row, Col>>> // Square matrix
	inline var_t<M, Assemble, spv::StorageClassFunction> Inverse(const var_t<M, Assemble, Class>& _Mat)
	{
		return make_ext_op1(_Mat, [](const M& m) {return glm::inverse(m); }, ExtGLSL450, GLSLstd450MatrixInverse);
	}
	//---------------------------------------------------------------------------------------------------
	// MatrixDeterminant
	template <
		class M, bool Assemble, spv::StorageClass Class,
		class Row = row_type_t<M>, class Col = col_type_t<M>, class R = base_type_t<M>,
		typename = std::enable_if_t<std::is_same_v<Row, Col>>> // Square matrix
		inline var_t<R, Assemble, spv::StorageClassFunction> Determinant(const var_t<M, Assemble, Class>& _Mat)
	{
		return make_ext_op1(_Mat, [](const M& m) {return glm::determinant(m); }, ExtGLSL450, GLSLstd450Determinant);
	}

	//---------------------------------------------------------------------------------------------------
	// Reflect: For the incident vector I and surface orientation N, the result is the reflection direction: I - 2 * dot(N,I) *	N
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> Reflect(const var_t<T, Assemble, C1>& I, const var_t<T, Assemble, C2>& N)
	{
		return make_ext_op2(I, N, [](const T& i, const T& n) {return glm::reflect(i, n); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Reflect);
	}
	//---------------------------------------------------------------------------------------------------

	// Refract: For the incident vector I and surface normal N, and the ratio of indices of refraction eta, the result is the refraction vector.
	// The result is computed by k = 1.0 - eta * eta * (1.0 - dot(N,I) * dot(N,I))
	// if k < 0.0 the result is 0.0	otherwise, the result is eta * I - (eta	* dot(N,I) + sqrt(k)) *	N
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<T, Assemble, spv::StorageClassFunction> Refract(const var_t<T, Assemble, C1>& I, const var_t<T, Assemble, C2>& N, const var_t<base_type_t<T>, Assemble, C3>& ETA)
	{
		return make_ext_op3(I, N, ETA, [](const T& i, const T& n, const base_type_t<T>& eta) {return glm::refract(i, n, eta); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Refract);
	}

	// Refract with constant ETA
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> Refract(const var_t<T, Assemble, C1>& I, const var_t<T, Assemble, C2>& N, const base_type_t<T>& ETA)
	{
		return Refract(I, N, var_t<base_type_t<T>, Assemble, spv::StorageClassFunction>(ETA));
	}

	//---------------------------------------------------------------------------------------------------
	// Clamp
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<T, Assemble, spv::StorageClassFunction> Clamp(const var_t<T, Assemble, C1>& X, const var_t<T, Assemble, C2>& Min, const var_t<T, Assemble, C3>& Max)
	{
		return make_ext_op3(X, Min, Max, [](const T& x, const T& min, const T& max) -> T{return glm::clamp(x, min, max); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450FClamp, GLSLstd450SClamp, GLSLstd450UClamp);
	}
	//---------------------------------------------------------------------------------------------------
	// Min
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> Min(const var_t<T, Assemble, C1>& X, const var_t<T, Assemble, C2>& Y)
	{
		return make_ext_op2(X, Y, [](const T& x, const T& y) -> T {return glm::min(x, y); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450FMin, GLSLstd450SMin, GLSLstd450UMin);
	}
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class ...Ts>
	inline var_t<T, Assemble, spv::StorageClassFunction> Min(const var_t<T, Assemble, C1>& X, const var_t<T, Assemble, C2>& Y, const Ts& ..._Args)
	{
		return Min(Min(X, Y), _Args...);
	}

	//---------------------------------------------------------------------------------------------------
	//Max
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> Max(const var_t<T, Assemble, C1>& X, const var_t<T, Assemble, C2>& Y)
	{
		return make_ext_op2(X, Y, [](const T& x, const T& y) -> T {return glm::max(x, y); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450FMax, GLSLstd450SMax, GLSLstd450UMax);
	}
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class ...Ts>
	inline var_t<T, Assemble, spv::StorageClassFunction> Max(const var_t<T, Assemble, C1>& X, const var_t<T, Assemble, C2>& Y, const Ts& ..._Args)
	{
		return Max(Max(X, Y), _Args...);
	}

	//---------------------------------------------------------------------------------------------------
	// Mix  linear blend of x and y , i.e., x * (1-a) + y*a
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<T, Assemble, spv::StorageClassFunction> Mix(const var_t<T, Assemble, C1>& X, const var_t<T, Assemble, C2>& Y, const var_t<T, Assemble, C3>& A)
	{
		return make_ext_op3(X, Y, A, [](const T& x, const T& y, const T& a) -> T {return glm::mix(x, y, a); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450FMix, GLSLstd450IMix);
	}
	//---------------------------------------------------------------------------------------------------
	// Step Result is 0.0 if x < edge; otherwise result is 1.0
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_base_float<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Step(const var_t<T, Assemble, C1>& Edge, const var_t<T, Assemble, C2>& X)
	{
		return make_ext_op2(Edge, X, [](const T& e, const T& x) -> T {return glm::step(e, x); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Step);
	}
	//---------------------------------------------------------------------------------------------------
	// SmoothStep 
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3, typename = std::enable_if_t<is_base_float<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> SmoothStep(const var_t<T, Assemble, C1>& Edge1, const var_t<T, Assemble, C2>& Edge2, const var_t<T, Assemble, C3>& X)
	{
		return make_ext_op3(Edge1, Edge2, X, [](const T& e1, const T& e2, const T& x) -> T {return glm::smoothstep(e1, e2, x); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450SmoothStep);
	}
	//---------------------------------------------------------------------------------------------------
	// HELPER FUNCTIONS
	//---------------------------------------------------------------------------------------------------

	// LERP
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<T, Assemble, spv::StorageClassFunction> Lerp(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r, const var_t<float, Assemble, C3> t)
	{
		return l * (1.f - t) + r * t;
		//return Mix(l, r, t);
	}

	//---------------------------------------------------------------------------------------------------
	// NDC to [0..1]
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> NDCToZeroOne(const var_t<T, Assemble, C1>& ndc)
	{
		return (ndc + 1.f) * 0.5f;
	}

	//---------------------------------------------------------------------------------------------------
	// NDC to range
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<T, Assemble, spv::StorageClassFunction> NDCToRange(const var_t<T, Assemble, C1>& ndc, const var_t<float, Assemble, C2>& low, const var_t<float, Assemble, C3> high)
	{
		return low + ((ndc + 1.f) * 0.5f * (high - low));
	}

	//---------------------------------------------------------------------------------------------------
	// returns size of the encapsulated type
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<uint32_t, Assemble, spv::StorageClassFunction> SizeOf(const var_t<T, Assemble, C1>& var)
	{
		// create variable initialized with constant
		if constexpr(Assemble)
		{
			return var_t<uint32_t, Assemble, spv::StorageClassFunction>(var.Type.GetSize());
		}
		else
		{
			//static_assert(is_struct<T> == false, "FromType not implemented for structures");
			return var_t<uint32_t, Assemble, spv::StorageClassFunction>(SPIRVType::FromType<T>().GetSize());
		}
	}

}; //!Tracy

#endif // !TRACY_SPIRVOPERATORIMPL_H
