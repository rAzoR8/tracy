#ifndef TRACY_SPIRVOPERATORIMPL_H
#define TRACY_SPIRVOPERATORIMPL_H

#include "SPIRVVariable.h"
#include "SPIRVAssembler.h"
#include <vulkan\GLSL.std.450.h>

namespace Tracy
{
	//---------------------------------------------------------------------------------------------------
	template <class U, class V, class OpFunc, bool Assemble, spv::StorageClass C1, spv::StorageClass C2,  class T = std::invoke_result_t<OpFunc, const U&, const V&>, class ...Ops >
	inline var_t<T, Assemble, spv::StorageClassFunction> make_op(const var_t<U, Assemble, C1>& l, const var_t<V, Assemble, C2>& r, const OpFunc& _OpFunc, const EOpTypeBase _kOpTypeBase, const Ops ..._Ops)
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
			var.Value = _OpFunc(v1.Value, v2.Value, v3);
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
		return make_op(l, r, [](const T& v1, const T& v2)-> T {return v1 + v2; }, kOpTypeBase_Result, spv::OpFAdd, spv::OpIAdd);
	}
	// add with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator+(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) + r;
	}
	// add with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator+(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l + var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}
	//---------------------------------------------------------------------------------------------------
	// SUB
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator-(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op(l, r, [](const T& v1, const T& v2)-> T {return v1 - v2; }, kOpTypeBase_Result, spv::OpFSub, spv::OpISub);
	}
	// sub with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator-(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) - r;
	}
	// sub with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
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
			return make_op(l, r, [](const U& v1, const V& v2) -> T {return v1 * v2; }, kOpTypeBase_Result, spv::OpVectorTimesScalar);
		else if constexpr(is_vector<V> && is_scalar<U>)
			return make_op(r, l, [](const V& v1, const U& v2) -> T {return v1 * v2; }, kOpTypeBase_Result, spv::OpVectorTimesScalar);
		else if constexpr(is_matrix<V> || is_matrix<U>)
			return Mul(l, r); // implementation below
		else
			return make_op(l, r, [](const U& v1, const V& v2) -> T {return v1 * v2; }, kOpTypeBase_Result, spv::OpFMul, spv::OpIMul);
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

	//---------------------------------------------------------------------------------------------------
	// DIV
	template <class U, class V, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class T = longer_type_t<U, V>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator/(const var_t<U, Assemble, C1>& l, const var_t<V, Assemble, C2>& r)
	{
		return make_op(l, r, [](const U& v1, const V& v2)-> T {return v1 / v2; }, kOpTypeBase_Result, spv::OpFDiv, spv::OpSDiv, spv::OpUDiv); // kOpTypeBase_Operand1
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
		return make_op(l, r, [](const T& v1, const T& v2)-> bool {return v1 == v2; }, kOpTypeBase_Result, spv::OpLogicalEqual);
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
		return make_op(l, r, [](const T& v1, const T& v2)-> bool {return v1 != v2; }, kOpTypeBase_Result, spv::OpLogicalNotEqual);
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
		return make_op(l, r, [](const bool& v1, const bool& v2)-> bool {return v1 || v2; }, kOpTypeBase_Result, spv::OpLogicalOr);
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
		return make_op(l, r, [](const bool& v1, const bool& v2)-> bool {return v1 && v2; }, kOpTypeBase_Result, spv::OpLogicalAnd);
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
	// Less
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator<(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op(l, r, [](const T& v1, const T& v2)-> bool {return v1 < v2; }, kOpTypeBase_Operand1, spv::OpFOrdLessThan, spv::OpSLessThan, spv::OpULessThan);
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
		return make_op(l, r, [](const T& v1, const T& v2)-> bool {return v1 <= v2; }, kOpTypeBase_Operand1, spv::OpFOrdLessThanEqual, spv::OpSLessThanEqual, spv::OpULessThanEqual);
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
		return make_op(l, r, [](const T& v1, const T& v2)-> bool {return v1 > v2; }, kOpTypeBase_Operand1, spv::OpFOrdGreaterThan, spv::OpSGreaterThan, spv::OpUGreaterThan);
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
		return make_op(l, r, [](const T& v1, const T& v2)-> bool {return v1 >= v2; }, kOpTypeBase_Operand1, spv::OpFOrdGreaterThanEqual, spv::OpSGreaterThanEqual, spv::OpUGreaterThanEqual);
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
	// DOT
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_float<T>>>
	inline var_t<base_type_t<T>, Assemble, spv::StorageClassFunction> Dot(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op(l, r, [](const T& u, const T& v)-> base_type_t<T> {return glm::dot(u, v); }, kOpTypeBase_Result, spv::OpDot);
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
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Atanh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::atanh(v1); }, ExtGLSL450, GLSLstd450Atanh);
	}
	//---------------------------------------------------------------------------------------------------
	// TODO: atan2 etc

	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> Sqrt(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::sqrt(v1); }, ExtGLSL450, GLSLstd450Sqrt);
	}
	//---------------------------------------------------------------------------------------------------
	// NORMALIZE
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> Normalize(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::normalize(v1); }, ExtGLSL450, GLSLstd450Normalize);
	}
	//---------------------------------------------------------------------------------------------------
	// LENGTH
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<base_type_t<T>, Assemble, spv::StorageClassFunction> Length(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::length(v1); }, ExtGLSL450, GLSLstd450Length);
	}
	//---------------------------------------------------------------------------------------------------
	// DISTANCE
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<base_type_t<T>, Assemble, spv::StorageClassFunction> Distance(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_ext_op2(l, r, [](const T& v1, const T& v2) {return glm::distance(v1, v2); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Distance);
	}
	//---------------------------------------------------------------------------------------------------
	// CROSS
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2/*, class T = vec_type_t<FloatT, 3>*/>
	inline var_t<T, Assemble, spv::StorageClassFunction> Cross(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_ext_op2(l, r, [](const T& v1, const T& v2) -> T{return glm::cross(v1, v2); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Cross);
	}
	//---------------------------------------------------------------------------------------------------
	// FMA
	template <class A, class B, class C, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3,
		typename = std::enable_if_t<is_base_float<A> && is_base_float<B> && is_base_float<C>>>
	inline auto Fma(const var_t<A, Assemble, C1>& va, const var_t<B, Assemble, C2>& vb, const var_t<C, Assemble, C3>& vc)
	{
		return make_ext_op3(va, vb, vc, [](const A& a, const B& b, const C& c) {return a * b + c; }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Fma);
	}

	//---------------------------------------------------------------------------------------------------
	// MUL
	// vector * matrix
	template <class M, bool Assemble,spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_matrix<M>>>
		inline var_t<row_type_t<M>, Assemble, spv::StorageClassFunction> Mul(
			const var_t<col_type_t<M>, Assemble, C1>& l,
			const var_t<M, Assemble, C2>& r)
	{
		return make_op(l, r, [](const col_type_t<M>& v, const M& m)-> row_type_t<M> {return v * m; }, kOpTypeBase_Result, spv::OpVectorTimesMatrix);
	}
	//---------------------------------------------------------------------------------------------------
	// matrix * vector
	template <class M, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_matrix<M>>>
		inline var_t<col_type_t<M>, Assemble, spv::StorageClassFunction> Mul(
			const var_t<M, Assemble, C1>& l,
			const var_t<row_type_t<M>, Assemble, C2>& r)
	{
		return make_op(l, r, [](const M& m, const row_type_t<M>& v)-> col_type_t<M> {return m * v; }, kOpTypeBase_Result, spv::OpMatrixTimesVector);
	}

	// matrix * matrix
	//---------------------------------------------------------------------------------------------------
	template <bool Assemble,
		spv::StorageClass C1, spv::StorageClass C2,
		class M, class N,
		class MRow = row_type_t<M>,
		class MCol = col_type_t<M>,
		class NRow = row_type_t<N>,
		class NCol = col_type_t<N>,
		class R = mat_type_t<NRow, MCol>,
		typename = std::enable_if_t<std::is_same_v<MRow, NCol>>
		>
		inline var_t<R, Assemble, spv::StorageClassFunction> Mul(
			const var_t<M, Assemble, C1>& l,
			const var_t<N, Assemble, C2>& r)
	{
		return make_op(l, r, [](const M& m, const N& n)-> R {return m * n; }, kOpTypeBase_Result, spv::OpMatrixTimesMatrix);
	}

	//---------------------------------------------------------------------------------------------------

}; //!Tracy

#endif // !TRACY_SPIRVOPERATORIMPL_H
