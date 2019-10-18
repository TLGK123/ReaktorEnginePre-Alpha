
#pragma once

//= INCLUDES ==============
#include "RHI_Definition.h"
#include "RHI_Object.h"
#include <memory>
//=========================

namespace TmingEngine
{
	class RHI_Sampler : public RHI_Object
	{
	public:
		RHI_Sampler(
			const std::shared_ptr<RHI_Device>& rhi_device,
			RHI_Texture_Filter filter						= Texture_Filter_Anisotropic,
			RHI_Sampler_Address_Mode sampler_address_mode	= Sampler_Address_Wrap,
			RHI_Comparison_Function comparison_function		= Comparison_Always);
		~RHI_Sampler();

		RHI_Texture_Filter GetFilter() const					{ return m_filter; }
		RHI_Sampler_Address_Mode GetAddressMode() const			{ return m_sampler_address_mode; }
		RHI_Comparison_Function GetComparisonFunction() const	{ return m_comparison_function; }
		void* GetResource() const								{ return m_buffer_view; }

	private:	
		RHI_Texture_Filter m_filter;
		RHI_Sampler_Address_Mode m_sampler_address_mode;
		RHI_Comparison_Function m_comparison_function;
		std::shared_ptr<RHI_Device> m_rhi_device;

		// API
		void* m_buffer_view = nullptr;
	};
}
