
//= IMPLEMENTATION ===============
#include "../RHI_Implementation.h"
#ifdef API_GRAPHICS_D3D11
//================================

//= INCLUDES =====================
#include "../RHI_Sampler.h"
#include "../RHI_Device.h"
#include "../../Logging/Log.h"
#include "../../Core/Settings.h"
//================================

namespace TmingEngine
{
	RHI_Sampler::RHI_Sampler(
		const std::shared_ptr<RHI_Device>& rhi_device,
		const RHI_Texture_Filter filter						/*= Texture_Sampler_Anisotropic*/,
		const RHI_Sampler_Address_Mode sampler_address_mode	/*= Texture_Address_Wrap*/,
		const RHI_Comparison_Function comparison_function	/*= Texture_Comparison_Always*/
	)
	{	
		m_buffer_view				= nullptr;
		m_rhi_device			= rhi_device;
		m_filter				= filter;
		m_sampler_address_mode	= sampler_address_mode;
		m_comparison_function	= comparison_function;

		if (!rhi_device || !m_rhi_device->GetContext()->device)
		{
			LOG_ERROR_INVALID_PARAMETER();
			return;
		}
		
		D3D11_SAMPLER_DESC sampler_desc;
		sampler_desc.Filter			= d3d11_filter[filter];
		sampler_desc.AddressU		= d3d11_sampler_address_mode[sampler_address_mode];
		sampler_desc.AddressV		= d3d11_sampler_address_mode[sampler_address_mode];
		sampler_desc.AddressW		= d3d11_sampler_address_mode[sampler_address_mode];
		sampler_desc.MipLODBias		= 0.0f;
		sampler_desc.MaxAnisotropy	= Settings::Get().GetAnisotropy();
		sampler_desc.ComparisonFunc	= d3d11_compare_operator[comparison_function];
		sampler_desc.BorderColor[0]	= 0;
		sampler_desc.BorderColor[1]	= 0;
		sampler_desc.BorderColor[2]	= 0;
		sampler_desc.BorderColor[3]	= 0;
		sampler_desc.MinLOD			= FLT_MIN;
		sampler_desc.MaxLOD			= FLT_MAX;
	
		// Create sampler state.
		if (FAILED(m_rhi_device->GetContext()->device->CreateSamplerState(&sampler_desc, reinterpret_cast<ID3D11SamplerState**>(&m_buffer_view))))
		{
			LOG_ERROR("Failed to create sampler state");
		}
	}

	RHI_Sampler::~RHI_Sampler()
	{
		safe_release(static_cast<ID3D11SamplerState*>(m_buffer_view));
		m_buffer_view = nullptr;
	}
}
#endif
