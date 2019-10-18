

#pragma once

//= INCLUDES ============
#include "RHI_Texture.h"
#include "RHI_Viewport.h"
//=======================

namespace TmingEngine
{
	class ENGINE_CLASS RHI_Texture2D : public RHI_Texture
	{
	public:
		// Creates an empty texture intended for deferred loading
		RHI_Texture2D(Context* context, bool generate_mipmaps = true) : RHI_Texture(context) 
		{ 
			m_resource_type = Resource_Texture2d;
			m_has_mipmaps	= generate_mipmaps; 
		}

		// Creates a texture with mimaps. If only the first mipmap is available, the rest will automatically generated
		RHI_Texture2D(Context* context, unsigned int width, unsigned int height, RHI_Format format, const std::vector<std::vector<std::byte>>& data) : RHI_Texture(context)
		{
			m_resource_type = Resource_Texture2d;
			m_width			= width;
			m_height		= height;
			m_viewport		= RHI_Viewport(0, 0, static_cast<float>(width), static_cast<float>(height));
			m_channels		= GetChannelCountFromFormat(format);
			m_format		= format;		
			m_has_mipmaps	= true;
			m_data			= data;

			CreateResourceGpu();
		}

		// Creates a texture without any mipmaps
		RHI_Texture2D(Context* context, unsigned int width, unsigned int height, RHI_Format format, const std::vector<std::byte>& data) : RHI_Texture(context)
		{
			m_resource_type = Resource_Texture2d;
			m_width			= width;
			m_height		= height;
			m_viewport		= RHI_Viewport(0, 0, static_cast<float>(width), static_cast<float>(height));
			m_channels		= GetChannelCountFromFormat(format);
			m_format		= format;
			m_has_mipmaps	= false;
			m_data.emplace_back(data);

			CreateResourceGpu();
		}

		// Creates a texture without any data, intended for usage as a render target
		RHI_Texture2D(Context* context, unsigned int width, unsigned int height, RHI_Format format, unsigned int array_size = 1) : RHI_Texture(context)
		{
			m_resource_type		= Resource_Texture2d;
			m_width				= width;
			m_height			= height;
			m_channels			= GetChannelCountFromFormat(format);
			m_viewport			= RHI_Viewport(0, 0, static_cast<float>(width), static_cast<float>(height));
			m_format			= format;
			m_array_size		= array_size;
			m_is_render_texture = true;

			CreateResourceGpu();
		}

		~RHI_Texture2D();

		// RHI_Texture
		bool CreateResourceGpu() override;

	private:
		bool m_is_render_texture = false;
	};
}
