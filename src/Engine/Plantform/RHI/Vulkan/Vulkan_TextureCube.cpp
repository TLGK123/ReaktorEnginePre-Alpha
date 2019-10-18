

//= IMPLEMENTATION ===============
#include "../RHI_Implementation.h"
#ifdef API_GRAPHICS_VULKAN
//================================

//= INCLUDES =====================
#include "../RHI_TextureCube.h"
#include "../../Math/MathHelper.h"
//================================

//= NAMESPAECES ====
using namespace std;
//==================

namespace TmingEngine
{
	RHI_TextureCube::~RHI_TextureCube()
	{
		m_data.clear();
		Vulkan_Common::image_view::destroy(m_rhi_device, m_resource_texture);
		Vulkan_Common::image::destroy(m_rhi_device, m_texture);
		Vulkan_Common::memory::free(m_rhi_device, m_texture_memory);
	}

	bool RHI_TextureCube::CreateResourceGpu()
	{
		return true;
	}
}
#endif
