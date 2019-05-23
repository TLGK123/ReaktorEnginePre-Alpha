
//= IMPLEMENTATION ===============
#include "../RHI_Implementation.h"
#ifdef API_GRAPHICS_D3D11
//================================

//= INCLUDES ======================
#include "../RHI_RasterizerState.h"
#include "../RHI_Device.h"
#include "../../Logging/Log.h"
//=================================

//= NAMESPACES =====
using namespace std;
//==================

namespace TmingEngine
{
	RHI_RasterizerState::RHI_RasterizerState
	(
		const shared_ptr<RHI_Device>& rhi_device,
		const RHI_Cull_Mode cull_mode,
		const RHI_Fill_Mode fill_mode,
		const bool depth_clip_enabled,
		const bool scissor_enabled,
		const bool multi_sample_enabled,
		const bool antialised_line_enabled)
	{
		if (!rhi_device)
		{
			LOG_ERROR_INVALID_INTERNALS();
			return;
		}

		if (!rhi_device->GetContext()->device)
		{
			LOG_ERROR_INVALID_INTERNALS();
			return;
		}

		// Save properties
		m_cull_mode					= cull_mode;
		m_fill_mode					= fill_mode;
		m_depth_clip_enabled		= depth_clip_enabled;
		m_scissor_enabled			= scissor_enabled;
		m_multi_sample_enabled		= multi_sample_enabled;
		m_antialised_line_enabled	= antialised_line_enabled;

		// Create rasterizer description
		D3D11_RASTERIZER_DESC desc;
		desc.CullMode				= d3d11_cull_mode[cull_mode];
		desc.FillMode				= d3d11_polygon_mode[fill_mode];	
		desc.FrontCounterClockwise	= false;
		desc.DepthBias				= 0;
		desc.DepthBiasClamp			= 0.0f;
		desc.SlopeScaledDepthBias	= 0.0f;
		desc.DepthClipEnable		= depth_clip_enabled;	
		desc.MultisampleEnable		= multi_sample_enabled;
		desc.AntialiasedLineEnable	= antialised_line_enabled;
		desc.ScissorEnable			= scissor_enabled;

		// Create rasterizer state
		auto rasterizer_state	= static_cast<ID3D11RasterizerState*>(m_buffer);
		const auto result		= rhi_device->GetContext()->device->CreateRasterizerState(&desc, &rasterizer_state);
	
		// Handle result
		if (SUCCEEDED(result))
		{
			m_buffer		= static_cast<void*>(rasterizer_state);
			m_initialized	= true;
		}
		else
		{
			LOGF_ERROR("Failed to create the rasterizer state, %s.", D3D11_Common::dxgi_error_to_string(result));
			m_initialized = false;
		}
	}

	RHI_RasterizerState::~RHI_RasterizerState()
	{
		safe_release(static_cast<ID3D11RasterizerState*>(m_buffer));
	}
}
#endif
