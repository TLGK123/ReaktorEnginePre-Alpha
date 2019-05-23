#pragma once

//= INCLUDES ==================
#include <memory>
#include "RHI_Object.h"
#include "RHI_Definition.h"
#include "../Core/EngineDefs.h"
//=============================

namespace TmingEngine
{
	class ENGINE_CLASS RHI_ConstantBuffer : public RHI_Object
	{
	public:
		RHI_ConstantBuffer(const std::shared_ptr<RHI_Device>& rhi_device)
		{
			m_rhi_device = rhi_device;
		}
		~RHI_ConstantBuffer();

		template<typename T>
		bool Create()
		{
			m_size = static_cast<unsigned int>(sizeof(T));
			return _Create();
		}

		void* Map() const;
		bool Unmap() const;
		auto GetResource() const	{ return m_buffer; }
		auto GetSize()	const		{ return m_size; }

	private:
		bool _Create();

		std::shared_ptr<RHI_Device> m_rhi_device;

		// API
		void* m_buffer			= nullptr;
		void* m_buffer_memory	= nullptr;
	};
}
