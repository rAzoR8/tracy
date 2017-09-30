#ifndef TRACY_GLM_H
#define TRACY_GLM_H

//http://glm.g-truc.net/0.9.8/glm-0.9.8.pdf
#include <glm\fwd.hpp> // forward decls
// put this into Source file: #include <glm/glm.hpp> 

//#include <glm\vec2.hpp>
//#include <glm\vec3.hpp>
//#include <glm\vec4.hpp>

namespace Tracy
{
	using float2 = glm::vec2;
	using float3 = glm::vec3;
	using float4 = glm::vec4;

	using int2 = glm::i32vec2;
	using int3 = glm::i32vec3;
	using int4 = glm::i32vec4;
	
	using uint2 = glm::u32vec2;
	using uint3 = glm::u32vec3;
	using uint4 = glm::u32vec4;

	using float2x2 = glm::mat2x2;
	using float3x3 = glm::mat3x3;
	using float3x4 = glm::mat3x4; // transpose ?
	using float4x3 = glm::mat4x3; // transpose ?
	using float4x4 = glm::mat4x4;
	using matrix = glm::mat4x4;

	template <class ...Ts>
	struct va_type {};

	template <>
	struct va_type<float> { typedef float type; };
	template <>
	struct va_type<float, float> { typedef float2 type; };
	template <>
	struct va_type<float, float, float> { typedef float3 type; };
	template <>
	struct va_type<float, float, float, float> { typedef float4 type; };

	template <>
	struct va_type<int32_t> { typedef int32_t type; };
	template <>
	struct va_type<int32_t, int32_t> { typedef int2 type; };
	template <>
	struct va_type<int32_t, int32_t, int32_t> { typedef int3 type; };
	template <>
	struct va_type<int32_t, int32_t, int32_t, int32_t> { typedef int4 type; };

	template <>
	struct va_type<uint32_t> { typedef uint32_t type; };
	template <>
	struct va_type<uint32_t, uint32_t> { typedef uint2 type; };
	template <>
	struct va_type<uint32_t, uint32_t, uint32_t> { typedef uint3 type; };
	template <>
	struct va_type<uint32_t, uint32_t, uint32_t, uint32_t> { typedef uint4 type; };
	
	template <class ...Ts>
	using va_type_t = typename va_type<typename std::decay_t<Ts>...>::type;
}; // Tracy

#endif // !TRACY_GLM_H
