#ifndef TRACY_GLM_H
#define TRACY_GLM_H

//http://glm.g-truc.net/0.9.8/glm-0.9.8.pdf
#include <glm\fwd.hpp> // forward decls
// put this into Source file: #include <glm/glm.hpp> 

#include "FunctionalUtils.h"

namespace Tracy
{
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
	using float3x4_t = glm::mat3x4; // transpose ?
	using float4x3_t = glm::mat4x3; // transpose ?
	using float4x4_t = glm::mat4x4;
	using matrix_t = glm::mat4x4;

#pragma region col_type
	template <class MatrixT>
	struct col_type {};

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
	struct row_type {};

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
	struct mat_type {};

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
	template <class ...Ts>
	struct va_type {};

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

#pragma region base_type
	template <class VecT>
	struct base_type {};

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
	constexpr bool is_vector =
		hlx::is_of_type<T,
		int2_t, int3_t, int4_t,
		uint2_t, uint3_t, uint4_t,
		float2_t, float3_t, float4_t>();

	template <class T>
	constexpr bool is_matrix = hlx::is_of_type<T, float2x2_t, float3x3_t, float3x4_t, float4x3_t, float4x4_t>();

}; // Tracy

#endif // !TRACY_GLM_H
