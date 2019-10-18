
//= IMPLEMENTATION ===============
#include "../RHI_Implementation.h"
#ifdef API_GRAPHICS_VULKAN
//================================

//= INCLUDES ======================
#include "../RHI_RasterizerState.h"
#include "../RHI_Device.h"
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
		m_cull_mode					= cull_mode;
		m_fill_mode					= fill_mode;
		m_depth_clip_enabled		= depth_clip_enabled;
		m_scissor_enabled			= scissor_enabled;
		m_multi_sample_enabled		= multi_sample_enabled;
		m_antialised_line_enabled	= antialised_line_enabled;
	}

	RHI_RasterizerState::~RHI_RasterizerState()
	{
		
	}
}
#endif
