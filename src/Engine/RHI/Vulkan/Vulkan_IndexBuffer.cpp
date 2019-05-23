

//= IMPLEMENTATION ===============
#include "../RHI_Implementation.h"
#ifdef API_GRAPHICS_VULKAN
//================================

//= INCLUDES ==================
#include "../RHI_Device.h"
#include "../RHI_IndexBuffer.h"
#include "../../Logging/Log.h"
//=============================

//= NAMESPACES =====
using namespace std;
//==================

namespace TmingEngine
{
	RHI_IndexBuffer::~RHI_IndexBuffer()
	{
		Vulkan_Common::buffer::destroy(m_rhi_device, m_buffer);
		Vulkan_Common::memory::free(m_rhi_device, m_buffer_memory);
	}

	bool RHI_IndexBuffer::Create(const void* indices)
	{
		if (!m_rhi_device || !m_rhi_device->GetContext()->device)
		{
			LOG_ERROR_INVALID_INTERNALS();
			return false;
		}

		// Clear previous buffer
		Vulkan_Common::buffer::destroy(m_rhi_device, m_buffer);
		Vulkan_Common::memory::free(m_rhi_device, m_buffer_memory);

		// Create buffer
		VkBuffer buffer					= nullptr;
		VkDeviceMemory buffer_memory	= nullptr;
		if (!Vulkan_Common::buffer::create(m_rhi_device, buffer, buffer_memory, m_size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT))
		{
			LOG_ERROR("Failed to create buffer");
			return false;
		}

		// Save
		m_buffer		= static_cast<void*>(buffer);
		m_buffer_memory = static_cast<void*>(buffer_memory);

		return true;
	}

	void* RHI_IndexBuffer::Map() const
	{
		if (!m_rhi_device || !m_rhi_device->GetContext()->device || !m_buffer_memory)
		{
			LOG_ERROR_INVALID_INTERNALS();
			return nullptr;
		}

		void* ptr	= nullptr;
		auto result = vkMapMemory(m_rhi_device->GetContext()->device, static_cast<VkDeviceMemory>(m_buffer_memory), 0, m_size, 0, reinterpret_cast<void**>(&ptr));
		if (result != VK_SUCCESS)
		{
			LOGF_ERROR("Failed to map memory, %s.", Vulkan_Common::result_to_string(result));
			return nullptr;
		}

		return ptr;
	}

	bool RHI_IndexBuffer::Unmap() const
	{
		if (!m_buffer_memory)
		{
			LOG_ERROR_INVALID_INTERNALS();
			return false;
		}

		vkUnmapMemory(m_rhi_device->GetContext()->device, static_cast<VkDeviceMemory>(m_buffer_memory));
		return true;
	}
}
#endif
