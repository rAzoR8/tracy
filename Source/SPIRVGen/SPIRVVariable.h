#ifndef TRACY_SPIRVVARIABLE_H
#define TRACY_SPIRVVARIABLE_H

#include "GetStructMember.h"
#include "SPIRVDecoration.h"
#include "SPIRVType.h"
#include "SPIRVAssembler.h"
#include <array>

namespace Tracy
{
	enum EOpTypeBase : uint32_t
	{
		kOpTypeBase_Result,
		kOpTypeBase_Operand1,
		kOpTypeBase_Operand2,
		kOpTypeBase_Operand3
	};

	constexpr uint32_t kAlignmentSize = 16u;

	template <bool Assemble>
	struct var_decoration {};

	template <>
	struct var_decoration<false>
	{
		template <class... Ts>
		var_decoration(Ts&& ... _args) noexcept {} // consume arguments
		//var_decoration(const var_decoration& _Other) {}
		//var_decoration(var_decoration&& _Other) noexcept {}
		inline const var_decoration& operator=(var_decoration&& _Other) const noexcept { return *this; }
		inline const var_decoration& operator=(const var_decoration& _Other) const noexcept { return *this; }
		template <class T>
		inline const var_decoration& operator=(T&& _Other) const { return *this; }
		template <class T>
		inline const var_decoration& operator=(const T& _Other) const { return *this; }
		inline void Store() const noexcept {};
		inline uint32_t Load() const noexcept { return HUNDEFINED32; };
		inline void Decorate(const SPIRVDecoration& _Decoration) noexcept {};
		inline void SetBinding(const uint32_t _uBinding, const uint32_t uDescriptorSet) noexcept {}
		inline void SetLocation(const uint32_t _uLocation) noexcept {}
		inline void SetIdentifier(const uint32_t _uIdentifier) noexcept {}
		inline void MaterializeDecorations() const noexcept {};
	};

	template <>
	struct var_decoration<true>
	{
		mutable uint32_t uVarId = HUNDEFINED32; // result id OpVar or OpAccessChain
		mutable uint32_t uResultId = HUNDEFINED32; // result of arithmetic instructions or OpLoad
		mutable uint32_t uLastStoredId = HUNDEFINED32;
		mutable uint32_t uBaseId = HUNDEFINED32; // base VarId from parent structure
		mutable uint32_t uBaseTypeId = HUNDEFINED32; // type of base parent sturcture
		spv::StorageClass kStorageClass = spv::StorageClassMax;
		mutable uint32_t uTypeId = HUNDEFINED32;
		uint32_t uMemberOffset = HUNDEFINED32;
		uint32_t uMemberIndex = HUNDEFINED32; // relative to the parent sturcture

		uint32_t uDescriptorSet = HUNDEFINED32; // res input
		uint32_t uBinding = HUNDEFINED32; // local to res input
		uint32_t uLocation = HUNDEFINED32; // res output
		uint32_t uSpecConstId = HUNDEFINED32; // used in vulkan api to set data for specialization
		uint32_t uInputAttachmentIndex = HUNDEFINED32; // subpass output index
		mutable bool bTexSampled = false; // indicates that the var texture has been sampled in the code
		mutable bool bTexStored = false; // indicates that the var texture has been stored in the code
		bool bInstanceData = false; // only valid for StorageClassInput in vertex stage
		mutable bool bMaterializedName = false;

		std::string sName; // user can set this to identify the variable stored in the module

		// for structs
		std::vector<uint32_t> AccessChain;
		SPIRVOperation* pVarOp = nullptr;

		SPIRVType Type;
		mutable std::vector<SPIRVDecoration> Decorations;

		void Decorate(const SPIRVDecoration& _Decoration);
		void MaterializeDecorations() const;
		void SetBinding(const uint32_t _uBinding, const uint32_t uDescriptorSet);
		void SetLocation(const uint32_t _uLocation);
		void SetName(const std::string& _sName);

		void Store() const;
		uint32_t Load(const bool _bForceLoad = false) const;

		var_decoration(const spv::StorageClass _kStorageClass) : kStorageClass(_kStorageClass) {};
		var_decoration(const var_decoration<true>& _Other);
		var_decoration(var_decoration<true>&& _Other) noexcept;
		virtual ~var_decoration();

		const var_decoration& operator=(const var_decoration& _Other) const;
		const var_decoration& operator=(var_decoration&& _Other) const noexcept;
	};

	//---------------------------------------------------------------------------------------------------

	struct TIntermediate {};

	template <typename T, bool Assemble = true, spv::StorageClass Class = spv::StorageClassFunction>
	struct var_t : public var_decoration<Assemble>
	{
		typedef TSPVVarTag SPVVarTag;
		typedef T ValueType;

		mutable T Value;

		using BaseType = base_type_t<T>;

		// generates OpVar
		template <class... Ts>
		var_t(const Ts& ... _args);

		// does not generate OpVar, uResultId needs to be assigned
		template <class... Ts>
		var_t(TIntermediate, const Ts& ... _args);

		// calls SetName
		var_t(const char* _sName);

		template <spv::StorageClass C1>
		var_t(var_t<T, Assemble, C1>&& _Other);
		template <spv::StorageClass C1>
		var_t(const var_t<T, Assemble, C1>& _Other);

		// direct constant assign
		const var_t& operator=(const T& _Other) const;
		const var_t& operator=(T&& _Other) const;

#pragma region conversion_assignment
		template <class U, spv::StorageClass C1>
		const var_t& operator=(const var_t<U, Assemble, C1>& _Other) const
		{
			constexpr bool bConvertible = is_convertible<U, BaseType> && Dimmension<U> == Dimmension<T>;
			if constexpr(std::is_same_v<U, T>)
			{
				var_decoration<Assemble>::operator=(_Other);
				Value = _Other.Value;
			}
			else if constexpr(bConvertible)
			{
				Value = (T)_Other.Value; // std memcopy?

				if constexpr(Assemble)
				{
					_Other.Load();

					spv::Op kType = GetConvertOp<U, T>();
					HASSERT(kType != spv::OpNop, "Invalid variable type conversion!");
					SPIRVOperation Op(kType, uTypeId, SPIRVOperand(kOperandType_Intermediate, _Other.uResultId));
					uResultId = GlobalAssembler.AddOperation(Op);
					Store();
				}
			}
			return *this;
		}
#pragma endregion

		//template <spv::StorageClass C1>
		//const var_t& operator=(const var_t<T, Assemble, C1>& _Other) const;
		template <spv::StorageClass C1>
		const var_t& operator=(var_t<T, Assemble, C1>&& _Other) const;

		template <spv::StorageClass C1>
		const var_t& operator+=(const var_t<T, Assemble, C1>& _Other) const;
		template <spv::StorageClass C1>
		const var_t& operator-=(const var_t<T, Assemble, C1>& _Other) const;

		template <class U, typename = std::enable_if_t<is_convertible<U, BaseType>>>
		const var_t& operator+=(const U& _Other) const { return operator+=(var_t<T, Assemble, spv::StorageClassFunction>((BaseType)_Other)); }
		template <class U, typename = std::enable_if_t<is_convertible<U, BaseType>>>
		const var_t& operator-=(const U& _Other) const { return operator-=(var_t<T, Assemble, spv::StorageClassFunction>((BaseType)_Other)); }

		template <class U, spv::StorageClass C1>
		const var_t& operator*=(const var_t<U, Assemble, C1>& _Other) const;

		// mutable mul with constant
		template <class U, typename = std::enable_if_t<is_convertible<U, BaseType>>>
		const var_t& operator*=(const U& _Other) const { return operator*=(var_t<BaseType, Assemble, spv::StorageClassFunction>((BaseType)_Other));	}
	
		template <class U, spv::StorageClass C1>
		const var_t& operator/=(const var_t<U, Assemble, C1>& _Other) const;
		
		// mutable div with constant
		template <class U, typename = std::enable_if_t<is_convertible<U, BaseType>>>
		const var_t& operator/=(const U& _Other) const { return operator*=(var_t<BaseType, Assemble, spv::StorageClassFunction>((BaseType)1 / (BaseType)_Other)); }
		
		var_t<T, Assemble, spv::StorageClassFunction> operator!() const;

		const var_t& operator++() const; // mutable
		var_t<T, Assemble, spv::StorageClassFunction> operator++(int) const; // immutable

		const var_t& operator--() const; // mutable
		var_t<T, Assemble, spv::StorageClassFunction> operator--(int) const; // immutable

		const T* operator->() const { return &Value; }

#pragma region ArrayAccess
		var_t<uint32_t, Assemble, spv::StorageClassFunction> Length() const
		{
			static_assert(is_array<T>, "Unsupported type (array expected)");
			return var_t<uint32_t, Assemble, spv::StorageClassFunction>(T::Size);
		}

		template <spv::StorageClass C1, class U = T, typename = std::enable_if_t<is_array<U>>>
		var_t<array_element_t<U>, Assemble, Class> operator[](const var_t<uint32_t, Assemble, C1>& _Index) const
		{
			static_assert(is_array<U>, "Unsupported type (array expected)");
			auto var = var_t<array_element_t<U>, Assemble, spv::StorageClassFunction>(TIntermediate(), Value[_Index.Value]);

			if constexpr(Assemble)
			{
				const uint32_t uIndexId = _Index.Load();

				const uint32_t uPtrTypeId = GlobalAssembler.AddType(SPIRVType::Pointer(var.Type, kStorageClass));
				SPIRVOperation OpAccessChain(spv::OpAccessChain, uPtrTypeId, SPIRVOperand(kOperandType_Intermediate, uBaseId != HUNDEFINED32 ? uBaseId : uVarId));

				for (const uint32_t& uMemberIdx : AccessChain)
				{
					OpAccessChain.AddIntermediate(GlobalAssembler.AddConstant(SPIRVConstant::Make<false>(uMemberIdx)));
				}

				OpAccessChain.AddIntermediate(uIndexId);

				var.uVarId = GlobalAssembler.AddOperation(OpAccessChain);
			}

			return var;
		}

#pragma endregion

#pragma region VectorAccess
		template <size_t Dim, uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3>
		static constexpr bool Monotonic = !((Dim >= 1 && v0 != 0) || (Dim >= 2 && v1 != 1) || (Dim >= 3 && v2 != 2) || (Dim >= 4 && v3 != 3));

		template <size_t Dim>
		using TExtractType = var_t<vec_type_t<BaseType, Dim>, Assemble, spv::StorageClassFunction>;

#include "SPIRVVectorComponentAccess.h"
#pragma endregion

#pragma region sample tex
		template <
			spv::StorageClass C1,
			spv::StorageClass C2,
			class TexCompT = tex_component_t<T>,
			class TexCoordT = tex_coord_t<T>,
			typename = std::enable_if_t<is_texture<T>>>
			var_t<TexCompT, Assemble, spv::StorageClassFunction> Sample(const var_t<sampler_t, Assemble, C1>& _Sampler, const var_t<TexCoordT, Assemble, C2>& _Coords) const
		{
			auto var = var_t<TexCompT, Assemble, spv::StorageClassFunction>(TIntermediate());

			if constexpr(Assemble)
			{
				bTexSampled = true;

				// Result Type must be a vector of four components of floating point type or integer type.
				// Its components must be the same as Sampled Type of the underlying OpTypeImage(unless that underlying	Sampled Type is OpTypeVoid).
				using BaseRetType = base_type_t<TexCompT>;
				using ReturnType = vec_type_t<BaseRetType, 4>;
				const uint32_t uReturnTypeId = GlobalAssembler.AddType(SPIRVType::FromType<ReturnType>());

				// create SampledImageType if it did not exist yet
				const uint32_t uSampledImgType = GlobalAssembler.AddType(SPIRVType::SampledImage(Type));

				const uint32_t uImageId = Load();
				const uint32_t uSamplerId = _Sampler.Load();

				// OpSampledImage uSampledImgType ImgId SamplerId
				SPIRVOperation OpSampledImage(spv::OpSampledImage, uSampledImgType);
				OpSampledImage.AddIntermediate(uImageId);
				OpSampledImage.AddIntermediate(uSamplerId);

				const uint32_t uOpSampledImageId = GlobalAssembler.AddOperation(OpSampledImage);
				const uint32_t uCoordId = _Coords.Load();

				// OpImageSampleImplicitLod uReturnTypeId uOpSampledImageId uCoordId
				SPIRVOperation OpSampleImageImplicitLod(spv::OpImageSampleImplicitLod, uReturnTypeId);
				OpSampleImageImplicitLod.AddIntermediate(uOpSampledImageId);
				OpSampleImageImplicitLod.AddIntermediate(uCoordId);

				const uint32_t uSampleResultId = GlobalAssembler.AddOperation(OpSampleImageImplicitLod);
				if constexpr(std::is_same_v<TexCompT, ReturnType> == false)
				{
					const uint32_t uRealReturnTypeId = GlobalAssembler.AddType(SPIRVType::FromType<TexCompT>());
					const uint32_t uElemTypeId = GlobalAssembler.AddType(SPIRVType::FromType<BaseRetType>());

					SPIRVOperation OpConstruct(spv::OpCompositeConstruct, uRealReturnTypeId);

					for (uint32_t n = 0u; n < Dimmension<TexCompT>; ++n)
					{
						SPIRVOperation OpExtract(spv::OpCompositeExtract, uElemTypeId, SPIRVOperand(kOperandType_Intermediate, uSampleResultId)); // var id to extract from
						OpExtract.AddLiteral(n); // extraction index

						uint32_t uId = GlobalAssembler.AddOperation(OpExtract);
						OpConstruct.AddIntermediate(uId);
					}

					// composite constructs treated as intermediates as they cant be loaded
					var.uResultId = GlobalAssembler.AddOperation(OpConstruct);
				}
				else
				{
					var.uResultId = uSampleResultId;
				}
			}

			return var;
		}

#pragma endregion

	private:

		template <class... Ts>
		void InitVar(const Ts& ..._args);

#pragma region InsertComponent
		// identity
		template <
			size_t Dim,
			uint32_t v0,
			uint32_t v1 = HUNDEFINED32,
			uint32_t v2 = HUNDEFINED32,
			uint32_t v3 = HUNDEFINED32,
			spv::StorageClass C1,
			typename = std::enable_if_t<is_vector<T> && Dim == Dimmension<T> && Monotonic<Dim, v0, v1, v2, v3>>>
			const var_t& InsertComponent(const var_t<T, Assemble, C1>& _Var) const
		{
			return operator=(_Var);
		}

		// swizzle / shuffle
		template <
			size_t Dim,
			uint32_t v0,
			uint32_t v1 = HUNDEFINED32,
			uint32_t v2 = HUNDEFINED32,
			uint32_t v3 = HUNDEFINED32,
			spv::StorageClass C1,
			class VecT = vec_type_t<BaseType, Dim>,
			typename = std::enable_if_t<is_vector<T>>>
			const var_t& InsertComponent(const var_t<VecT, Assemble, C1>& _Var) const
		{
			if constexpr(Assemble == false)
			{
				if constexpr(Dim > 1)
				{
					if constexpr(is_valid_index<T, v0>() && is_valid_index<VecT, 0>()) Value[v0] = _Var.Value[0];
					if constexpr(is_valid_index<T, v1>() && is_valid_index<VecT, 1>()) Value[v1] = _Var.Value[1];
					if constexpr(is_valid_index<T, v2>() && is_valid_index<VecT, 2>()) Value[v2] = _Var.Value[2];
					if constexpr(is_valid_index<T, v3>() && is_valid_index<VecT, 3>()) Value[v3] = _Var.Value[3];
				}
				else
				{
					if constexpr(Dimmension<T> > 1 && is_valid_index<T, v0>())
					{
						Value[v0] = _Var.Value;
					}
					else
					{
						Value = _Var.Value;
					}
				}
			}
			else if (uSpecConstId == HUNDEFINED32)
			{
				// vector 1 (this) + vector 2
				// xyzw xy
				// 0123 45
				// vector1.xz = vector2.xy
				// 4153

				constexpr uint32_t N = Dimmension<T>;
				const std::array<uint32_t, 4> Indices = {v0, v1, v2, v3};
				std::vector<uint32_t> Target(N);
		
				uint32_t n = N;
				for (uint32_t i = 0; i < N; ++i)
				{
					const uint32_t& j = Indices[i];
					Target[i] = i;// copy from vector 1
					if (j < Dim)
					{
						Target[j] = n++; // take from concated vector 2
					}
				}
				//HASSERT(n == Dim+N, "Index missmatch");

				Load();
				_Var.Load();

				SPIRVOperation OpVectorShuffle(spv::OpVectorShuffle, uTypeId);
				OpVectorShuffle.AddIntermediate(uResultId); // vector 1
				OpVectorShuffle.AddIntermediate(_Var.uResultId); // vector 2
				OpVectorShuffle.AddLiterals(Target);
				
				uResultId = GlobalAssembler.AddOperation(OpVectorShuffle);

				Store();
			}

			return *this;
		}

#pragma endregion

#pragma region ExtractComponent		
		// swizzle / shuffle
		template <
			size_t Dim,
			uint32_t v0,
			uint32_t v1 = HUNDEFINED32,
			uint32_t v2 = HUNDEFINED32,
			uint32_t v3 = HUNDEFINED32,
			class VecT = vec_type_t<BaseType, Dim>> // not a struct
			var_t<VecT, Assemble, spv::StorageClassFunction> ExtractComponent() const
		{
			auto var = var_t<VecT, Assemble, spv::StorageClassFunction>(TIntermediate());

			if constexpr(Assemble == false)
			{
				if constexpr(Dim > 1)
				{
					if constexpr(is_valid_index<T, v0>()) var.Value[0] = Value[v0];
					if constexpr(is_valid_index<T, v1>()) var.Value[1] = Value[v1];
					if constexpr(is_valid_index<T, v2>()) var.Value[2] = Value[v2];
					if constexpr(is_valid_index<T, v3>()) var.Value[3] = Value[v3];
				}
				else
				{
					var.Value = Value[v0];
				}
			}
			else // Assemble
			{
				Load();

				// identity
				if constexpr(std::is_same_v<VecT, T> && Monotonic<Dim, v0, v1, v2, v3>)
				{
					var.uResultId = uResultId;
					return var;
				}

				const uint32_t uElemTypeId = GlobalAssembler.AddType(SPIRVType::FromType<base_type_t<T>>());
				std::array<uint32_t, 4> Indices = { v0, v1, v2, v3 };
				SPIRVOperation Op;

				if constexpr(Dim > 1)
				{
					if constexpr(std::is_same_v<VecT, T>)// VectorShuffle
					{
						Op = SPIRVOperation(spv::OpVectorShuffle, var.uTypeId);
						Op.AddIntermediate(uResultId); // comp1
						Op.AddIntermediate(uResultId); // comp2
						for (const uint32_t& i : Indices)
						{
							if (i < 4u)
							{
								Op.AddLiteral(i); // extraction index
							}
						}
					}
					else // extract and construct
					{
						Op = SPIRVOperation(spv::OpCompositeConstruct, var.uTypeId);
						for (const uint32_t& i : Indices)
						{
							if (i < 4u)
							{
								SPIRVOperation OpExtract(spv::OpCompositeExtract, uElemTypeId, SPIRVOperand(kOperandType_Intermediate, uResultId)); // var id to extract from
								OpExtract.AddLiterals(AccessChain);
								OpExtract.AddLiteral(i); // extraction index
								Op.AddIntermediate(GlobalAssembler.AddOperation(OpExtract));
							}
						}
					}
				}
				else // Dim == 1
				{
					// TODO: use AccessChain instead?
					Op = SPIRVOperation(spv::OpCompositeExtract, uElemTypeId, SPIRVOperand(kOperandType_Intermediate, uResultId)); // var id to extract from
					Op.AddLiteral(v0); // extraction index
				}

				var.uResultId = GlobalAssembler.AddOperation(Op);
			}

			return var;
		}
#pragma endregion

	private:
		// two operands (self + other) mutible
		template <class U, class OpFunc, spv::StorageClass C1, class ...Ops>
		const var_t<T, Assemble, Class>& make_op2(const var_t<U, Assemble, C1>& _Other, const OpFunc& _OpFunc, const Ops ..._Ops) const;

		// one operand (self) immutable
		template <class OpFunc, class ...Ops>
		var_t<T, Assemble, spv::StorageClassFunction> make_op1_immutable(const OpFunc& _OpFunc, const Ops ..._Ops) const;

		// one operand (self) mutable
		template <class OpFunc, class ...Ops>
		const var_t<T, Assemble, spv::StorageClassFunction>& make_op1_mutable(const OpFunc& _OpFunc, const Ops ..._Ops) const;
	};

	//---------------------------------------------------------------------------------------------------
	// HELPER FUNCTIONS
	//---------------------------------------------------------------------------------------------------
#pragma region helper_functions
	//---------------------------------------------------------------------------------------------------
	template <class T>
	inline uint32_t OpTypeDecider(const uint32_t _kOp)
	{
		return _kOp;
	}

	template <class OperandType>
	uint32_t OpTypeDecider(const uint32_t _FloatOp, const uint32_t _SIntOp, const uint32_t _UIntOp = spv::OpNop, const spv::Op _BoolOp = spv::OpNop)
	{
		if (std::is_same_v<OperandType, float>)
			return _FloatOp;

		if (std::is_same_v<OperandType, bool>)
			return _BoolOp;

		if (_UIntOp == spv::OpNop)
		{
			if (std::is_same_v<OperandType, int32_t> || std::is_same_v<OperandType, uint32_t>)
				return _SIntOp;
		}
		else
		{
			if (std::is_same_v<OperandType, int32_t>)
				return _SIntOp;
			else if (std::is_same_v<OperandType, uint32_t>)
				return _UIntOp;
		}

		return spv::OpNop;
	}

	template <class Result, class Operand1 = Result, class Operand2 = Result, class Operand3 = Result, class ...Ops>
	uint32_t OpTypeDeciderEx(const EOpTypeBase _kOpBase, const Ops ..._Ops)
	{
		if constexpr(sizeof...(_Ops) == 1)
		{
			return OpTypeDecider<base_type_t<Result>>(_Ops...);
		}
		else
		{
			switch (_kOpBase)
			{
			case kOpTypeBase_Result: return OpTypeDecider<base_type_t<Result>>(_Ops...);
			case kOpTypeBase_Operand1: return OpTypeDecider<base_type_t<Operand1>>(_Ops...);
			case kOpTypeBase_Operand2: return OpTypeDecider<base_type_t<Operand2>>(_Ops...);
			case kOpTypeBase_Operand3: return OpTypeDecider<base_type_t<Operand3>>(_Ops...);
			default: return spv::OpNop;
			}
		}
	}

	//---------------------------------------------------------------------------------------------------

	template <class U, spv::StorageClass C1, class ...Ts>
	inline void LoadVariables(const var_t<U, true, C1>& var, const Ts& ... vars)
	{
		var.Load();

		if constexpr(sizeof...(vars) > 0)
		{
			LoadVariables(vars...);
		}
	}

	//---------------------------------------------------------------------------------------------------
	// make operation with mutable operation with two operands (self + other)
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class U, class OpFunc, spv::StorageClass C1, class ...Ops>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::make_op2(const var_t<U, Assemble, C1>& _Other, const OpFunc& _OpFunc, const Ops ..._Ops) const
	{
		if constexpr(Assemble == false)
		{
			_OpFunc(Value, _Other.Value);
		}
		else if(uSpecConstId == HUNDEFINED32) // Assemble
		{
			LoadVariables(*this, _Other);

			spv::Op kOpCode = (spv::Op)OpTypeDecider<BaseType>(_Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			SPIRVOperation Op(kOpCode, uTypeId, // result type
			{
				SPIRVOperand(kOperandType_Intermediate, uResultId),
				SPIRVOperand(kOperandType_Intermediate, _Other.uResultId)
			});

			uResultId = GlobalAssembler.AddOperation(Op);

			Store();
		}

		return *this;
	}

	//---------------------------------------------------------------------------------------------------
	// make immutable operation (returns intermediate var) with one operand (self)
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class OpFunc, class ...Ops>
	inline var_t<T, Assemble, spv::StorageClassFunction> var_t<T, Assemble, Class>::make_op1_immutable(const OpFunc& _OpFunc, const Ops ..._Ops) const
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc(Value);
		}
		else // Assemble
		{
			Load();

			spv::Op kOpCode = OpTypeDecider<BaseType>(_Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");
			HASSERT(uTypeId != HUNDEFINED32, "Invalid type");

			SPIRVOperation Op(kOpCode, uTypeId, SPIRVOperand(kOperandType_Intermediate, uResultId));
			var.uResultId = GlobalAssembler.AddOperation(Op);
		}

		return var;
	}
	//---------------------------------------------------------------------------------------------------
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class OpFunc, class ...Ops>
	inline const var_t<T, Assemble, spv::StorageClassFunction>& var_t<T, Assemble, Class>::make_op1_mutable(const OpFunc& _OpFunc, const Ops ..._Ops) const
	{
		if constexpr(Assemble == false)
		{
			_OpFunc(Value);
		}
		else if(uSpecConstId == HUNDEFINED32) // Assemble
		{
			Load();

			spv::Op kOpCode = (spv::Op)OpTypeDecider<BaseType>(_Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			SPIRVOperation Op(kOpCode, uTypeId, SPIRVOperand(kOperandType_Intermediate, uResultId));

			uResultId = GlobalAssembler.AddOperation(Op);

			Store();
		}

		return *this;
	}
	//---------------------------------------------------------------------------------------------------

#pragma endregion

	//---------------------------------------------------------------------------------------------------
	// CONSTRUCTORS
	//---------------------------------------------------------------------------------------------------

#pragma region constructors
	//---------------------------------------------------------------------------------------------------
	// move constructor
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline var_t<T, Assemble, Class>::var_t(var_t<T, Assemble, C1>&& _Other) :
		Value(std::move(_Other.Value)),
		var_decoration<Assemble>(std::forward<var_t<T, Assemble, C1>>(_Other))
	{
	}
	//---------------------------------------------------------------------------------------------------
	// copy constructor
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline var_t<T, Assemble, Class>::var_t(const var_t<T, Assemble, C1>& _Other) :
		var_decoration<Assemble>(_Other),
		Value(_Other.Value)
	{
	}

	//---------------------------------------------------------------------------------------------------
	// name constructor
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, Class>::var_t(const char* _sName) : 
		var_decoration<Assemble>(Class)
	{
		SetName(_sName);
		InitVar();
	}

	//---------------------------------------------------------------------------------------------------
	// constant assign operator
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator=(const T& _Other) const
	{
		var_decoration<Assemble>::operator=(var_t<T, Assemble, spv::StorageClassFunction>(_Other));
		Value = _Other;
		return *this;
	}
	//---------------------------------------------------------------------------------------------------
	// constant move operator
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator=(T && _Other) const
	{
		var_decoration<Assemble>::operator=(var_t<T, Assemble, spv::StorageClassFunction>(std::forward<T>(_Other)));
		Value = std::move(_Other);
		return *this;
	}
	//---------------------------------------------------------------------------------------------------
	// assign operator
	//template<typename T, bool Assemble, spv::StorageClass Class>
	//template<spv::StorageClass C1>
	//inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator=(const var_t<T, Assemble, C1>& _Other) const
	//{
	//	var_decoration<Assemble>::operator=(_Other);
	//	Value = _Other.Value;
	//	return *this;
	//}
	//---------------------------------------------------------------------------------------------------
	// move operator
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator=(var_t<T, Assemble, C1>&& _Other) const
	{
		Value = std::move(_Other.Value);
		var_decoration<Assemble>::operator=(std::forward<var_t<T, Assemble, C1>>(_Other));
		return *this;
	}
	//---------------------------------------------------------------------------------------------------
	// set, binding & location helper
	template<typename T, bool Assemble, spv::StorageClass Class>
	void LocationHelper(var_t<T, Assemble, Class>& _Var, const uint32_t _uLocation, const bool _bInput)
	{
		if constexpr(Assemble)
		{
			uint32_t uLocation = _uLocation != HUNDEFINED32 ? _uLocation : (_bInput ? GlobalAssembler.GetCurrentInputLocation() : GlobalAssembler.GetCurrentOutputLocation());
			HASSERT(uLocation != HUNDEFINED32, "Invalid location for variable %s", _Var.sName.c_str());
			_Var.SetLocation(uLocation);
		}
	}

	template<typename T, bool Assemble, spv::StorageClass Class>
	void BindingSetHelper(var_t<T, Assemble, Class>& _Var, const uint32_t _uBinding, const uint32_t _uSet)
	{
		if constexpr(Assemble)
		{
			uint32_t uSet = _uSet != HUNDEFINED32 ? _uSet : GlobalAssembler.GetDefaultSet();
			uint32_t uBinding = _uBinding != HUNDEFINED32 ? _uBinding : GlobalAssembler.GetCurrentBinding(uSet);
			HASSERT(uBinding != HUNDEFINED32 && uSet != HUNDEFINED32, "Invalid set and binding for variable %s", _Var.sName.c_str());
			_Var.SetBinding(uBinding, uSet);
		}
	}

	//---------------------------------------------------------------------------------------------------
	// input variable constructor
	template <typename T, bool Assemble = true, uint32_t Location = HUNDEFINED32, bool InstanceData = false>
	struct var_in_t : public var_t<T, Assemble, spv::StorageClassInput>
	{
		var_in_t() : var_t<T, Assemble, spv::StorageClassInput>() { LocationHelper(*this, Location, true); bInstanceData = InstanceData; }
		template <spv::StorageClass C1>
		const var_in_t& operator=(const var_t<T, Assemble, C1>& _Other) const { var_t<T, Assemble, spv::StorageClassInput>::operator=(_Other); return *this; }
	};
	//---------------------------------------------------------------------------------------------------
	// output variable constructor
	template <typename T, bool Assemble = true, uint32_t Location = HUNDEFINED32>
	struct var_out_t : public var_t<T, Assemble, spv::StorageClassOutput>
	{
		var_out_t() : var_t<T, Assemble, spv::StorageClassOutput>() { LocationHelper(*this, Location, false); }
		template <spv::StorageClass C1>
		const var_out_t& operator=(const var_t<T, Assemble, C1>& _Other) const { var_t<T, Assemble, spv::StorageClassOutput>::operator=(_Other);	return *this; }
	};
	//---------------------------------------------------------------------------------------------------
	// uniform variable constructor
	template <typename T, bool Assemble = true, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32>
	struct var_uniform_t : public var_t<T, Assemble, spv::StorageClassUniform>
	{
		var_uniform_t() : var_t<T, Assemble, spv::StorageClassUniform>() { BindingSetHelper(*this, Binding, Set); }
		template <spv::StorageClass C1>
		const var_uniform_t& operator=(const var_t<T, Assemble, C1>& _Other) const { var_t<T, Assemble, spv::StorageClassUniform>::operator=(_Other);	return *this; }
	};
	//---------------------------------------------------------------------------------------------------
	// uniform constant variable constructor
	template <typename T, bool Assemble = true, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32, uint32_t Location = HUNDEFINED32>
	struct var_uniform_constant_t : public var_t<T, Assemble, spv::StorageClassUniformConstant>
	{
		var_uniform_constant_t() : var_t<T, Assemble, spv::StorageClassUniformConstant>() { BindingSetHelper(*this, Binding, Set); LocationHelper(*this, Location, true); }
		template <spv::StorageClass C1>
		const var_uniform_constant_t& operator=(const var_t<T, Assemble, C1>& _Other) const { var_t<T, Assemble, spv::StorageClassUniformConstant>::operator=(_Other);	return *this; }
	};

	//---------------------------------------------------------------------------------------------------
	// Specialization constant constructor
	template <typename T, bool Assemble = true, uint32_t SpecId = HUNDEFINED32>
	struct var_spec_const_t : public var_t<T, Assemble, spv::StorageClassMax>
	{
		template <class ...Ts>
		var_spec_const_t(const Ts&... _args) : var_t<T, Assemble, spv::StorageClassMax>(TIntermediate(), _args...)
		{
			if constexpr(Assemble)
			{
				constexpr size_t uArgs = sizeof...(_args);
				static_assert(uArgs > 0, "Speialization constant needs default values");

				if constexpr(uArgs > 0)
				{
					SPIRVConstant Constant = SPIRVConstant::Make<true>(_args...);
					uResultId = GlobalAssembler.AddConstant(Constant);

					uSpecConstId = (SpecId != HUNDEFINED32) ? SpecId : GlobalAssembler.GetCurrentSpecConstId();
					HASSERT(uSpecConstId != HUNDEFINED32, "Unspecified specialization constant id");

					GlobalAssembler.AddOperation(SPIRVDecoration(spv::DecorationSpecId, uSpecConstId).MakeOperation(uResultId));
				}
			}
		}
		// todo: delete assignment/copy operators/constructors
	};

	//---------------------------------------------------------------------------------------------------
	// subpass constructor
	template <typename T, bool Assemble = true, bool Depth = false, uint32_t InputAttachmentIndex = HUNDEFINED32, class SubT = cond_t<Depth, tex_depth_subpass_t<T>, tex_color_subpass_t<T>>>
	struct var_subpass_t : public var_t<SubT, Assemble, spv::StorageClassUniformConstant>
	{
		var_subpass_t() : var_t<SubT, Assemble, spv::StorageClassUniformConstant>()
		{
			if constexpr(Assemble)
			{
				uInputAttachmentIndex = (InputAttachmentIndex != HUNDEFINED32) ? InputAttachmentIndex : GlobalAssembler.GetCurrentInputAttchmentIndex();
				HASSERT(uInputAttachmentIndex != HUNDEFINED32, "Invalid input attachment index for variable %s", sName.c_str());
				
				GlobalAssembler.AddOperation(SPIRVDecoration(spv::DecorationInputAttachmentIndex, uInputAttachmentIndex).MakeOperation(uVarId));
			}
		}
	};

	//---------------------------------------------------------------------------------------------------
	// push constant constructor
	template <typename T, bool Assemble = true>
	struct var_push_const_t : public var_t<T, Assemble, spv::StorageClassPushConstant>
	{
		var_push_const_t() : var_t<T, Assemble, spv::StorageClassPushConstant>() {}
	};

	//---------------------------------------------------------------------------------------------------
	// re-initialize struct member variable
	template <class T, spv::StorageClass Class>
	void InitVar(var_t<T, true, Class>& _Member, SPIRVType& _Type, std::vector<uint32_t> _AccessChain, const spv::StorageClass _kStorageClass, uint32_t& _uCurOffset, uint32_t& _uCurBoundary)
	{
		// override var id from previous init (should be generated on load with access chain)
		_Member.uVarId = HUNDEFINED32;
		// actual stuff happening here
		_Member.AccessChain = _AccessChain;
		_Member.kStorageClass = _kStorageClass;

		// translate bool members to int (taken from example)
		using VarT = std::conditional_t<std::is_same_v<T, bool>, int32_t, T>;

		_Member.Type = SPIRVType::FromType<VarT>();
		_Member.uTypeId = GlobalAssembler.AddType(_Member.Type);
		_Type.Member(_Member.Type); // struct type

		// member offset, check for 16byte allignment
		if (_uCurOffset + sizeof(VarT) <= _uCurBoundary)
		{
			_Member.uMemberOffset = _uCurOffset;
		}
		else
		{
			_Member.uMemberOffset = _uCurBoundary;
			_uCurBoundary += kAlignmentSize;
		}

		_uCurOffset += sizeof(VarT);
	}
	//---------------------------------------------------------------------------------------------------
	// recursively initialize all struct members
	template <size_t n, size_t N, class T>
	void InitStruct(
		T& _Struct,
		SPIRVType& _Type,
		std::vector<var_decoration<true>*>& _Members,
		std::vector<uint32_t> _AccessChain,
		const spv::StorageClass _kStorageClass,
		uint32_t& _uCurOffset,
		uint32_t& _uCurBoundary)
	{
		if constexpr(n < N && has_struct_tag<T>::value)
		{
			auto& member = hlx::get<n>(_Struct);
			using MemberType = std::remove_reference_t<std::remove_cv_t<decltype(member)>>;

			if constexpr(has_struct_tag<MemberType>::value)
			{
				member.uMemberIndex = static_cast<uint32_t>(n);
				_AccessChain.push_back(n);
				SPIRVType NestedType(spv::OpTypeStruct);
				InitStruct<0, hlx::aggregate_arity<decltype(member)>, MemberType>(member, NestedType, _AccessChain, _kStorageClass, _uCurOffset, _uCurBoundary);
				_Type.Member(NestedType);
			}
			else if constexpr(has_var_tag<MemberType>::value)
			{
				member.uMemberIndex = static_cast<uint32_t>(n);
				std::vector<uint32_t> FinalChain(_AccessChain);
				FinalChain.push_back(n);
				InitVar(member, _Type, FinalChain, _kStorageClass, _uCurOffset, _uCurBoundary);
				_Members.push_back(&member);
			}

			InitStruct<n + 1, N, T>(_Struct, _Type, _Members, _AccessChain, _kStorageClass, _uCurOffset, _uCurBoundary);
		}
	}

	//---------------------------------------------------------------------------------------------------
	// extract all components from any T that is of var_t<> type and pass the index to _Op as an argument
	// non var_t<> type arguments are converted to spirv constants and passed to _Op
	template <class T, class ...Ts>
	void ExtractCompnents(SPIRVOperation& _Op, const T& _First, const Ts& ..._Rest)
	{
		if constexpr(is_var<T>)
		{
			using VarT = decltype(_First.Value);
			constexpr size_t N = Dimmension<VarT>;
			uint32_t uTypeId = GlobalAssembler.AddType(SPIRVType::FromType<base_type_t<VarT>>());
			_First.Load();

			// extract all components of variable
			for (uint32_t n = 0u; n < N; ++n)
			{
				SPIRVOperation OpExtract(spv::OpCompositeExtract, uTypeId, SPIRVOperand(kOperandType_Intermediate, _First.uResultId)); // var id to extract from
				OpExtract.AddLiterals(_First.AccessChain); // can be empty
				OpExtract.AddLiteral(n); // extraction index

				uint32_t uId = GlobalAssembler.AddOperation(OpExtract);
				_Op.AddIntermediate(uId);
			}
		}
		else
		{
			// create component constant
			SPIRVConstant Constant = SPIRVConstant::Make<false>(_First);
			const uint32_t uConstId = GlobalAssembler.AddConstant(Constant);
			_Op.AddIntermediate(uConstId);
		}

		constexpr size_t uArgs = sizeof...(_Rest);
		if constexpr(uArgs > 0)
		{
			ExtractCompnents(_Op, _Rest...);
		}
	}

	//---------------------------------------------------------------------------------------------------
	// get value of var_t<> based on type
	template<class T>
	auto get_arg_value(const T& var)
	{
		if constexpr(is_var<T>)
		{
			return var.Value;
		}
		else
		{
			return var;
		}
	}

	template <class T, class ...Ts>
	const T& get_first_arg(const T& _first, const Ts& ..._args) { return _first; }

	//---------------------------------------------------------------------------------------------------
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class ...Ts>
	inline void var_t<T, Assemble, Class>::InitVar(const Ts & ..._args)
	{
		constexpr size_t uArgs = sizeof...(_args);
		if constexpr(Assemble)
		{
			std::vector<var_decoration<true>*> Members;
			if constexpr(has_struct_tag<T>::value)
			{
				static_assert(uArgs == 0, "spv struct can't be value initialized");
				Type = SPIRVType::Struct();

				uint32_t uMemberOffset = 0u;
				uint32_t uAlignmentBoundary = kAlignmentSize;
				InitStruct<0, hlx::aggregate_arity<T>, T>(Value, Type, Members, {}, kStorageClass, uMemberOffset, uAlignmentBoundary);

				uTypeId = GlobalAssembler.AddType(Type);
				GlobalAssembler.AddOperation(SPIRVDecoration(spv::DecorationBlock).MakeOperation(uTypeId));
			}
			else
			{
				Type = SPIRVType::FromType<T>();
				uTypeId = GlobalAssembler.AddType(Type);
			}

			// pointer type
			const uint32_t uPtrTypeId = GlobalAssembler.AddType(SPIRVType::Pointer(Type, kStorageClass));

			// OpVariable:
			// Allocate an object in memory, resulting in a pointer to it, which can be used with OpLoad and OpStore.
			// Result Type must be an OpTypePointer. Its Type operand is the type of object in memory.
			// Storage Class is the Storage Class of the memory holding the object. It cannot be Generic.
			// Initializer is optional. If Initializer is present, it will be the initial value of the variable’s memory content.
			// Initializer must be an <id> from a constant instruction or a global(module scope) OpVariable instruction.
			// Initializer must havethe same type as the type pointed to by Result Type.

			SPIRVOperation OpCreateVar;

			// argument list has var_t<> initializers
			constexpr bool bHasVar = has_var<Ts...>;
			if constexpr(bHasVar)
			{
				OpCreateVar = SPIRVOperation(spv::OpCompositeConstruct, uTypeId); // uPtrTypeId
				ExtractCompnents(OpCreateVar, _args...);

				// composite constructs treated as intermediates as they cant be loaded
				uResultId = GlobalAssembler.AddOperation(OpCreateVar);
			}
			else
			{
				OpCreateVar = SPIRVOperation(spv::OpVariable, uPtrTypeId, // result type
					SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(kStorageClass))); // variable storage location	

				if constexpr(uArgs > 0u)
				{
					SPIRVConstant Constant = SPIRVConstant::Make<false>(_args...);
					const uint32_t uConstId = GlobalAssembler.AddConstant(Constant);
					OpCreateVar.AddIntermediate(uConstId);
				}

				uVarId = GlobalAssembler.AddOperation(OpCreateVar, &pVarOp);
			}

			// correct sturct member variables
			for (var_decoration<true>* pMember : Members)
			{
				pMember->uBaseId = uVarId;
				pMember->uBaseTypeId = uTypeId;

				// fix storage class in OpVar
				{
					HASSERT(pVarOp != nullptr && pVarOp->GetOpCode() == spv::OpVariable, "Invalid variable op");
					auto& Operands = pMember->pVarOp->GetOperands();
					HASSERT(Operands.size() > 0u, "Invalid number of variable operands");
					Operands.front().uId = (uint32_t)kStorageClass;
				}

				// Create member offset decoration
				SPIRVDecoration MemberDecl(spv::DecorationOffset, pMember->uMemberOffset, kDecorationType_Member, pMember->AccessChain.back());
				GlobalAssembler.AddOperation(MemberDecl.MakeOperation(uTypeId));
			}
		}
	}

	//---------------------------------------------------------------------------------------------------
	// the all mighty variable default constructor
	template<typename T, bool Assemble, spv::StorageClass C1>
	template<class ...Ts>
	inline var_t<T, Assemble, C1>::var_t(const Ts& ..._args) :
		var_decoration<Assemble>(C1),
		Value(get_arg_value(_args)...)
	{
		InitVar(_args...);
	}

	//---------------------------------------------------------------------------------------------------
	// Intermediate variable constructor
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class ...Ts>
	inline var_t<T, Assemble, Class>::var_t(TIntermediate, const Ts& ..._args) :
		var_decoration<Assemble>(Class),
		Value(_args...)
	{
		if constexpr(Assemble)
		{
			Type = SPIRVType::FromType<T>();
			uTypeId = GlobalAssembler.AddType(Type);
		}
	}

#pragma endregion

	//---------------------------------------------------------------------------------------------------
	// OPERATIONS
	//---------------------------------------------------------------------------------------------------
#pragma region Operations

	//---------------------------------------------------------------------------------------------------
	// mutable add
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator+=(const var_t<T, Assemble, C1>& _Other) const
	{
		return make_op2(_Other, [](T& v1, const T& v2) { v1 += v2; }, spv::OpFAdd, spv::OpIAdd);
	}

	//---------------------------------------------------------------------------------------------------
	// mutable sub
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator-=(const var_t<T, Assemble, C1>& _Other) const
	{
		return make_op2(_Other, [](T& v1, const T& v2) { v1 -= v2; }, spv::OpFSub, spv::OpISub);
	}

	//---------------------------------------------------------------------------------------------------
	// mutable mul
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class U, spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator*=(const var_t<U, Assemble, C1>& _Other) const
	{
		// square matrix mul
		if constexpr(is_square_matrix<T> && std::is_same_v<T, U>)
			return make_op2(_Other, [](T& v1, const U& v2) { v1 *= v2; }, spv::OpMatrixTimesMatrix);
		if constexpr(is_vector<T> && is_scalar<U>)
			return make_op2(_Other, [](T& v1, const U& v2) { v1 *= v2; }, spv::OpVectorTimesScalar);
		else
			return make_op2(_Other, [](T& v1, const U& v2) { v1 *= v2; }, spv::OpFMul, spv::OpIMul);
	}


	//---------------------------------------------------------------------------------------------------
	// mutable div
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class U, spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator/=(const var_t<U, Assemble, C1>& _Other) const
	{
		static_assert(std::is_same_v<T, U>, "Unsupported result type");
		return make_op2(_Other, [](T& v1, const U& v2) { v1 /= v2; }, spv::OpFDiv, spv::OpSDiv, spv::OpUDiv);
	}

	//---------------------------------------------------------------------------------------------------
	// negation
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> var_t<T, Assemble, Class>::operator!() const
	{
		return make_op1_immutable([](T& _Value) -> T { return !_Value; }, spv::OpFNegate, spv::OpSNegate, spv::OpNop, spv::OpLogicalNot);
	}

	// increment mutable
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator++() const
	{
		static_assert(hlx::is_of_type<T, float, double, int32_t, uint32_t>(), "Incompatible variable type");
		return make_op2(var_t<T, Assemble, spv::StorageClassFunction>((T)1), [](T& v1, const T& v2) { v1 += v2; }, spv::OpFAdd, spv::OpIAdd);
	}

	// increment immutable
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> var_t<T, Assemble, Class>::operator++(int) const
	{
		var_t<T, Assemble, spv::StorageClassFunction> PreEval(*this);
		++(*this); // call mutable increment
		return PreEval;
	}

	// decrement mutable
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator--() const
	{
		static_assert(hlx::is_of_type<T, float, double, int32_t, uint32_t>(), "Incompatible variable type");
		return make_op2(var_t<T, Assemble, spv::StorageClassFunction>((T)1), [](T& v1, const T& v2) { v1 -= v2; }, spv::OpFSub, spv::OpISub);
	}
	//decrement immutable
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> var_t<T, Assemble, Class>::operator--(int) const
	{
		var_t<T, Assemble, spv::StorageClassFunction> PreEval(*this);
		--(*this); // call mutable decrement
		return PreEval;
	}
	//---------------------------------------------------------------------------------------------------
#pragma endregion

} // !Tracy

#endif // !TRACY_SPIRVVARIABLE_H
