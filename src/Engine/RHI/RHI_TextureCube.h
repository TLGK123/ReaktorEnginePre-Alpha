
#pragma once

//= INCLUDES ===========
#include "RHI_Texture.h"
//======================

namespace TmingEngine
{
	class SPARTAN_CLASS RHI_TextureCube : public RHI_Texture
	{
	public:
		RHI_TextureCube(Context* context) : RHI_Texture(context) { m_resource_type = Resource_TextureCube; }

		// Creates a cubemap. 6 textures containing mip-levels have to be provided
		RHI_TextureCube(Context* context, unsigned int width, unsigned int height, RHI_Format format, const std::vector<std::vector<std::vector<std::byte>>>& data) : RHI_Texture(context)
		{
			m_width			= width;
			m_height		= height;
			m_viewport		= RHI_Viewport(0, 0, static_cast<float>(width), static_cast<float>(height));
			m_channels		= GetChannelCountFromFormat(format);
			m_format		= format;
			m_has_mipmaps	= true;
			m_data_cube		= data;
			m_array_size	= 6;

			CreateResourceGpu();
		}

		// Creates a cubemap, to be used as a render target
		RHI_TextureCube(Context* context, unsigned int width, unsigned int height, RHI_Format format) : RHI_Texture(context)
		{
			m_width			= width;
			m_height		= height;
			m_channels		= GetChannelCountFromFormat(format);
			m_viewport		= RHI_Viewport(0, 0, static_cast<float>(width), static_cast<float>(height));
			m_format		= format;
			m_has_mipmaps	= true;
			m_array_size	= 6;

			CreateResourceGpu();
		}

		~RHI_TextureCube();

		// RHI_Texture
		bool CreateResourceGpu() override;

	private:
		std::vector<std::vector<std::vector<std::byte>>> m_data_cube;
	};
}
