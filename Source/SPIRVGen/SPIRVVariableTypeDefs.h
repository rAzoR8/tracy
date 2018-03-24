#ifndef TRACY_SPIRVVARIABLETYPEDEFS_H
#define TRACY_SPIRVVARIABLETYPEDEFS_H

//#include <cstdint>
//
////forward decl
//namespace spv
//{
//	enum StorageClass;
//}
//
//namespace Tracy
//{
//	template <class T, bool Assemble, spv::StorageClass Class>
//	struct var_t;
//} // Tracy

#define S32 Tracy::var_t<int32_t, Assemble, spv::StorageClassFunction>
#define S64 Tracy::var_t<int64_t, Assemble, spv::StorageClassFunction>
#define Int2 Tracy::var_t<int2_t, Assemble, spv::StorageClassFunction>
#define Int3 Tracy::var_t<int3_t, Assemble, spv::StorageClassFunction>
#define Int4 Tracy::var_t<int4_t, Assemble, spv::StorageClassFunction>

#define U32 Tracy::var_t<uint32_t, Assemble, spv::StorageClassFunction>
#define U64 Tracy::var_t<uint64_t, Assemble, spv::StorageClassFunction>
#define UInt2 Tracy::var_t<uint2_t, Assemble, spv::StorageClassFunction>
#define UInt3 Tracy::var_t<uint3_t, Assemble, spv::StorageClassFunction>
#define UInt4 Tracy::var_t<uint4_t, Assemble, spv::StorageClassFunction>

#define F32 Tracy::var_t<float, Assemble, spv::StorageClassFunction>
#define F64 Tracy::var_t<double, Assemble, spv::StorageClassFunction>
#define Float2 Tracy::var_t<float2_t, Assemble, spv::StorageClassFunction>
#define Float3 Tracy::var_t<float3_t, Assemble, spv::StorageClassFunction>
#define Float4 Tracy::var_t<float4_t, Assemble, spv::StorageClassFunction>

#define Quaternion = SPIRVQuaternion<Assemble, spv::StorageClassFunction>;
#define Complex = SPIRVComplex<Assemble, spv::StorageClassFunction>;
#define Boolean Tracy::var_t<bool, Assemble, spv::StorageClassFunction>

#define Float2x2 Tracy::var_t<float2x2_t, Assemble, spv::StorageClassFunction>
#define Float3x3 Tracy::var_t<float3x3_t, Assemble, spv::StorageClassFunction>
#define Float3x4 Tracy::var_t<float3x4_t, Assemble, spv::StorageClassFunction>
#define Float4x3 Tracy::var_t<float4x3_t, Assemble, spv::StorageClassFunction>
#define Float4x4 Tracy::var_t<float4x4_t, Assemble, spv::StorageClassFunction>
#define Matrix Tracy::var_t<float4x4_t, Assemble, spv::StorageClassFunction>

//#define SamplerState Tracy::var_t<sampler_t, Assemble, spv::StorageClassUniformConstant>
//
//#define Texture1D Tracy::var_t<tex1d_t<float4_t>, spv::StorageClassUniformConstant>
//#define Texture2D Tracy::var_t<tex2d_t<float4_t>, spv::StorageClassUniformConstant>
//#define Texture3D Tracy::var_t<tex3d_t<float4_t>, spv::StorageClassUniformConstant>
//#define TextureCube Tracy::var_t<tex_cube_t<float4_t>, spv::StorageClassUniformConstant>

#endif // !TRACY_SPIRVVARIABLETYPEDEFS_H
