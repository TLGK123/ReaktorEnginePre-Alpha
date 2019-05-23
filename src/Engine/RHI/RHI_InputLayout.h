#pragma once

//= INCLUDES ==================
#include <memory>
#include <vector>
#include "RHI_Definition.h"
#include "../Core/EngineDefs.h"
//=============================

namespace TmingEngine
{
	struct VertexInputAttributeDescription 
	{
		VertexInputAttributeDescription(uint32_t location, uint32_t binding, RHI_Format format, uint32_t offset)
		{
			this->location		= location;
			this->binding		= binding;
			this->format		= format;
			this->offset		= offset;
		}

		uint32_t location;
		uint32_t binding;
		RHI_Format format;
		uint32_t offset;
	};

	class ENGINE_CLASS RHI_InputLayout
	{
	public:
		RHI_InputLayout(const std::shared_ptr<RHI_Device>& rhi_device);
		~RHI_InputLayout();

		bool Create(void* vertex_shader_blob, RHI_Vertex_Attribute_Type vertex_attributes);
		auto GetVertexAttributes() const		{ return m_vertex_attributes; }
		const auto& GetAttributeDescriptions()	{ return m_attribute_descs; }
		auto GetResource() const				{ return m_resource; }

	private:		
		RHI_Vertex_Attribute_Type m_vertex_attributes = Vertex_Attribute_None;

		// API
		void* m_resource = nullptr;
		std::shared_ptr<RHI_Device> m_rhi_device;
		std::vector<VertexInputAttributeDescription> m_attribute_descs;
	};
}
