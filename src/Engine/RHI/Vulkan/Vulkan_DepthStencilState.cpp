
//= IMPLEMENTATION ===============
#include "../RHI_Implementation.h"
#ifdef API_GRAPHICS_VULKAN
//================================

//= INCLUDES ========================
#include "../RHI_DepthStencilState.h"
#include "../RHI_Device.h"
//===================================

//= NAMESPACES =====
using namespace std;
//==================

namespace Spartan
{
	RHI_DepthStencilState::RHI_DepthStencilState(const shared_ptr<RHI_Device>& rhi_device, const bool depth_enabled, const RHI_Comparison_Function comparison)
	{
		VkPipelineDepthStencilStateCreateInfo depth_stencil_state{};
		depth_stencil_state.sType				= VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depth_stencil_state.depthTestEnable		= depth_enabled;
		depth_stencil_state.depthWriteEnable	= depth_enabled;
		depth_stencil_state.depthCompareOp		= vulkan_compare_operator[comparison];
		depth_stencil_state.front				= depth_stencil_state.back;
		depth_stencil_state.back.compareOp		= VK_COMPARE_OP_ALWAYS;
	}

	RHI_DepthStencilState::~RHI_DepthStencilState()
	{
		
	}
}
#endif
