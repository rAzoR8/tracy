#ifndef TRACY_SPIRVOPERATORIMPL_H
#define TRACY_SPIRVOPERATORIMPL_H

#include "SPIRVVariable.h"
#include "SPIRVAssembler.h"
#include <functional>
#include "GLM.h"

namespace Tracy
{
	//---------------------------------------------------------------------------------------------------
	template <class U, class V, class OpFunc, bool Assemble, spv::StorageClass C1, spv::StorageClass C2,  class T = std::invoke_result_t<OpFunc, const U&, const V&>, class ...Ops >
	inline var_t<T, Assemble, spv::StorageClassFunction> make_op(const var_t<U, Assemble, C1>& l, const var_t<V, Assemble, C2>& r, const OpFunc& _OpFunc, const Ops ..._Ops)
	{
		var_t<T, Assemble, spv::StorageClassFunction> var(TIntermediate(), _OpFunc(l.Value, r.Value));

		if constexpr(Assemble)
		{
			LoadVariables(l, r);

			spv::Op kType = (spv::Op)OpTypeDecider<base_type_t<T>>(_Ops...);
			HASSERT(kType != spv::OpNop, "Invalid variable base type!");

			SPIRVOperation Op(kType, var.uTypeHash, // result type
			{
				SPIRVOperand(kOperandType_Intermediate, l.uResultId),
				SPIRVOperand(kOperandType_Intermediate, r.uResultId)
			});

			var.uResultId = GlobalAssembler.AddOperation(Op);
		}

		return var;
	}
	//---------------------------------------------------------------------------------------------------
	template <class U, class OpFunc, bool Assemble, spv::StorageClass C1, class T = std::invoke_result_t<OpFunc, const U&>, class ...Ops >
	inline var_t<T, Assemble, spv::StorageClassFunction> make_ext_op1(const var_t<U, Assemble, C1>& l, const OpFunc& _OpFunc, const std::string& _sExt, const Ops ..._Ops)
	{
		var_t<T, Assemble, spv::StorageClassFunction> var(TIntermediate(), _OpFunc(l.Value));

		if constexpr(Assemble)
		{
			l.Load();

			uint32_t kType = OpTypeDecider<base_type_t<T>>(_Ops...);
			HASSERT(kType != spv::OpNop, "Invalid variable base type!");

			uint32_t uExtId = GlobalAssembler.GetExtensionId(_sExt);
			HASSERT(uExtId != HUNDEFINED32, "Invalid extension");

			SPIRVOperation Op(spv::OpExtInst, var.uTypeHash, // result type
			{
				SPIRVOperand(kOperandType_Intermediate, uExtId),
				SPIRVOperand(kOperandType_Literal, kType), // instr opcode
				SPIRVOperand(kOperandType_Intermediate, l.uResultId),
			});

			var.uResultId = GlobalAssembler.AddOperation(Op);
		}

		return var;
	}
	//---------------------------------------------------------------------------------------------------
	// OPERATOR IMPLEMENTATIONS
	//---------------------------------------------------------------------------------------------------

	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator+(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op(l, r, [](const T& v1, const T& v2)-> T {return v1 + v2; }, spv::OpFAdd, spv::OpIAdd);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator-(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op(l, r, [](const T& v1, const T& v2)-> T {return v1 - v2; }, spv::OpFSub, spv::OpISub);
	}
	//---------------------------------------------------------------------------------------------------
	template <class U, class V, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class T = longer_type_t<U,V>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator*(const var_t<U, Assemble, C1>& l, const var_t<V, Assemble, C2>& r)
	{
		return make_op(l, r, [](const U& v1, const V& v2)-> T {return v1 * v2; }, spv::OpFMul, spv::OpIMul);
	}
	//---------------------------------------------------------------------------------------------------
	template <class U, class V, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class T = longer_type_t<U, V>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator/(const var_t<U, Assemble, C1>& l, const var_t<V, Assemble, C2>& r)
	{
		return make_op(l, r, [](const U& v1, const V& v2)-> T {return v1 / v2; }, spv::OpFDiv, spv::OpSDiv, spv::OpUDiv);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator==(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op(l, r, [](const T& v1, const T& v2)-> bool {return v1 == v2; }, spv::OpLogicalEqual);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator!=(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op(l, r, [](const T& v1, const T& v2)-> bool {return v1 != v2; }, spv::OpLogicalNotEqual);
	}
	//---------------------------------------------------------------------------------------------------
	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator||(const var_t<bool, Assemble, C1>& l, const var_t<bool, Assemble, C2>& r)
	{
		return make_op(l, r, [](const T& v1, const T& v2)-> bool {return v1 || v2; }, spv::OpLogicalOr);
	}
	//---------------------------------------------------------------------------------------------------
	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator&&(const var_t<bool, Assemble, C1>& l, const var_t<bool, Assemble, C2>& r)
	{
		return make_op(l, r, [](const T& v1, const T& v2)-> bool {return v1 && v2; }, spv::OpLogicalAnd);
	}
	//---------------------------------------------------------------------------------------------------
	// GLSLstd450 EXTENSION
	//---------------------------------------------------------------------------------------------------

	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, C1> radians(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::radians(v1); }, ExtGLSL450, GLSLstd450Radians);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, C1> degrees(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::degrees(v1); }, ExtGLSL450, GLSLstd450Degrees);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, C1> sin(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::sin(v1); }, ExtGLSL450, GLSLstd450Sin);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, C1> cos(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::cos(v1); }, ExtGLSL450, GLSLstd450Cos);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, C1> tan(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::tan(v1); }, ExtGLSL450, GLSLstd450Tan);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, C1> asin(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::asin(v1); }, ExtGLSL450, GLSLstd450Asin);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, C1> acos(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::acos(v1); }, ExtGLSL450, GLSLstd450Acos);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, C1> atan(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::atan(v1); }, ExtGLSL450, GLSLstd450Atan);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, C1> sinh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::sinh(v1); }, ExtGLSL450, GLSLstd450Sinh);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, C1> cosh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::cos(v1); }, ExtGLSL450, GLSLstd450Cosh);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, C1> tanh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::tan(v1); }, ExtGLSL450, GLSLstd450Tanh);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, C1> asinh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::asinh(v1); }, ExtGLSL450, GLSLstd450Asinh);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, C1> acosh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::acosh(v1); }, ExtGLSL450, GLSLstd450Acosh);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, C1> atanh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::atanh(v1); }, ExtGLSL450, GLSLstd450Atanh);
	}
	//---------------------------------------------------------------------------------------------------
	// TODO: atan2

	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, Class> sqrt(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::sqrt(v1); }, ExtGLSL450, GLSLstd450Sqrt);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, Class> normalize(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::normalize(v1); }, ExtGLSL450, GLSLstd450Normalize);
	}
	//---------------------------------------------------------------------------------------------------

	template <class M, bool Assemble,
		spv::StorageClass C1, spv::StorageClass C2,
		class V = col_type_t<M>,
		class R = row_type_t<M>,
		typename = std::enable_if_t<is_matrix<M>>>
	inline var_t<R, Assemble, spv::StorageClassFunction> mul(
		const var_t<V, Assemble, C1>& l,
		const var_t<M, Assemble, C2>& r)
	{
		return make_op(l, r, [](const V& v, const M& m)-> R {return v * m; }, spv::OpVectorTimesMatrix);
	}
	//---------------------------------------------------------------------------------------------------
	
	template <class M, bool Assemble,
		spv::StorageClass C1, spv::StorageClass C2,
		class V = col_type_t<M>,
		class R = row_type_t<M>,
		typename = std::enable_if_t<is_matrix<M>>>
		inline var_t<V, Assemble, spv::StorageClassFunction> mul(
			const var_t<M, Assemble, C1>& l,
			const var_t<R, Assemble, C2>& r)
	{
		return make_op(l, r, [](const M& m, const R& v)-> V {return m * v; }, spv::OpMatrixTimesVector);
	}
	//---------------------------------------------------------------------------------------------------

}; //!Tracy

#endif // !TRACY_SPIRVOPERATORIMPL_H
