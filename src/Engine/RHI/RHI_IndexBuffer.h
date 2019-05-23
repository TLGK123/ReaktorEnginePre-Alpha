#pragma once

//= INCLUDES ==============
#include "RHI_Definition.h"
#include "RHI_Object.h"
#include <vector>
//=========================

namespace TmingEngine
{
	class RHI_IndexBuffer : public RHI_Object
	{
	public:
		RHI_IndexBuffer(const std::shared_ptr<RHI_Device>& rhi_device)
		{
			m_rhi_device = rhi_device;
		}

		~RHI_IndexBuffer();
	
		template<typename T>
		bool Create(const std::vector<T>& indices)
		{
			m_is_dynamic	= false;
			m_stride		= sizeof(T);
			m_index_count	= static_cast<unsigned int>(indices.size());
			m_size			= m_stride * m_index_count;
			return Create(indices.data());
		}

		template<typename T>
		bool CreateDynamic(unsigned int index_count)
		{
			m_is_dynamic	= true;
			m_stride		= sizeof(T);
			m_index_count	= index_count;
			m_size			= m_stride * m_index_count;
			return Create(nullptr);
		}

		void* Map() const;
		bool Unmap() const;

		auto GetResource()		const { return m_buffer; }
		auto GetSize()			const { return m_size; }
		auto GetIndexCount()	const { return m_index_count; }
		auto Is16Bit()			const { return sizeof(uint16_t) == m_stride; }
		auto Is32Bit()			const { return sizeof(uint32_t) == m_stride; }

	protected:
		bool Create(const void* indices);

		bool m_is_dynamic			= false;
		unsigned int m_stride		= 0;
		unsigned int m_index_count	= 0;
		std::shared_ptr<RHI_Device> m_rhi_device;

		void* m_buffer			= nullptr;
		void* m_buffer_memory	= nullptr;		
	};
}
