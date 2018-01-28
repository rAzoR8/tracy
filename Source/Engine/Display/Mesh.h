#ifndef TRACY_MESH_H
#define TRACY_MESH_H

#include "GPUBuffer.h"

namespace Tracy
{
	// do something like helix meshcluster and stuff
	class Mesh
	{
	public:
		// default constructor
		Mesh(
			const EDrawMode _kDrawMode = kDrawMode_VertexData,
			const uint32_t _uVertexCount = 0u,
			const GPUBuffer& _VertexBuffer = nullptr,
			const uint32_t _uFirstVertex = 0u,
			const uint32_t _uVertexOffset = 0u,

			const uint32_t _uIndexCount = 0u,
			const GPUBuffer& _IndexBuffer = nullptr,
			const EIndexType _kIndexType = kIndexType_UInt32,
			const uint32_t _uFirstIndex = 0u,
			const uint32_t _uIndexOffset = 0u,

			const uint32_t _uInstanceCount = 1u,
			const uint32_t _uFirstInstance = 0u) :

			m_kDrawMode(_kDrawMode),
			m_uVertexCount(_uVertexCount),
			m_VertexBuffer(_VertexBuffer),
			m_uFirstVertex(_uFirstVertex),
			m_uVertexOffset(_uVertexOffset),

			m_uIndexCount(_uIndexCount),
			m_IndexBuffer(_IndexBuffer),
			m_kIndexType(_kIndexType),
			m_uFirstIndex(_uFirstIndex),
			m_uIndexOffset(_uIndexOffset),

			m_uInstanceCount(_uInstanceCount),
			m_uFirstInstance(_uFirstInstance)
		{};

		// vertexbuffer move
		Mesh(
			GPUBuffer&& _VertexBuffer,
			const uint32_t _uVertexCount = 0u,
			const EDrawMode _kDrawMode = kDrawMode_VertexData,
			const uint32_t _uFirstVertex = 0u,
			const uint32_t _uVertexOffset = 0u,

			const uint32_t _uIndexCount = 0u,
			const GPUBuffer& _IndexBuffer = nullptr,
			const EIndexType _kIndexType = kIndexType_UInt32,
			const uint32_t _uFirstIndex = 0u,
			const uint32_t _uIndexOffset = 0u,

			const uint32_t _uInstanceCount = 1u,
			const uint32_t _uFirstInstance = 0u) :

			m_kDrawMode(_kDrawMode),
			m_uVertexCount(_uVertexCount),
			m_VertexBuffer(std::forward<GPUBuffer>(_VertexBuffer)),
			m_uFirstVertex(_uFirstVertex),
			m_uVertexOffset(_uVertexOffset),

			m_uIndexCount(_uIndexCount),
			m_IndexBuffer(_IndexBuffer),
			m_kIndexType(_kIndexType),
			m_uFirstIndex(_uFirstIndex),
			m_uIndexOffset(_uIndexOffset),

			m_uInstanceCount(_uInstanceCount),
			m_uFirstInstance(_uFirstInstance)
		{};

		// move buffer constructor
		Mesh(
			GPUBuffer&& _VertexBuffer,
			GPUBuffer&& _IndexBuffer,
			const EDrawMode _kDrawMode = kDrawMode_VertexData,
			const uint32_t _uVertexCount = 0u,
			const uint32_t _uFirstVertex = 0u,
			const uint32_t _uVertexOffset = 0u,

			const uint32_t _uIndexCount = 0u,
			const EIndexType _kIndexType = kIndexType_UInt32,
			const uint32_t _uFirstIndex = 0u,
			const uint32_t _uIndexOffset = 0u,

			const uint32_t _uInstanceCount = 1u,
			const uint32_t _uFirstInstance = 0u) :

			m_kDrawMode(_kDrawMode),
			m_uVertexCount(_uVertexCount),
			m_VertexBuffer(std::forward<GPUBuffer>(_VertexBuffer)),
			m_uFirstVertex(_uFirstVertex),
			m_uVertexOffset(_uVertexOffset),

			m_uIndexCount(_uIndexCount),
			m_IndexBuffer(std::forward<GPUBuffer>(_IndexBuffer)),
			m_kIndexType(_kIndexType),
			m_uFirstIndex(_uFirstIndex),
			m_uIndexOffset(_uIndexOffset),

			m_uInstanceCount(_uInstanceCount),
			m_uFirstInstance(_uFirstInstance)
		{};

		virtual ~Mesh() {};

		const GPUBuffer& GetVertexBuffer() const;
		const GPUBuffer& GetIndexBuffer() const;

		const uint32_t& GetFirstVertex() const noexcept;
		const uint32_t& GetVertexOffset() const noexcept;
		const uint32_t& GetVertexCount() const noexcept;
		const uint32_t& GetIndexCount() const noexcept;
		const uint32_t& GetIndexOffset() const noexcept;
		const uint32_t& GetFirstIndex() const noexcept;
		const uint32_t& GetInstanceCount() const noexcept;
		const uint32_t& GetFirstInstance() const noexcept;

		const EDrawMode GetDrawMode() const noexcept;
		const EIndexType GetIndexType() const noexcept;

	private:
		EDrawMode m_kDrawMode = kDrawMode_VertexData;

		GPUBuffer m_VertexBuffer;
		uint32_t m_uVertexCount = 0u;
		uint32_t m_uFirstVertex = 0u;
		uint32_t m_uVertexOffset = 0u;

		GPUBuffer m_IndexBuffer;
		uint32_t m_uIndexCount = 0u;
		uint32_t m_uFirstIndex = 0u;
		EIndexType m_kIndexType = kIndexType_UInt32;
		uint32_t m_uIndexOffset = 0u;

		uint32_t m_uInstanceCount = 1u;
		uint32_t m_uFirstInstance = 0u;
	};
	//---------------------------------------------------------------------------------------------------

	inline const GPUBuffer& Mesh::GetVertexBuffer() const
	{
		return m_VertexBuffer;
	}
	inline const GPUBuffer& Mesh::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

	inline const uint32_t& Mesh::GetFirstVertex() const noexcept
	{
		return m_uFirstVertex;
	}
	inline const uint32_t& Mesh::GetVertexOffset() const  noexcept
	{
		return m_uVertexOffset;
	}
	inline const uint32_t& Mesh::GetVertexCount() const noexcept
	{
		return m_uVertexCount;
	}
	inline const uint32_t& Mesh::GetIndexCount() const noexcept
	{
		return m_uIndexCount;
	}
	inline const uint32_t& Mesh::GetIndexOffset() const noexcept
	{
		return m_uIndexOffset;
	}
	inline const uint32_t& Mesh::GetFirstIndex() const noexcept
	{
		return m_uFirstIndex;
	}
	inline const uint32_t& Mesh::GetInstanceCount() const noexcept
	{
		return m_uInstanceCount;
	}
	inline const uint32_t& Mesh::GetFirstInstance() const noexcept
	{
		return m_uFirstInstance;
	}
	inline const EDrawMode Mesh::GetDrawMode() const noexcept
	{
		return m_kDrawMode;
	}
	inline const EIndexType Mesh::GetIndexType() const noexcept
	{
		return m_kIndexType;
	}
} // Tracy

#endif // !TRACY_MESH_H
