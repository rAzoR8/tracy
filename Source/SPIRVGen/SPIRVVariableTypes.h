#ifndef TRACY_SPIRVVARIABLETYPES_H
#define TRACY_SPIRVVARIABLETYPES_H

//http://glm.g-truc.net/0.9.8/glm-0.9.8.pdf
#include <glm\fwd.hpp> // forward decls
// put this into Source file: #include <glm/glm.hpp> 
#include <vulkan\spirv.hpp>
#include "FunctionalUtils.h"

namespace Tracy
{
	template <bool Cond, class U, class V>
	using cond_t = std::conditional_t<Cond, U, V>;

	using float2_t = glm::vec2;
	using float3_t = glm::vec3;
	using float4_t = glm::vec4;

	using int2_t = glm::i32vec2;
	using int3_t = glm::i32vec3;
	using int4_t = glm::i32vec4;
	
	using uint2_t = glm::u32vec2;
	using uint3_t = glm::u32vec3;
	using uint4_t = glm::u32vec4;

	using float2x2_t = glm::mat2x2;
	using float3x3_t = glm::mat3x3;
	using float3x4_t = glm::mat3x4; // transposed wrt to open gl
	using float4x3_t = glm::mat4x3; // transposed wrt to open gl
	using float4x4_t = glm::mat4x4;
	using matrix_t = glm::mat4x4;

#pragma region col_type
	template <class MatrixT>
	struct col_type { typedef std::false_type type; };

	template<>
	struct col_type<float2x2_t> { typedef float2_t type; };

	template<>
	struct col_type<float3x3_t> { typedef float3_t type; };

	template<>
	struct col_type<float3x4_t> { typedef float4_t type; };

	template<>
	struct col_type<float4x3_t> { typedef float3_t type; };

	template<>
	struct col_type<float4x4_t> { typedef float4_t type; };

	template <class T>
	using col_type_t = typename col_type<T>::type;
#pragma endregion

#pragma region row_type
	template <class MatrixT>
	struct row_type { typedef std::false_type type; };

	template<>
	struct row_type<float2x2_t> { typedef float2_t type; };

	template<>
	struct row_type<float3x3_t> { typedef float3_t type; };

	template<>
	struct row_type<float3x4_t> { typedef float3_t type; };

	template<>
	struct row_type<float4x3_t> { typedef float4_t type; };

	template<>
	struct row_type<float4x4_t> { typedef float4_t type; };

	template <class T>
	using row_type_t = typename row_type<T>::type;
#pragma endregion

#pragma region mat_type
	template <class Row, class Col>
	struct mat_type { typedef std::false_type type; };

	template <>
	struct mat_type<float2_t, float2_t> { typedef float2x2_t type; };

	template <>
	struct mat_type<float3_t, float3_t> { typedef float3x3_t type; };

	template <>
	struct mat_type<float4_t, float3_t> { typedef float4x3_t type; };

	template <>
	struct mat_type<float3_t, float4_t> { typedef float3x4_t type; };

	template <>
	struct mat_type<float4_t, float4_t> { typedef float4x4_t type; };

	template <class Row, class Col>
	using mat_type_t = typename mat_type<Row, Col>::type;
#pragma endregion

#pragma region va_type
	// create type from typelist
	template <class ...Ts>
	struct va_type { typedef std::false_type type; };

	template <>
	struct va_type<bool> { typedef bool type; };

	template <>
	struct va_type<float> { typedef float type; };
	template <>
	struct va_type<float, float> { typedef float2_t type; };
	template <>
	struct va_type<float, float, float> { typedef float3_t type; };
	template <>
	struct va_type<float, float, float, float> { typedef float4_t type; };
	template <>
	struct va_type<double> { typedef double type; };

	template <>
	struct va_type<int32_t> { typedef int32_t type; };
	template <>
	struct va_type<int32_t, int32_t> { typedef int2_t type; };
	template <>
	struct va_type<int32_t, int32_t, int32_t> { typedef int3_t type; };
	template <>
	struct va_type<int32_t, int32_t, int32_t, int32_t> { typedef int4_t type; };
	template <>
	struct va_type<int64_t> { typedef int64_t type; };

	template <>
	struct va_type<uint32_t> { typedef uint32_t type; };
	template <>
	struct va_type<uint32_t, uint32_t> { typedef uint2_t type; };
	template <>
	struct va_type<uint32_t, uint32_t, uint32_t> { typedef uint3_t type; };
	template <>
	struct va_type<uint32_t, uint32_t, uint32_t, uint32_t> { typedef uint4_t type; };
	template <>
	struct va_type<uint64_t> { typedef uint64_t type; };

	template <class ...Ts>
	using va_type_t = typename va_type<typename std::decay_t<Ts>...>::type;
#pragma endregion

#pragma region vec_type
	// create vector type from base type and dimension
	template <class T, size_t Dim>
	struct vec_type { typedef std::false_type type; }; // could also use glm::vec<Dim, T, highpr> but then dim == 1 is not a base type

	template<>
	struct vec_type<float, 1> { typedef float type; };

	template<>
	struct vec_type<float, 2> { typedef float2_t type; };

	template<>
	struct vec_type<float, 3> { typedef float3_t type; };

	template<>
	struct vec_type<float, 4> { typedef float4_t type; };

	template<>
	struct vec_type<int32_t, 1> { typedef int32_t type; };

	template<>
	struct vec_type<int32_t, 2> { typedef int2_t type; };

	template<>
	struct vec_type<int32_t, 3> { typedef int3_t type; };

	template<>
	struct vec_type<int32_t, 4> { typedef int4_t type; };

	template<>
	struct vec_type<uint32_t, 1> { typedef uint32_t type; };

	template<>
	struct vec_type<uint32_t, 2> { typedef uint2_t type; };

	template<>
	struct vec_type<uint32_t, 3> { typedef uint3_t type; };

	template<>
	struct vec_type<uint32_t, 4> { typedef uint4_t type; };

	template <class T, size_t Dim>
	using vec_type_t = typename vec_type<T, Dim>::type;
#pragma endregion

#pragma region base_type
	template <class VecT>
	struct base_type { typedef std::false_type type; };

	template <>
	struct base_type<bool> { typedef bool type; };

	template <>
	struct base_type<float> { typedef float type; };

	template <>
	struct base_type<double> { typedef double type; };

	template <>
	struct base_type<float2_t> { typedef float type; };

	template <>
	struct base_type<float3_t> { typedef float type; };

	template <>
	struct base_type<float4_t> { typedef float type; };

	template <>
	struct base_type<int32_t> { typedef int32_t type; };

	template <>
	struct base_type<int64_t> { typedef int64_t type; };

	template <>
	struct base_type<int2_t> { typedef int32_t type; };

	template <>
	struct base_type<int3_t> { typedef int32_t type; };

	template <>
	struct base_type<int4_t> { typedef int32_t type; };

	template <>
	struct base_type<uint32_t> { typedef uint32_t type; };

	template <>
	struct base_type<uint64_t> { typedef uint64_t type; };

	template <>
	struct base_type<uint2_t> { typedef uint32_t type; };

	template <>
	struct base_type<uint3_t> { typedef uint32_t type; };

	template <>
	struct base_type<uint4_t> { typedef uint32_t type; };

	template <>
	struct base_type<float2x2_t> { typedef float type; };

	template <>
	struct base_type<float3x3_t> { typedef float type; };

	template <>
	struct base_type<float3x4_t> { typedef float type; };

	template <>
	struct base_type<float4x3_t> { typedef float type; };

	template <>
	struct base_type<float4x4_t> { typedef float type; };
	
	template <class VecT>
	using base_type_t = typename base_type<VecT>::type;
#pragma endregion

	template <class T>
	constexpr size_t Dimmension = sizeof(T) / sizeof(base_type_t<T>);

	template <class T>
	constexpr bool is_scalar = std::is_same_v<T, base_type_t<T>>;

	template <class T>
	constexpr bool is_vector =
		hlx::is_of_type<T,
		int2_t, int3_t, int4_t,
		uint2_t, uint3_t, uint4_t,
		float2_t, float3_t, float4_t>();

	template <class T>
	constexpr bool is_matrix = hlx::is_of_type<T, float2x2_t, float3x3_t, float3x4_t, float4x3_t, float4x4_t>();

	template <class T>
	constexpr bool is_square_matrix = hlx::is_of_type<T, float2x2_t, float3x3_t, float4x4_t>();

#pragma region texture_types

	enum ETexDepthType : uint32_t
	{
		kTexDepthType_NonDepth = 0,
		kTexDepthType_Depth,
		kTexDepthType_Unspecified
	};

	// Sampled	indicates whether or not this image will be accessed in combination with a sampler, and must be one of the following values :
	//	0 indicates this is only known at run time, not at compile time
	//	1 indicates will be used with sampler
	//	2 indicates will be used without a sampler (a storage image)
	enum ETexSamplerAccess : uint32_t
	{
		kTexSamplerAccess_Runtime = 0, 
		kTexSamplerAccess_Sampled = 1,
		kTexSamplerAccess_Storage = 2
	};

	constexpr uint32_t SPVDimToRealDim(const spv::Dim _Dim)
	{
		if (_Dim <= spv::Dim3D)
			return _Dim + 1u;

		if (_Dim == spv::DimSubpassData)
			return 2u;

		return 0u;
	}

	// Image Format can be Unknown, depending on the client API
	// we omit the format, since it should be coming from the api anyway
	template <
		class T,
		spv::Dim _Dim,
		bool _Array = false,
		ETexDepthType _DType = kTexDepthType_NonDepth,
		bool _MultiSampled = false,
		ETexSamplerAccess _SAccess = kTexSamplerAccess_Sampled>
	struct tex_t
	{
		typedef T TexComponentType; // result type of sample
		typedef vec_type_t<float, SPVDimToRealDim(_Dim) + _Array> TexCoordType; // UV coord vector type
		static constexpr spv::Dim Dim = _Dim; // 1 2 3
		static constexpr bool Array = _Array; // is array
		static constexpr ETexDepthType DepthType = _DType;
		static constexpr bool MultiSampled = _MultiSampled;
		static constexpr ETexSamplerAccess SamplerAccess = _SAccess;
	};

	template<class, class = std::void_t<> >
	struct is_texture_impl : std::false_type { };

	template<class T>
	struct is_texture_impl<T, std::void_t<typename T::TexComponentType>> : std::true_type { };

	template <class T>
	constexpr bool is_texture = is_texture_impl<T>::value;

	template <class T = float4_t>
	using tex1d_t = tex_t<T, spv::Dim1D>;

	template <class T = float4_t>
	using tex2d_t = tex_t<T, spv::Dim2D>;

	template <class T = float4_t>
	using tex3d_t = tex_t<T, spv::Dim3D>;

	template <class T = float4_t>
	using tex_cube_t = tex_t<T, spv::DimCube>;

	template <class T = float4_t>
	using tex_color_subpass_t = tex_t<T, spv::DimSubpassData, false, kTexDepthType_NonDepth>;

	template <class T = float4_t>
	using tex_depth_subpass_t = tex_t<T, spv::DimSubpassData, false, kTexDepthType_Depth>;

	template <class T = float4_t>
	using tex_color_storage_t = tex_t<T, spv::Dim2D, false, kTexDepthType_NonDepth, false, kTexSamplerAccess_Storage>;

	template <class T = float>
	using tex_depth_storage_t = tex_t<T, spv::Dim2D, false, kTexDepthType_Depth, false, kTexSamplerAccess_Storage>;

	// TODO: array types

	template <class TexT> // TexT = tex_t variant
	using tex_component_t = typename TexT::TexComponentType;

	template <class TexT> // TexT = tex_t variant
	using tex_coord_t = typename TexT::TexCoordType;

#pragma endregion

	struct sampler_t {};

	template <class T>
	constexpr bool is_sampler = std::is_same_v<std::decay_t<T>, sampler_t>;

	template<class T, uint32_t Index>
	constexpr bool is_valid_index()
	{
		if constexpr(is_vector<T> || is_matrix<T>)
		{
			return Index < Dimmension<T>;
		}
		else
		{
			return false;
		}
	}

	template <class T>
	constexpr bool is_valid_type = !std::is_same_v<std::false_type, T>;

	template <class T>
	constexpr bool is_base_integral_type = hlx::is_of_type<T, int32_t, uint32_t, float>();

	template <class U, class V>
	constexpr bool is_convertible = is_base_integral_type<U> && is_base_integral_type<V>;

	template <class U, class V>
	using longer_type_t = cond_t<Dimmension<U> >= Dimmension<V>, U, V>;

#pragma region mul result tpye
	// result type of a multiplication
	template <class M/*, class V*/> // M times V
	using matxvec_t = col_type_t<M>;

	template <class M/*, class V*/> // M times V
	using vecxmat_t = row_type_t<M>;

	template <class M, class N> // M times N
	using matxmat_t = mat_type_t<row_type_t<N>, col_type_t<M>>;

	template <class L, class R, class ElseT> // L * R
	using cond_mm_t = cond_t<is_matrix<L> && is_matrix<R>, matxmat_t<L, R>, ElseT>;

	template <class L, class R, class ElseT> // L * R
	using cond_mv_t = cond_t<is_matrix<L> && is_vector<R>, matxvec_t<L>, ElseT>;

	template <class L, class R, class ElseT> // L * R
	using conc_vm_t = cond_t<is_vector<L> && is_matrix<R>, vecxmat_t<R>, ElseT>;

	template <class L, class R> // L * R
	using mul_result_t = cond_mm_t<L, R, cond_mv_t<L, R, conc_vm_t<L, R, longer_type_t<L, R>>>>;
#pragma endregion

}; // Tracy

#endif // !TRACY_SPIRVVARIABLETYPES_H
