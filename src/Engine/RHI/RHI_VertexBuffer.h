
#pragma once

//= INCLUDES ==============
#include "RHI_Definition.h"
#include "RHI_Object.h"
#include "RHI_Vertex.h"
#include <vector>
//=========================

namespace TmingEngine
{
	class RHI_VertexBuffer : public RHI_Object
	{
	public:
		RHI_VertexBuffer(const std::shared_ptr<RHI_Device>& rhi_device, uint32_t stride = 0) 
		{
			m_rhi_device	= rhi_device;
			m_stride		= stride;
		}

		~RHI_VertexBuffer();

		template<typename T>
		bool Create(const std::vector<T>& vector)
		{
			m_is_dynamic	= false;
			m_stride		= static_cast<uint32_t>(sizeof(T));
			m_vertex_count	= static_cast<uint32_t>(vector.size());
			m_size			= m_stride * m_vertex_count;
			return Create(static_cast<const void*>(vector.data()));
		}

		template<typename T>
		bool CreateDynamic(uint32_t vertex_count)
		{
			m_is_dynamic	= true;		
			m_stride		= static_cast<uint32_t>(sizeof(T));
			m_vertex_count	= vertex_count;
			m_size			= m_stride * vertex_count;
			return Create(nullptr);
		}

		void* Map() const;
		bool Unmap() const;

		auto GetResource()		const { return m_buffer; }
		auto& GetSize()			const { return m_size; }
		auto GetStride()		const { return m_stride; }
		auto GetVertexCount()	const { return m_vertex_count; }

	private:
		bool Create(const void* vertices);

		uint32_t m_stride			= 0;
		uint32_t m_vertex_count		= 0;
		bool m_is_dynamic			= false;	

		// API
		std::shared_ptr<RHI_Device> m_rhi_device;
		void* m_buffer			= nullptr;
		void* m_buffer_memory	= nullptr;
	};
}
