
#pragma once

//= INCLUDES ==============
#include "RHI_Definition.h"
#include "RHI_Object.h"
#include <memory>
#include <vector>
//=========================

namespace TmingEngine
{
	namespace Math { class Vector4; }

	class RHI_SwapChain : public RHI_Object
	{
	public:
		RHI_SwapChain(
			void* window_handle,
			const std::shared_ptr<RHI_Device>& rhi_device,
			unsigned int width,
			unsigned int height,
			RHI_Format format				= Format_R8G8B8A8_UNORM,
			RHI_Present_Mode present_mode	= Present_Immediate,
			unsigned int buffer_count		= 1,		
			void* render_pass				= nullptr
		);
		~RHI_SwapChain();

		bool Resize(unsigned int width, unsigned int height);
		bool AcquireNextImage();
		bool Present(void* semaphore_render_finished);

		auto GetWidth()								{ return m_width; }
		auto GetHeight()							{ return m_height; }
		auto IsInitialized()						{ return m_initialized; }
		auto GetSwapChainView()						{ return m_swap_chain_view; }
		auto GetRenderTargetView()					{ return m_render_target_view; }
		auto GetBufferCount()						{ return m_buffer_count; }
		auto& GetFrameBuffer(unsigned int index)	{ return m_frame_buffers[index]; }
		auto& GetSemaphoreImageAcquired()			{ return m_semaphores_image_acquired[m_image_index]; }
		auto& GetImageIndex()						{ return m_image_index; }

	private:
		bool m_initialized				= false;
		bool m_windowed					= false;
		unsigned int m_buffer_count		= 0;		
		unsigned int m_max_resolution	= 16384;
		unsigned int m_width			= 0;
		unsigned int m_height			= 0;
		unsigned int m_flags			= 0;
		RHI_Format m_format;
		RHI_Present_Mode m_present_mode;
		std::shared_ptr<RHI_Device> m_rhi_device;

		// API
		void* m_swap_chain_view				= nullptr;
		void* m_render_target_view			= nullptr;
		void* m_surface						= nullptr;	
		void* m_render_pass					= nullptr;
		void* m_window_handle				= nullptr;
		uint32_t m_image_index				= 0;
		std::vector<void*> m_semaphores_image_acquired;
		std::vector<void*> m_image_views;
		std::vector<void*> m_frame_buffers;
		bool m_first_run = true;
	};
}
