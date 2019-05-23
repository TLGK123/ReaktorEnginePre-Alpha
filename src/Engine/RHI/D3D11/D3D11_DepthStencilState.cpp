

//= IMPLEMENTATION ===============
#include "../RHI_Implementation.h"
#ifdef API_GRAPHICS_D3D11
//================================

//= INCLUDES ========================
#include "../RHI_DepthStencilState.h"
#include "../RHI_Device.h"
#include "../../Logging/Log.h"
//===================================

//= NAMESPACES =====
using namespace std;
//==================

namespace TmingEngine
{
	RHI_DepthStencilState::RHI_DepthStencilState(const shared_ptr<RHI_Device>& rhi_device, const bool depth_enabled, const RHI_Comparison_Function comparison)
	{
		if (!rhi_device)
		{
			LOG_ERROR_INVALID_INTERNALS();
			return;
		}

		auto d3d11_device = rhi_device->GetContext()->device;
		if (!d3d11_device)
		{
			LOG_ERROR_INVALID_INTERNALS();
			return;
		}

		// Save properties
		m_depth_enabled = depth_enabled;

		// Create description
		D3D11_DEPTH_STENCIL_DESC desc;

		if (!depth_enabled)
		{
			desc.DepthEnable					= false;
			desc.DepthWriteMask					= D3D11_DEPTH_WRITE_MASK_ALL;
			desc.DepthFunc						= d3d11_compare_operator[comparison];
			desc.StencilEnable					= false;
			desc.StencilReadMask				= D3D11_DEFAULT_STENCIL_READ_MASK;
			desc.StencilWriteMask				= D3D11_DEFAULT_STENCIL_WRITE_MASK;
			desc.FrontFace.StencilDepthFailOp	= D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilFailOp		= D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilPassOp		= D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;
			desc.BackFace						= desc.FrontFace;
		}
		else
		{
			desc.DepthEnable					= true;
			desc.DepthWriteMask					= D3D11_DEPTH_WRITE_MASK_ALL;
			desc.DepthFunc						= d3d11_compare_operator[comparison];
			desc.StencilEnable					= false;
			desc.StencilReadMask				= D3D11_DEFAULT_STENCIL_READ_MASK;
			desc.StencilWriteMask				= D3D11_DEFAULT_STENCIL_WRITE_MASK;
			desc.FrontFace.StencilDepthFailOp	= D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilFailOp		= D3D11_STENCIL_OP_KEEP;
			desc.FrontFace.StencilPassOp		= D3D11_STENCIL_OP_REPLACE;
			desc.FrontFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;
			desc.BackFace						= desc.FrontFace;
		
		}

		// Create depth-stencil state
		auto depth_stencil_state	= static_cast<ID3D11DepthStencilState*>(m_buffer);
		const auto result			= d3d11_device->CreateDepthStencilState(&desc, &depth_stencil_state);

		// Handle result
		if (SUCCEEDED(result))
		{
			m_buffer		= static_cast<void*>(depth_stencil_state);
			m_initialized	= true;
		}
		else
		{
			m_initialized = false;
			LOGF_ERROR("Failed to create depth-stencil state %s.", D3D11_Common::dxgi_error_to_string(result));
		}
	}

	RHI_DepthStencilState::~RHI_DepthStencilState()
	{
		safe_release(static_cast<ID3D11DepthStencilState*>(m_buffer));
	}
}
#endif
