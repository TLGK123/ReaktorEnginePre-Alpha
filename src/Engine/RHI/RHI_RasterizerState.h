
#pragma once

//= INCLUDES ==============
#include <memory>
#include "RHI_Object.h"
#include "RHI_Definition.h"
//=========================

namespace TmingEngine
{
	class ENGINE_CLASS RHI_RasterizerState : public RHI_Object
	{
	public:
		RHI_RasterizerState(
			const std::shared_ptr<RHI_Device>& rhi_device,
			RHI_Cull_Mode cull_mode,
			RHI_Fill_Mode fill_mode,
			bool depth_clip_enabled,
			bool scissor_enabled,
			bool multi_sample_enabled, 
			bool antialised_line_enabled
		);
		~RHI_RasterizerState();

		RHI_Cull_Mode GetCullMode() const		{ return m_cull_mode; }
		RHI_Fill_Mode GetFillMode() const		{ return m_fill_mode; }
		bool GetDepthClipEnabled() const		{ return m_depth_clip_enabled; }
		bool GetScissorEnabled() const			{ return m_scissor_enabled; }
		bool GetMultiSampleEnabled() const		{ return m_multi_sample_enabled; }
		bool GetAntialisedLineEnabled() const	{ return m_antialised_line_enabled; }
		bool IsInitialized() const				{ return m_initialized; }
		void* GetBuffer() const					{ return m_buffer; }

	private:
		// Properties
		RHI_Cull_Mode m_cull_mode;
		RHI_Fill_Mode m_fill_mode;
		bool m_depth_clip_enabled;
		bool m_scissor_enabled;
		bool m_multi_sample_enabled;
		bool m_antialised_line_enabled;

		// Initialized
		bool m_initialized = false;

		// Rasterizer state view
		void* m_buffer = nullptr;
	};
}
