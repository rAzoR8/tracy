#ifndef TRACY_DISPLAYTYPES_H
#define TRACY_DISPLAYTYPES_H

#include "StandardDefines.h"

namespace Tracy
{
	enum EShaderType : uint8_t
	{
		kShaderType_Vertex = 0,
		kShaderType_TessellationControl = 1,
		kShaderType_TessellationEvaluation = 2,
		kShaderType_Geometry = 3,
		kShaderType_Fragment = 4,
		kShaderType_GLCompute = 5,
		kShaderType_Kernel = 6,

		kShaderType_NumOf,
		kShaderType_Unknown = kShaderType_NumOf
	};

	struct ShaderID
	{
		ShaderID(const uint64_t _uID = 0u) : uID(_uID) {}
		ShaderID(const EShaderType _kType, const uint8_t _uCompileFlags, const uint16_t _uShader, const uint32_t _uVariant) :
			kType(_kType), uCompileFlags(_uCompileFlags), uShader(_uShader), uVariant(_uVariant) {}
		ShaderID(const ShaderID& _Other) : uID(_Other.uID) {}

		static constexpr uint64_t kInvalid = kShaderType_Unknown;

		const bool Valid() const { return kType < kShaderType_NumOf; }

		union
		{
			struct
			{
				EShaderType kType; // 8
				uint8_t uCompileFlags; // debug, optimization etc
				uint16_t uShader; // which shader
				uint32_t uVariant; // which permutation of the shader
			};
			uint64_t uID;
		};

		operator uint64_t() const { return uID; }
	};

	// https://msdn.microsoft.com/en-us/library/windows/desktop/dn770385(v=vs.85).aspx
	//typedef enum D3D12_PRIMITIVE_TOPOLOGY_TYPE {
	//	D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED = 0,
	//	D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT = 1,
	//	D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE = 2,
	//	D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE = 3,
	//	D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH = 4
	//}

	// https://vulkan.lunarg.com/doc/view/1.0.33.0/linux/vkspec.chunked/ch19s01.html
	//typedef enum VkPrimitiveTopology {
	//	VK_PRIMITIVE_TOPOLOGY_POINT_LIST = 0,
	//	VK_PRIMITIVE_TOPOLOGY_LINE_LIST = 1,
	//	VK_PRIMITIVE_TOPOLOGY_LINE_STRIP = 2,
	//	VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = 3,
	//	VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP = 4,
	//	VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN = 5,
	//	VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY = 6,
	//	VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY = 7,
	//	VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY = 8,
	//	VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY = 9,
	//	VK_PRIMITIVE_TOPOLOGY_PATCH_LIST = 10,
	//}

	enum EPrimitiveTopology : uint32_t
	{
		kPrimitiveTopology_PointList = 0,
		kPrimitiveTopology_LineList = 1,
		kPrimitiveTopology_LineStrip = 2,
		kPrimitiveTopology_TriangleList = 3,
		kPrimitiveTopology_TriangleStrip = 4,
		kPrimitiveTopology_TriangleFan = 5,
		kPrimitiveTopology_NumOf,
		kPrimitiveTopology_Unknown = kPrimitiveTopology_NumOf
	};

	//---------------------------------------------------------------------------------------------------

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dn770366(v=vs.85).aspx
	//typedef enum D3D12_FILL_MODE {
	//	D3D12_FILL_MODE_WIREFRAME = 2,
	//	D3D12_FILL_MODE_SOLID = 3
	//}

	//typedef enum VkPolygonMode {
	//	VK_POLYGON_MODE_FILL = 0,
	//	VK_POLYGON_MODE_LINE = 1,
	//	VK_POLYGON_MODE_POINT = 2,
	//}

	// we use to common subset:
	enum EPolygonFillMode : uint32_t
	{
		kPolygonFillMode_Solid = 0, // fill
		kPolygonFillMode_Line = 1, // wireframe

		kPolygonFillMode_NumOf,
		kPolygonFillMode_Unknown = kPolygonFillMode_NumOf
	};

	//---------------------------------------------------------------------------------------------------

	//https://msdn.microsoft.com/en-us/library/windows/desktop/dn770354(v=vs.85).aspx
	//typedef enum D3D12_CULL_MODE {
	//	D3D12_CULL_MODE_NONE = 1,
	//	D3D12_CULL_MODE_FRONT = 2,
	//	D3D12_CULL_MODE_BACK = 3
	//}

	// https://www.khronos.org/registry/vulkan/specs/1.0-wsi_extensions/html/vkspec.html#VkCullModeFlagBits
	//typedef enum VkCullModeFlagBits {
	//	VK_CULL_MODE_NONE = 0,
	//	VK_CULL_MODE_FRONT_BIT = 0x00000001,
	//	VK_CULL_MODE_BACK_BIT = 0x00000002,
	//	VK_CULL_MODE_FRONT_AND_BACK = 0x00000003,
	//}

	enum ECullMode : uint32_t
	{
		kCullMode_None = 0,
		kCullMode_Front = 1,
		kCullMode_Back = 2,

		kCullMode_NumOf,
		kCullMode_Unknown = kCullMode_NumOf
	};

	//---------------------------------------------------------------------------------------------------
	//https://www.khronos.org/registry/vulkan/specs/1.0-wsi_extensions/html/vkspec.html#VkFrontFace
	//typedef enum VkFrontFace {
	//	VK_FRONT_FACE_COUNTER_CLOCKWISE = 0,
	//	VK_FRONT_FACE_CLOCKWISE = 1,
	//}

	// DX12: BOOL FrontCounterClockwise

	enum EFrontFace : uint32_t
	{
		kFrontFace_CounterClockwise = 0,
		kFrontFace_Clockwise = 1,

		kFrontFace_NumOf,
		kFrontFace_Unknown = kFrontFace_NumOf
	};

	//---------------------------------------------------------------------------------------------------
	// DX12 RASTERIZER DESC: https://msdn.microsoft.com/en-us/library/windows/desktop/dn770387(v=vs.85).aspx
	//typedef struct D3D12_RASTERIZER_DESC {
	//	D3D12_FILL_MODE                       FillMode;
	//	D3D12_CULL_MODE                       CullMode;
	//	BOOL                                  FrontCounterClockwise;
	//	INT                                   DepthBias;
	//	FLOAT                                 DepthBiasClamp;
	//	FLOAT                                 SlopeScaledDepthBias;
	//	BOOL                                  DepthClipEnable;
	//	BOOL                                  MultisampleEnable;
	//	BOOL                                  AntialiasedLineEnable;
	//	UINT                                  ForcedSampleCount;
	//	D3D12_CONSERVATIVE_RASTERIZATION_MODE ConservativeRaster;
	//}

	//---------------------------------------------------------------------------------------------------
	// VK	RASTERIZER DESC: https://www.khronos.org/registry/vulkan/specs/1.0-wsi_extensions/html/vkspec.html#VkPipelineRasterizationStateCreateInfo
	//typedef struct VkPipelineRasterizationStateCreateInfo {
	//	VkStructureType                            sType;
	//	const void*                                pNext;
	//	VkPipelineRasterizationStateCreateFlags    flags;
	//	VkBool32                                   depthClampEnable;
	//	VkBool32                                   rasterizerDiscardEnable;
	//	VkPolygonMode                              polygonMode;
	//	VkCullModeFlags                            cullMode;
	//	VkFrontFace                                frontFace;
	//	VkBool32                                   depthBiasEnable;
	//	float                                      depthBiasConstantFactor;
	//	float                                      depthBiasClamp;
	//	float                                      depthBiasSlopeFactor;
	//	float                                      lineWidth;
	//}

	//---------------------------------------------------------------------------------------------------

	//typedef enum D3D12_COMPARISON_FUNC {
	//	D3D12_COMPARISON_FUNC_NEVER = 1,
	//	D3D12_COMPARISON_FUNC_LESS = 2,
	//	D3D12_COMPARISON_FUNC_EQUAL = 3,
	//	D3D12_COMPARISON_FUNC_LESS_EQUAL = 4,
	//	D3D12_COMPARISON_FUNC_GREATER = 5,
	//	D3D12_COMPARISON_FUNC_NOT_EQUAL = 6,
	//	D3D12_COMPARISON_FUNC_GREATER_EQUAL = 7,
	//	D3D12_COMPARISON_FUNC_ALWAYS = 8
	//}

	//enum class CompareOp
	//{
	//	eNever = VK_COMPARE_OP_NEVER,
	//	eLess = VK_COMPARE_OP_LESS,
	//	eEqual = VK_COMPARE_OP_EQUAL,
	//	eLessOrEqual = VK_COMPARE_OP_LESS_OR_EQUAL,
	//	eGreater = VK_COMPARE_OP_GREATER,
	//	eNotEqual = VK_COMPARE_OP_NOT_EQUAL,
	//	eGreaterOrEqual = VK_COMPARE_OP_GREATER_OR_EQUAL,
	//	eAlways = VK_COMPARE_OP_ALWAYS
	//};

	enum EComparisonOp : uint32_t
	{
		kComparisonOp_Never = 0,
		kComparisonOp_Less = 1,
		kComparisonOp_Equal = 2,
		kComparisonOp_LessEqual = 3,
		kComparisonOp_Greater = 4,
		kComparisonOp_NotEqual = 5,
		kComparisonOp_GreaterEqual = 6,
		kComparisonOp_Always = 7,

		kComparisonOp_NumOf,
		kComparisonOp_Unknown = kComparisonOp_NumOf
	};

	//---------------------------------------------------------------------------------------------------

	//typedef enum D3D12_STENCIL_OP {
	//	D3D12_STENCIL_OP_KEEP = 1,
	//	D3D12_STENCIL_OP_ZERO = 2,
	//	D3D12_STENCIL_OP_REPLACE = 3,
	//	D3D12_STENCIL_OP_INCR_SAT = 4,
	//	D3D12_STENCIL_OP_DECR_SAT = 5,
	//	D3D12_STENCIL_OP_INVERT = 6,
	//	D3D12_STENCIL_OP_INCR = 7,
	//	D3D12_STENCIL_OP_DECR = 8
	//}

	//typedef enum VkStencilOp {
	//	VK_STENCIL_OP_KEEP = 0,
	//	VK_STENCIL_OP_ZERO = 1,
	//	VK_STENCIL_OP_REPLACE = 2,
	//	VK_STENCIL_OP_INCREMENT_AND_CLAMP = 3,
	//	VK_STENCIL_OP_DECREMENT_AND_CLAMP = 4,
	//	VK_STENCIL_OP_INVERT = 5,
	//	VK_STENCIL_OP_INCREMENT_AND_WRAP = 6,
	//	VK_STENCIL_OP_DECREMENT_AND_WRAP = 7,
	//}

	// dx12 and vulkan stencil ops are identical (also dx12 INCR and DECR wrap)

	enum EStencilOp : uint32_t
	{
		kStencilOp_Keep = 0,
		kStencilOp_Zero = 1,
		kStencilOp_Replace = 2,
		kStencilOp_IncrementAndClamp = 3, //D3D12_STENCIL_OP_INCR_SAT
		kStencilOp_DecrementAndClamp = 4, //VK_STENCIL_OP_DECREMENT_AND_CLAMP
		kStencilOp_Invert = 5,
		kStencilOp_IncrementAndWrap = 6, //D3D12_STENCIL_OP_INCR
		kStencilOp_DecrementAndWrap = 7, //D3D12_STENCIL_OP_DECR

		kStencilOp_NumOf,
		kStencilOp_Unknown = kStencilOp_NumOf,
	};

	//---------------------------------------------------------------------------------------------------
	//typedef struct VkStencilOpState {
	//	VkStencilOp    failOp;
	//	VkStencilOp    passOp;
	//	VkStencilOp    depthFailOp;
	//	VkCompareOp    compareOp;
	//	uint32_t       compareMask;
	//	uint32_t       writeMask;
	//	uint32_t       reference;
	//}

	//typedef struct D3D12_DEPTH_STENCILOP_DESC {
	//	D3D12_STENCIL_OP      StencilFailOp;
	//	D3D12_STENCIL_OP      StencilDepthFailOp;
	//	D3D12_STENCIL_OP      StencilPassOp;
	//	D3D12_COMPARISON_FUNC StencilFunc;
	//}

	struct StencilOpDesc
	{
		EStencilOp kFailOp = kStencilOp_Unknown; // Stencil Fail op
		EStencilOp kPassOp = kStencilOp_Unknown; // Stencil Pass op
		EStencilOp kDepthFailOp = kStencilOp_Unknown;
		EComparisonOp kStencilCompareOp = kComparisonOp_Unknown;
	};

	//---------------------------------------------------------------------------------------------------
	//https://msdn.microsoft.com/en-us/library/windows/desktop/dn770356(v=vs.85).aspx
	//typedef struct D3D12_DEPTH_STENCIL_DESC {
	//	BOOL                       DepthEnable;
	//	D3D12_DEPTH_WRITE_MASK     DepthWriteMask;
	//	D3D12_COMPARISON_FUNC      DepthFunc;
	//	BOOL                       StencilEnable;
	//	UINT8                      StencilReadMask;
	//	UINT8                      StencilWriteMask;
	//	D3D12_DEPTH_STENCILOP_DESC FrontFace;
	//	D3D12_DEPTH_STENCILOP_DESC BackFace;
	//}

	//https://www.khronos.org/registry/vulkan/specs/1.0-wsi_extensions/html/vkspec.html#VkPipelineDepthStencilStateCreateInfo
	//typedef struct VkPipelineDepthStencilStateCreateInfo {
	//	VkStructureType                           sType;
	//	const void*                               pNext;
	//	VkPipelineDepthStencilStateCreateFlags    flags;
	//	VkBool32                                  depthTestEnable;
	//	VkBool32                                  depthWriteEnable;
	//	VkCompareOp                               depthCompareOp;
	//	VkBool32                                  depthBoundsTestEnable;
	//	VkBool32                                  stencilTestEnable;
	//	VkStencilOpState                          front;
	//	VkStencilOpState                          back;
	//	float                                     minDepthBounds;
	//	float                                     maxDepthBounds;
	//}

	//---------------------------------------------------------------------------------------------------

	struct DepthStencilStateDesc
	{
		bool bStencilTestEnabled = false;
		bool bDepthTestEnabled = false;
		bool bDepthWriteEnabled = false; //D3D12_DEPTH_WRITE_MASK
		EComparisonOp kDepthCompareOp = kComparisonOp_Unknown;

		StencilOpDesc FrontFace;
		StencilOpDesc BackFace;

		uint32_t uStencilReference = 0u;
		uint32_t uStencilCompareMask = 0xffffffff;
		uint32_t uStencilWriteMask = 0u;
		// todo: depthBoundsTestEnable etc
	};
	//---------------------------------------------------------------------------------------------------

	// Used to convert ComponentMapping in View creation
	enum EColorChannel : uint32_t
	{
		kColorChannel_Identity = 0u,	// Is Default
		kColorChannel_Zero = 1u,
		kColorChannel_One = 2u,
		kColorChannel_Red = 3u,
		kColorChannel_Green = 4u,
		kColorChannel_Blue = 5u,
		kColorChannel_Alpha = 6u,

		kColorChannel_NumOf,
		kColorChannel_Unkown = kColorChannel_NumOf
	};

	struct ColorSwizzle
	{
		EColorChannel Red;
		EColorChannel Green;
		EColorChannel Blue;
		EColorChannel Alpha;

		ColorSwizzle(const EColorChannel _kRed = kColorChannel_Identity, const EColorChannel _kGreen = kColorChannel_Identity, const EColorChannel _kBlue = kColorChannel_Identity, const EColorChannel _kAlpha = kColorChannel_Identity) :
			Red(_kRed),
			Green(_kGreen),
			Blue(_kBlue),
			Alpha(_kAlpha)
		{}
	};

	// https://www.khronos.org/registry/vulkan/specs/1.0-wsi_extensions/html/vkspec.html#VkImageAspectFlagBits
	/*VK_IMAGE_ASPECT_COLOR_BIT = 0x00000001,
	VK_IMAGE_ASPECT_DEPTH_BIT = 0x00000002,
	VK_IMAGE_ASPECT_STENCIL_BIT = 0x00000004,
	VK_IMAGE_ASPECT_METADATA_BIT = 0x00000008,
	VK_IMAGE_ASPECT_PLANE_0_BIT_KHR = 0x00000010,
	VK_IMAGE_ASPECT_PLANE_1_BIT_KHR = 0x00000020,
	VK_IMAGE_ASPECT_PLANE_2_BIT_KHR = 0x00000040,*/
	enum EAspect : uint32_t
	{
		kAspect_Color = (1 << 0),
		kAspect_Depth = (1 << 1),
		kAspect_Stencil = (1 << 2),
		kAspect_Metadata = (1 << 3),
		kAspect_NumOf = 4u,
		kAspect_None = 0u
	};


	// TODO: NumOf / Unknown pattern
	enum ETextureType : uint32_t
	{
		kTextureType_Texture1D,
		kTextureType_Texture2D,
		kTextureType_Texture3D,
		kTextureType_TextureCube,
		kTextureType_TextureArray1D,
		kTextureType_TextureArray2D,
		kTextureType_TextureArrayCube,

		kTextureType_NumOf,
		kTextureType_Invalid = kTextureType_NumOf,
	};

	enum EBufferType : uint32_t
	{
		kBufferType_Invalid = 0u
	};

	/*VK_IMAGE_USAGE_TRANSFER_SRC_BIT = 0x00000001,
	VK_IMAGE_USAGE_TRANSFER_DST_BIT = 0x00000002,
	VK_IMAGE_USAGE_SAMPLED_BIT = 0x00000004,
	VK_IMAGE_USAGE_STORAGE_BIT = 0x00000008,
	VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT = 0x00000010,
	VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT = 0x00000020,
	VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT = 0x00000040,
	VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT = 0x00000080,*/
	enum ETextureUsage : uint32_t
	{
		kTextureUsage_CopySource		= (1 << 0),
		kTextureUsage_CopyDestination	= (1 << 1),
		kTextureUsage_ShaderRead		= (1 << 2),
		kTextureUsage_ShaderStore		= (1 << 3),
		kTextureUsage_RenderTarget		= (1 << 4),
		kTextureUsage_DepthStencil		= (1 << 5),
		kTextureUsage_Transient			= (1 << 6),
		kTextureUsage_Subpass			= (1 << 7),

		kTextureUsage_NumOf = 8u,
		kTextureUsage_None = 0u
	};

	/*VK_BUFFER_USAGE_TRANSFER_SRC_BIT = 0x00000001,
	VK_BUFFER_USAGE_TRANSFER_DST_BIT = 0x00000002,
	VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT = 0x00000004,
	VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT = 0x00000008,
	VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT = 0x00000010,
	VK_BUFFER_USAGE_STORAGE_BUFFER_BIT = 0x00000020,
	VK_BUFFER_USAGE_INDEX_BUFFER_BIT = 0x00000040,
	VK_BUFFER_USAGE_VERTEX_BUFFER_BIT = 0x00000080,
	VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT = 0x00000100,*/
	enum EBufferUsage : uint32_t
	{
		kBufferUsage_CopySource			= (1 << 0),
		kBufferUsage_CopyDestination	= (1 << 1),
		kBufferUsage_UniformTexel		= (1 << 2),
		kBufferUsage_StorageTexel		= (1 << 3),
		kBufferUsage_Uniform			= (1 << 4),
		kBufferUsage_Storage			= (1 << 5),
		kBufferUsage_Index				= (1 << 6),
		kBufferUsage_Vertex				= (1 << 7),
		kBufferUsage_Indirect			= (1 << 8),

		kBufferUsage_NumOf = 9u,
		kBufferUsage_None = 0u
	};

	//enum EUsageFlag : uint32_t
	//{
	//	// Default
	//	kUsageFlag_None = 0u,
	//	// Buffer Types
	//	kUsageFlag_VertexBuffer = (1 << 0),		// VB
	//	kUsageFlag_IndexBuffer = (1 << 1),		// IB
	//	kUsageFlag_ConstantBuffer = (1 << 2),		// CB
	//	kUsageFlag_StorageBuffer = (1 << 3),		// Structured Buffer
	//	kUsageFlag_IndirectBuffer = (1 << 4),		// Indirect Draw Data
	//	// Texture Types
	//	kUsageFlag_RenderTarget = (1 << 5),		// RTV
	//	kUsageFlag_DepthStencil = (1 << 6),		// DSV
	//	kUsageFlag_ShaderRead = (1 << 7),		// SRV
	//	kUsageFlag_ShaderStore = (1 << 8),		// UAV
	//	kUsageFlag_CopySource = (1 << 9),		// BLIT_SRC
	//	kUsageFlag_CopyDestination = (1 << 10),	// BLIT_DST
	//	// Upper Bit Pos
	//	kUsageFlag_NumOf = 11u,
	//	kUsageFlag_Unknown = kUsageFlag_NumOf
	//};

	enum EFormat : uint32_t
	{
		// Default
		kFormat_Undefined = 0u,
		//------------------------
		// 8-bits per channel
		// 1-channel
		kFormat_R_8_UNORM,
		kFormat_R_8_SNORM,
		kFormat_R_8_UINT,
		kFormat_R_8_SINT,
		kFormat_R_8_SRGB,
		// 2-channels
		kFormat_RG_8_UNORM,
		kFormat_RG_8_SNORM,
		kFormat_RG_8_UINT,
		kFormat_RG_8_SINT,
		kFormat_RG_8_SRGB,
		// 3-channels
		kFormat_RGB_8_UNORM,
		kFormat_RGB_8_SNORM,
		kFormat_RGB_8_UINT,
		kFormat_RGB_8_SINT,
		kFormat_RGB_8_SRGB,
		// 3-channels
		kFormat_BGR_8_UNORM,
		kFormat_BGR_8_SNORM,
		kFormat_BGR_8_UINT,
		kFormat_BGR_8_SINT,
		kFormat_BGR_8_SRGB,
		// 4-channels
		kFormat_RGBA_8_UNORM,
		kFormat_RGBA_8_SNORM,
		kFormat_RGBA_8_UINT,
		kFormat_RGBA_8_SINT,
		kFormat_RGBA_8_SRGB,
		// 4-channels
		kFormat_BGRA_8_UNORM,
		kFormat_BGRA_8_SNORM,
		kFormat_BGRA_8_UINT,
		kFormat_BGRA_8_SINT,
		kFormat_BGRA_8_SRGB,
		// 4-channels-pack
		kFormat_ABGR_8_UNORM_PACK32,
		kFormat_ABGR_8_SNORM_PACK32,
		kFormat_ABGR_8_UINT_PACK32,
		kFormat_ABGR_8_SINT_PACK32,
		kFormat_ABGR_8_SRGB_PACK32,
		//------------------------
		// 16-bits per channel
		// 1-channel
		kFormat_R_16_UNORM,
		kFormat_R_16_SNORM,
		kFormat_R_16_UINT,
		kFormat_R_16_SINT,
		kFormat_R_16_FLOAT,
		// 2-channels
		kFormat_RG_16_UNORM,
		kFormat_RG_16_SNORM,
		kFormat_RG_16_UINT,
		kFormat_RG_16_SINT,
		kFormat_RG_16_FLOAT,
		// 3-channels
		kFormat_RGB_16_UNORM,
		kFormat_RGB_16_SNORM,
		kFormat_RGB_16_UINT,
		kFormat_RGB_16_SINT,
		kFormat_RGB_16_FLOAT,
		// 4-channels
		kFormat_RGBA_16_UNORM,
		kFormat_RGBA_16_SNORM,
		kFormat_RGBA_16_UINT,
		kFormat_RGBA_16_SINT,
		kFormat_RGBA_16_FLOAT,
		//------------------------
		// 32-bits per channel
		// 1-channel
		kFormat_R_32_UINT,
		kFormat_R_32_SINT,
		kFormat_R_32_FLOAT,
		// 2-channel
		kFormat_RG_32_UINT,
		kFormat_RG_32_SINT,
		kFormat_RG_32_FLOAT,
		// 3-channel
		kFormat_RGB_32_UINT,
		kFormat_RGB_32_SINT,
		kFormat_RGB_32_FLOAT,
		// 4-channel
		kFormat_RGBA_32_UINT,
		kFormat_RGBA_32_SINT,
		kFormat_RGBA_32_FLOAT,
		//------------------------
		// 64-bits per channel
		// 1-channel
		kFormat_R_64_UINT,
		kFormat_R_64_SINT,
		kFormat_R_64_FLOAT,
		// 2-channel
		kFormat_RG_64_UINT,
		kFormat_RG_64_SINT,
		kFormat_RG_64_FLOAT,
		// 3-channel
		kFormat_RGB_64_UINT,
		kFormat_RGB_64_SINT,
		kFormat_RGB_64_FLOAT,
		// 4-channel
		kFormat_RGBA_64_UINT,
		kFormat_RGBA_64_SINT,
		kFormat_RGBA_64_FLOAT,
		//------------------------
		// Depth Formats, mixed size
		// Depth only
		kFormat_D_16_UNORM,
		kFormat_D_32_FLOAT,
		// Stencil Only
		kFormat_S_8_UINT,
		// Depth + Stencil
		kFormat_X8_D24_UNORM_PACK32,
		kFormat_D16_UNORM_S8_UINT,
		kFormat_D24_UNORM_S8_UINT,
		kFormat_D32_SFLOAT_S8_UINT,
		//------------------------
		// Compressed Formats

		kFormat_NumOf
	};

	// VK FORMATS, we use a subset for now
	/*VK_FORMAT_UNDEFINED = 0,
		VK_FORMAT_R4G4_UNORM_PACK8 = 1,
		VK_FORMAT_R4G4B4A4_UNORM_PACK16 = 2,
		VK_FORMAT_B4G4R4A4_UNORM_PACK16 = 3,
		VK_FORMAT_R5G6B5_UNORM_PACK16 = 4,
		VK_FORMAT_B5G6R5_UNORM_PACK16 = 5,
		VK_FORMAT_R5G5B5A1_UNORM_PACK16 = 6,
		VK_FORMAT_B5G5R5A1_UNORM_PACK16 = 7,
		VK_FORMAT_A1R5G5B5_UNORM_PACK16 = 8,
		VK_FORMAT_R8_UNORM = 9,
		VK_FORMAT_R8_SNORM = 10,
		VK_FORMAT_R8_USCALED = 11,
		VK_FORMAT_R8_SSCALED = 12,
		VK_FORMAT_R8_UINT = 13,
		VK_FORMAT_R8_SINT = 14,
		VK_FORMAT_R8_SRGB = 15,
		VK_FORMAT_R8G8_UNORM = 16,
		VK_FORMAT_R8G8_SNORM = 17,
		VK_FORMAT_R8G8_USCALED = 18,
		VK_FORMAT_R8G8_SSCALED = 19,
		VK_FORMAT_R8G8_UINT = 20,
		VK_FORMAT_R8G8_SINT = 21,
		VK_FORMAT_R8G8_SRGB = 22,
		VK_FORMAT_R8G8B8_UNORM = 23,
		VK_FORMAT_R8G8B8_SNORM = 24,
		VK_FORMAT_R8G8B8_USCALED = 25,
		VK_FORMAT_R8G8B8_SSCALED = 26,
		VK_FORMAT_R8G8B8_UINT = 27,
		VK_FORMAT_R8G8B8_SINT = 28,
		VK_FORMAT_R8G8B8_SRGB = 29,
		VK_FORMAT_B8G8R8_UNORM = 30,
		VK_FORMAT_B8G8R8_SNORM = 31,
		VK_FORMAT_B8G8R8_USCALED = 32,
		VK_FORMAT_B8G8R8_SSCALED = 33,
		VK_FORMAT_B8G8R8_UINT = 34,
		VK_FORMAT_B8G8R8_SINT = 35,
		VK_FORMAT_B8G8R8_SRGB = 36,
		VK_FORMAT_R8G8B8A8_UNORM = 37,
		VK_FORMAT_R8G8B8A8_SNORM = 38,
		VK_FORMAT_R8G8B8A8_USCALED = 39,
		VK_FORMAT_R8G8B8A8_SSCALED = 40,
		VK_FORMAT_R8G8B8A8_UINT = 41,
		VK_FORMAT_R8G8B8A8_SINT = 42,
		VK_FORMAT_R8G8B8A8_SRGB = 43,
		VK_FORMAT_B8G8R8A8_UNORM = 44,
		VK_FORMAT_B8G8R8A8_SNORM = 45,
		VK_FORMAT_B8G8R8A8_USCALED = 46,
		VK_FORMAT_B8G8R8A8_SSCALED = 47,
		VK_FORMAT_B8G8R8A8_UINT = 48,
		VK_FORMAT_B8G8R8A8_SINT = 49,
		VK_FORMAT_B8G8R8A8_SRGB = 50,
		VK_FORMAT_A8B8G8R8_UNORM_PACK32 = 51,
		VK_FORMAT_A8B8G8R8_SNORM_PACK32 = 52,
		VK_FORMAT_A8B8G8R8_USCALED_PACK32 = 53,
		VK_FORMAT_A8B8G8R8_SSCALED_PACK32 = 54,
		VK_FORMAT_A8B8G8R8_UINT_PACK32 = 55,
		VK_FORMAT_A8B8G8R8_SINT_PACK32 = 56,
		VK_FORMAT_A8B8G8R8_SRGB_PACK32 = 57,
		VK_FORMAT_A2R10G10B10_UNORM_PACK32 = 58,
		VK_FORMAT_A2R10G10B10_SNORM_PACK32 = 59,
		VK_FORMAT_A2R10G10B10_USCALED_PACK32 = 60,
		VK_FORMAT_A2R10G10B10_SSCALED_PACK32 = 61,
		VK_FORMAT_A2R10G10B10_UINT_PACK32 = 62,
		VK_FORMAT_A2R10G10B10_SINT_PACK32 = 63,
		VK_FORMAT_A2B10G10R10_UNORM_PACK32 = 64,
		VK_FORMAT_A2B10G10R10_SNORM_PACK32 = 65,
		VK_FORMAT_A2B10G10R10_USCALED_PACK32 = 66,
		VK_FORMAT_A2B10G10R10_SSCALED_PACK32 = 67,
		VK_FORMAT_A2B10G10R10_UINT_PACK32 = 68,
		VK_FORMAT_A2B10G10R10_SINT_PACK32 = 69,
		VK_FORMAT_R16_UNORM = 70,
		VK_FORMAT_R16_SNORM = 71,
		VK_FORMAT_R16_USCALED = 72,
		VK_FORMAT_R16_SSCALED = 73,
		VK_FORMAT_R16_UINT = 74,
		VK_FORMAT_R16_SINT = 75,
		VK_FORMAT_R16_SFLOAT = 76,
		VK_FORMAT_R16G16_UNORM = 77,
		VK_FORMAT_R16G16_SNORM = 78,
		VK_FORMAT_R16G16_USCALED = 79,
		VK_FORMAT_R16G16_SSCALED = 80,
		VK_FORMAT_R16G16_UINT = 81,
		VK_FORMAT_R16G16_SINT = 82,
		VK_FORMAT_R16G16_SFLOAT = 83,
		VK_FORMAT_R16G16B16_UNORM = 84,
		VK_FORMAT_R16G16B16_SNORM = 85,
		VK_FORMAT_R16G16B16_USCALED = 86,
		VK_FORMAT_R16G16B16_SSCALED = 87,
		VK_FORMAT_R16G16B16_UINT = 88,
		VK_FORMAT_R16G16B16_SINT = 89,
		VK_FORMAT_R16G16B16_SFLOAT = 90,
		VK_FORMAT_R16G16B16A16_UNORM = 91,
		VK_FORMAT_R16G16B16A16_SNORM = 92,
		VK_FORMAT_R16G16B16A16_USCALED = 93,
		VK_FORMAT_R16G16B16A16_SSCALED = 94,
		VK_FORMAT_R16G16B16A16_UINT = 95,
		VK_FORMAT_R16G16B16A16_SINT = 96,
		VK_FORMAT_R16G16B16A16_SFLOAT = 97,
		VK_FORMAT_R32_UINT = 98,
		VK_FORMAT_R32_SINT = 99,
		VK_FORMAT_R32_SFLOAT = 100,
		VK_FORMAT_R32G32_UINT = 101,
		VK_FORMAT_R32G32_SINT = 102,
		VK_FORMAT_R32G32_SFLOAT = 103,
		VK_FORMAT_R32G32B32_UINT = 104,
		VK_FORMAT_R32G32B32_SINT = 105,
		VK_FORMAT_R32G32B32_SFLOAT = 106,
		VK_FORMAT_R32G32B32A32_UINT = 107,
		VK_FORMAT_R32G32B32A32_SINT = 108,
		VK_FORMAT_R32G32B32A32_SFLOAT = 109,
		VK_FORMAT_R64_UINT = 110,
		VK_FORMAT_R64_SINT = 111,
		VK_FORMAT_R64_SFLOAT = 112,
		VK_FORMAT_R64G64_UINT = 113,
		VK_FORMAT_R64G64_SINT = 114,
		VK_FORMAT_R64G64_SFLOAT = 115,
		VK_FORMAT_R64G64B64_UINT = 116,
		VK_FORMAT_R64G64B64_SINT = 117,
		VK_FORMAT_R64G64B64_SFLOAT = 118,
		VK_FORMAT_R64G64B64A64_UINT = 119,
		VK_FORMAT_R64G64B64A64_SINT = 120,
		VK_FORMAT_R64G64B64A64_SFLOAT = 121,
		VK_FORMAT_B10G11R11_UFLOAT_PACK32 = 122,
		VK_FORMAT_E5B9G9R9_UFLOAT_PACK32 = 123,
		VK_FORMAT_D16_UNORM = 124,
		VK_FORMAT_X8_D24_UNORM_PACK32 = 125,
		VK_FORMAT_D32_SFLOAT = 126,
		VK_FORMAT_S8_UINT = 127,
		VK_FORMAT_D16_UNORM_S8_UINT = 128,
		VK_FORMAT_D24_UNORM_S8_UINT = 129,
		VK_FORMAT_D32_SFLOAT_S8_UINT = 130,
		VK_FORMAT_BC1_RGB_UNORM_BLOCK = 131,
		VK_FORMAT_BC1_RGB_SRGB_BLOCK = 132,
		VK_FORMAT_BC1_RGBA_UNORM_BLOCK = 133,
		VK_FORMAT_BC1_RGBA_SRGB_BLOCK = 134,
		VK_FORMAT_BC2_UNORM_BLOCK = 135,
		VK_FORMAT_BC2_SRGB_BLOCK = 136,
		VK_FORMAT_BC3_UNORM_BLOCK = 137,
		VK_FORMAT_BC3_SRGB_BLOCK = 138,
		VK_FORMAT_BC4_UNORM_BLOCK = 139,
		VK_FORMAT_BC4_SNORM_BLOCK = 140,
		VK_FORMAT_BC5_UNORM_BLOCK = 141,
		VK_FORMAT_BC5_SNORM_BLOCK = 142,
		VK_FORMAT_BC6H_UFLOAT_BLOCK = 143,
		VK_FORMAT_BC6H_SFLOAT_BLOCK = 144,
		VK_FORMAT_BC7_UNORM_BLOCK = 145,
		VK_FORMAT_BC7_SRGB_BLOCK = 146,
		VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK = 147,
		VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK = 148,
		VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK = 149,
		VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK = 150,
		VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK = 151,
		VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK = 152,
		VK_FORMAT_EAC_R11_UNORM_BLOCK = 153,
		VK_FORMAT_EAC_R11_SNORM_BLOCK = 154,
		VK_FORMAT_EAC_R11G11_UNORM_BLOCK = 155,
		VK_FORMAT_EAC_R11G11_SNORM_BLOCK = 156,
		VK_FORMAT_ASTC_4x4_UNORM_BLOCK = 157,
		VK_FORMAT_ASTC_4x4_SRGB_BLOCK = 158,
		VK_FORMAT_ASTC_5x4_UNORM_BLOCK = 159,
		VK_FORMAT_ASTC_5x4_SRGB_BLOCK = 160,
		VK_FORMAT_ASTC_5x5_UNORM_BLOCK = 161,
		VK_FORMAT_ASTC_5x5_SRGB_BLOCK = 162,
		VK_FORMAT_ASTC_6x5_UNORM_BLOCK = 163,
		VK_FORMAT_ASTC_6x5_SRGB_BLOCK = 164,
		VK_FORMAT_ASTC_6x6_UNORM_BLOCK = 165,
		VK_FORMAT_ASTC_6x6_SRGB_BLOCK = 166,
		VK_FORMAT_ASTC_8x5_UNORM_BLOCK = 167,
		VK_FORMAT_ASTC_8x5_SRGB_BLOCK = 168,
		VK_FORMAT_ASTC_8x6_UNORM_BLOCK = 169,
		VK_FORMAT_ASTC_8x6_SRGB_BLOCK = 170,
		VK_FORMAT_ASTC_8x8_UNORM_BLOCK = 171,
		VK_FORMAT_ASTC_8x8_SRGB_BLOCK = 172,
		VK_FORMAT_ASTC_10x5_UNORM_BLOCK = 173,
		VK_FORMAT_ASTC_10x5_SRGB_BLOCK = 174,
		VK_FORMAT_ASTC_10x6_UNORM_BLOCK = 175,
		VK_FORMAT_ASTC_10x6_SRGB_BLOCK = 176,
		VK_FORMAT_ASTC_10x8_UNORM_BLOCK = 177,
		VK_FORMAT_ASTC_10x8_SRGB_BLOCK = 178,
		VK_FORMAT_ASTC_10x10_UNORM_BLOCK = 179,
		VK_FORMAT_ASTC_10x10_SRGB_BLOCK = 180,
		VK_FORMAT_ASTC_12x10_UNORM_BLOCK = 181,
		VK_FORMAT_ASTC_12x10_SRGB_BLOCK = 182,
		VK_FORMAT_ASTC_12x12_UNORM_BLOCK = 183,
		VK_FORMAT_ASTC_12x12_SRGB_BLOCK = 184,
		VK_FORMAT_G8B8G8R8_422_UNORM_KHR = 1000156000,
		VK_FORMAT_B8G8R8G8_422_UNORM_KHR = 1000156001,
		VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM_KHR = 1000156002,
		VK_FORMAT_G8_B8R8_2PLANE_420_UNORM_KHR = 1000156003,
		VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM_KHR = 1000156004,
		VK_FORMAT_G8_B8R8_2PLANE_422_UNORM_KHR = 1000156005,
		VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM_KHR = 1000156006,
		VK_FORMAT_R10X6_UNORM_PACK16_KHR = 1000156007,
		VK_FORMAT_R10X6G10X6_UNORM_2PACK16_KHR = 1000156008,
		VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16_KHR = 1000156009,
		VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16_KHR = 1000156010,
		VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16_KHR = 1000156011,
		VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16_KHR = 1000156012,
		VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16_KHR = 1000156013,
		VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16_KHR = 1000156014,
		VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16_KHR = 1000156015,
		VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16_KHR = 1000156016,
		VK_FORMAT_R12X4_UNORM_PACK16_KHR = 1000156017,
		VK_FORMAT_R12X4G12X4_UNORM_2PACK16_KHR = 1000156018,
		VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16_KHR = 1000156019,
		VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16_KHR = 1000156020,
		VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16_KHR = 1000156021,
		VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16_KHR = 1000156022,
		VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16_KHR = 1000156023,
		VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16_KHR = 1000156024,
		VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16_KHR = 1000156025,
		VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16_KHR = 1000156026,
		VK_FORMAT_G16B16G16R16_422_UNORM_KHR = 1000156027,
		VK_FORMAT_B16G16R16G16_422_UNORM_KHR = 1000156028,
		VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM_KHR = 1000156029,
		VK_FORMAT_G16_B16R16_2PLANE_420_UNORM_KHR = 1000156030,
		VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM_KHR = 1000156031,
		VK_FORMAT_G16_B16R16_2PLANE_422_UNORM_KHR = 1000156032,
		VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM_KHR = 1000156033,*/

		//https://msdn.microsoft.com/en-us/library/windows/desktop/dn770403(v=vs.85).aspx
		//typedef struct D3D12_SAMPLER_DESC {
		//	D3D12_FILTER               Filter;
		//	D3D12_TEXTURE_ADDRESS_MODE AddressU;
		//	D3D12_TEXTURE_ADDRESS_MODE AddressV;
		//	D3D12_TEXTURE_ADDRESS_MODE AddressW;
		//	FLOAT                      MipLODBias;
		//	UINT                       MaxAnisotropy;
		//	D3D12_COMPARISON_FUNC      ComparisonFunc;
		//	FLOAT                      BorderColor[4];
		//	FLOAT                      MinLOD;
		//	FLOAT                      MaxLOD;
		//}

		//VkFilter
		//typedef enum VkFilter {
		//	VK_FILTER_NEAREST = 0,
		//	VK_FILTER_LINEAR = 1,
		//}
	enum ESamplerFilter : uint32_t
	{
		kSamplerFilter_Nearest = 0,
		kSamplerFilter_Linear = 1,

		kSamplerFilter_NumOf,
		kSamplerFilter_Unknown = kSamplerFilter_NumOf
	};

	//typedef enum VkSamplerMipmapMode {
	//	VK_SAMPLER_MIPMAP_MODE_NEAREST = 0,
	//	VK_SAMPLER_MIPMAP_MODE_LINEAR = 1,
	//}
	enum ESamplerMipmapMode : uint32_t
	{
		kSamplerMipmapMode_Nearest = 0u,
		kSamplerMipmapMode_Linear = 1,

		kSamplerMipmapMode_NumOf,
		kSamplerMipmapMode_Unknown = kSamplerMipmapMode_NumOf
	};

	//typedef enum VkSamplerAddressMode {
	//	VK_SAMPLER_ADDRESS_MODE_REPEAT = 0,
	//	VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT = 1,
	//	VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE = 2,
	//	VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER = 3,
	//	VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE = 4,
	//}

	enum ESamplerAddressMode : uint32_t
	{
		kSamplerAddressMode_Repeat = 0,
		kSamplerAddressMode_RepeatMirrored = 1,
		kSamplerAddressMode_ClamToEdge = 2,
		kSamplerAddressMode_ClampToBorder = 3,
		kSamplerAddressMode_MirrorClamToEdge = 4,

		kSamplerAddressMode_NumOf,
		kSamplerAddressMode_Unknown = kSamplerAddressMode_NumOf
	};

	//typedef enum VkBorderColor {
	//	VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK = 0,
	//	VK_BORDER_COLOR_INT_TRANSPARENT_BLACK = 1,
	//	VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK = 2,
	//	VK_BORDER_COLOR_INT_OPAQUE_BLACK = 3,
	//	VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE = 4,
	//	VK_BORDER_COLOR_INT_OPAQUE_WHITE = 5,
	//}

	enum ESamplerBorderColor
	{
		kSamplerBorderColor_TransparentBlackFloat = 0,
		kSamplerBorderColor_TransparentBlackInt = 1,
		kSamplerBorderColor_OpaqueBlackFloat = 2,
		kSamplerBorderColor_OpaqueBlackInt = 3,
		kSamplerBorderColor_OpaqueWhiteFloat = 4,
		kSamplerBorderColor_OpaqueWhiteInt = 5,

		kSamplerBorderColor_NumOf,
		kSamplerBorderColor_Unknown = kSamplerBorderColor_NumOf
	};

	//https://www.khronos.org/registry/vulkan/specs/1.0-wsi_extensions/html/vkspec.html#VkSamplerCreateInfo
	//typedef struct VkSamplerCreateInfo {
	//	VkStructureType         sType;
	//	const void*             pNext;
	//	VkSamplerCreateFlags    flags;
	//	VkFilter                magFilter;
	//	VkFilter                minFilter;
	//	VkSamplerMipmapMode     mipmapMode;
	//	VkSamplerAddressMode    addressModeU;
	//	VkSamplerAddressMode    addressModeV;
	//	VkSamplerAddressMode    addressModeW;
	//	float                   mipLodBias;
	//	VkBool32                anisotropyEnable;
	//	float                   maxAnisotropy;
	//	VkBool32                compareEnable;
	//	VkCompareOp             compareOp;
	//	float                   minLod;
	//	float                   maxLod;
	//	VkBorderColor           borderColor;
	//	VkBool32                unnormalizedCoordinates;
	//}

	struct SamplerDesc
	{
		ESamplerFilter kMagFiter = kSamplerFilter_Nearest;
		ESamplerFilter kMinFiter = kSamplerFilter_Nearest;
		ESamplerMipmapMode kMipmapMode = kSamplerMipmapMode_Nearest;

		ESamplerAddressMode kAddressModeU = kSamplerAddressMode_Repeat;
		ESamplerAddressMode kAddressModeV = kSamplerAddressMode_Repeat;
		ESamplerAddressMode kAddressModeW = kSamplerAddressMode_Repeat;

		float fMipLodBias = 0.f;
		bool bEnableAnisotropy = false;
		float fMaxAnisotropy = 1.f;

		bool bEnableCompare = false;
		EComparisonOp kCompareOp = kComparisonOp_Never;

		float fMinLod = 0.f;
		float fMaxLod = 1.f;

		ESamplerBorderColor kBorderColor = kSamplerBorderColor_OpaqueBlackFloat;

		bool bUnnormalizedCoordinates = false;
	};

	enum ETextureViewType
	{
		kViewType_ShaderResource = 0u,
		kViewType_RenderTarget,
		kViewType_DepthStencil,
		kViewType_NumOf
	};

	enum EIndexType : uint32_t
	{
		kIndexType_UInt16 = 0,
		kIndexType_UInt32,

		kIndexType_NumOf,
		kIndexType_Unknown = kIndexType_NumOf
	};

	enum EDrawMode : uint32_t
	{
		kDrawMode_VertexCount = 0,
		kDrawMode_VertexData = 1,
		kDrawMode_IndexData = 2,
		kDrawMode_Indirect = 3
	};

struct TextureDesc
{
	THandle hDevice = 0u; // Owner
	uint64_t uIdentifier = HUNDEFINED64; // filled by device
	uint16_t uWidth = 0u;
	uint16_t uHeight = 0u;
	uint16_t uDepth = 0u;
	uint32_t uLayerCount = 0u;
	EFormat kFormat = kFormat_Undefined;
	ETextureUsage kUsageFlag = kTextureUsage_None;
	ETextureType kType = kTextureType_Invalid;
	//std::string sName = "NewTexture";
};

struct BufferDesc
{
	THandle hDevice = 0u;
	uint64_t uIdentifier = HUNDEFINED64; // filled by device
	size_t uSize = 0u;
	const void* pInitialData = nullptr;
	const size_t uInitialDataOffset = 0u;
	const size_t uInitialDataSize = 0u; // must be in bounds with uSize
	EBufferUsage kUsageFlag = kBufferUsage_None;
};

} // Tracy

#endif // !TRACY_DISPLAYTYPES_H