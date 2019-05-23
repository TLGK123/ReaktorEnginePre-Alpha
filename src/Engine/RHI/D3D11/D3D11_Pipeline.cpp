

#pragma once

//= IMPLEMENTATION ===============
#include "../RHI_Implementation.h"
#ifdef API_GRAPHICS_D3D11
//================================

//= INCLUDES ===============
#include "../RHI_Pipeline.h"
//==========================

//= NAMESPACES =====
using namespace std;
//==================

namespace TmingEngine
{
	RHI_Pipeline::RHI_Pipeline(const shared_ptr<RHI_Device>& rhi_device)
	{
		m_rhi_device = rhi_device;
	}

	RHI_Pipeline::~RHI_Pipeline()
	{

	}

	bool RHI_Pipeline::Create()
	{
		return true;
	}

	void RHI_Pipeline::UpdateDescriptorSets(RHI_Texture* texture /*= nullptr*/)
	{

	}
}
#endif
