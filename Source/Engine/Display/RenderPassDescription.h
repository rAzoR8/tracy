#ifndef TRACY_RENDERPASSDESCRIPTION_H
#define TRACY_RENDERPASSDESCRIPTION_H

#include "DisplayTypes.h"
//#include "Bytes.h"
#include <vector>

// platform independant description needed to create/load a renderpass
namespace Tracy
{
	struct PipelineDesc
	{
		struct ShaderDesc
		{
			ShaderID Identifier;
			//hlx::bytes UserData;
		};

		std::vector<ShaderDesc> Shaders;
		// spec const data?

		bool bBasePipeline = false;

		// IA Stage
		EPrimitiveTopology kPrimitiveTopology = kPrimitiveTopology_Unknown;

		// Rasterizer Stage
		EPolygonFillMode kFillMode = kPolygonFillMode_Unknown;
		ECullMode kCullMode = kCullMode_Unknown;
		EFrontFace kFrontFace = kFrontFace_Unknown;
		
		bool bDepthBiasEnabled = false;
		float fDepthBiasConstFactor = 0.f;
		float fDepthBiasClamp = 0.f;
		float fDepthBiasSlopeFactor = 0.f;
		float fLineWidth = 0.f;

		// Tesselation Stage
		uint32_t uPatchControlPointCount = 0u;

		// DepthStencil State
		DepthStencilStateDesc DepthStencilState;

		struct MappedSampler
		{
			std::string sName;
			SamplerDesc Desc;
		};

		std::vector<MappedSampler> Samplers;
	};

	struct InputDependency
	{
		std::wstring sPrevPassName;

		enum EResourceType : uint32_t
		{
			kResourceType_Image = 0,
			kResourceType_Buffer,
			kResourceType_Unknown
		};

		struct Resource
		{
			EResourceType kType = kResourceType_Unknown;
			std::wstring sName; // name of the output variable
			// TODO: stage at which this resources need to be available to the next renderpass
		};

		// dependencies
		std::vector<Resource> Resources;
	};

	enum EResizeEventType : uint32_t
	{
		kResizeEvent_None = 0, // no resize
		kResizeEvent_Relative, // relative size change wrt to Source (Backbuffer)
		kResizeEvent_Absolute // same size as source
	};

	enum EAttachmentSourceType : uint32_t
	{
		kAttachmentSourceType_New = 0, // create new
		kAttachmentSourceType_Copy, // copy the resource (pixel data)
		kAttachmentSourceType_Use // donno yet
	};

	// default events
	static const std::string sBackbufferAbsoluteResize = "TRACY_BACKBUFFER_ABSOLUTE_RESIZE";
	static const std::string sBackbufferRelativeResize = "TRACY_BACKBUFFER_RELATIVE_RESIZE";
	
	struct FramebufferDesc
	{
		// use this to describe renderagets and usage
		struct Attachment
		{
			EResizeEventType kResizeType = kResizeEvent_None;
			std::string sResizeEventName;

			EAttachmentSourceType kSource = kAttachmentSourceType_New;

			// only used when kSource == kAttachmentSourceType_New
			uint32_t uInitialHeight = 0u;
			uint32_t uInitialWidth = 0u;
			// Initial format
		};

	};

	struct DescriptorSetRate
	{
		uint32_t uSet = 0u;
		uint32_t uCount = 0u; // number of unique sets to pre allocate for uSet
	};

	struct RenderPassDesc
	{
		std::wstring sPassName; // name of this pass
		std::wstring sLibName; // dll that contains the shader factory
		
		std::vector<DescriptorSetRate> DescriptorSetRates;

		FramebufferDesc Framebuffer; 

		// shaders / pipelines that are frequently used
		std::vector<PipelineDesc> DefaultPipelines; // pipelines will be created for these on Initialize

		std::vector<RenderPassDesc> SubPasses;

		std::vector<InputDependency> InputDependencies; // dependencies to previous renderpasses
	};

	// TODO: think about subpasses when resolving dependencies
	struct RenderGraphDesc
	{
		// graph is encoded in InputDependencies
		std::vector<RenderPassDesc> Passes;
	};
} // Tracy

#endif // !TRACY_RENDERPASSDESCRIPTION_H
