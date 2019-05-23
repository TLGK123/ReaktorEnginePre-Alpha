
//= IMPLEMENTATION ===============
#include "../RHI_Implementation.h"
#ifdef API_GRAPHICS_VULKAN
//================================

//= INCLUDES =================
#include "../RHI_BlendState.h"
#include "../RHI_Device.h"
//============================

//= NAMESPACES =====
using namespace std;
//==================

namespace TmingEngine
{
	RHI_BlendState::RHI_BlendState
	(
		const std::shared_ptr<RHI_Device>& device,
		const bool blend_enabled					/*= false*/,
		const RHI_Blend source_blend				/*= Blend_Src_Alpha*/,
		const RHI_Blend dest_blend					/*= Blend_Inv_Src_Alpha*/,
		const RHI_Blend_Operation blend_op			/*= Blend_Operation_Add*/,
		const RHI_Blend source_blend_alpha			/*= Blend_One*/,
		const RHI_Blend dest_blend_alpha			/*= Blend_One*/,
		const RHI_Blend_Operation blend_op_alpha	/*= Blend_Operation_Add*/
	)
	{
		// Save parameters
		m_blend_enabled			= blend_enabled;
		m_source_blend			= source_blend;
		m_dest_blend			= dest_blend;
		m_blend_op				= blend_op;
		m_source_blend_alpha	= source_blend_alpha;
		m_dest_blend_alpha		= dest_blend_alpha;
		m_blend_op_alpha		= blend_op_alpha;
	}

	RHI_BlendState::~RHI_BlendState()
	{
		
	}
}
#endif
