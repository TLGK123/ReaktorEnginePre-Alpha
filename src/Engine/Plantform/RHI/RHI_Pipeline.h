
#pragma once

//= INCLUDES =================
#include "RHI_Definition.h"
#include "RHI_Viewport.h"
#include "RHI_Shader.h"
#include <memory>
#include <map>
#include "../Math/Rectangle.h"
//============================

namespace TmingEngine
{
	class RHI_Pipeline
	{
	public:
		RHI_Pipeline(const std::shared_ptr<RHI_Device>& rhi_device);
		~RHI_Pipeline();
	
		bool Create();
		void UpdateDescriptorSets(RHI_Texture* texture = nullptr);
		void OnCommandListConsumed();

		auto GetPipeline() const			{ return m_graphics_pipeline; }
		auto GetPipelineLayout() const		{ return m_pipeline_layout; }
		auto GetRenderPass() const			{ return m_render_pass; }
		auto GetDescriptorSet(uint32_t id) 	{ return m_descriptor_set_cache.count(id) ? m_descriptor_set_cache[id] : nullptr; }
		auto GetDescriptorSet()				{ return m_descriptor_set_cache.size() ? m_descriptor_set_cache.begin()->second : nullptr; }
	
		std::shared_ptr<RHI_Shader> m_shader_vertex;
		std::shared_ptr<RHI_Shader> m_shader_pixel;
		std::shared_ptr<RHI_InputLayout> m_input_layout;	
		std::shared_ptr<RHI_RasterizerState> m_rasterizer_state;
		std::shared_ptr<RHI_BlendState> m_blend_state;
		std::shared_ptr<RHI_DepthStencilState> m_depth_stencil_state;
		RHI_Viewport m_viewport;
		Math::Rectangle m_scissor;
		RHI_PrimitiveTopology_Mode m_primitive_topology = PrimitiveTopology_NotAssigned;
		RHI_Sampler* m_sampler							= nullptr;
		RHI_ConstantBuffer* m_constant_buffer			= nullptr;
		RHI_VertexBuffer* m_vertex_buffer				= nullptr;

	private:
		bool CreateDescriptorPool();
		bool CreateDescriptorSetLayout();
		void ReflectShaders();

		void* m_graphics_pipeline		= nullptr;
		void* m_pipeline_layout			= nullptr;
		void* m_render_pass				= nullptr;
		void* m_descriptor_pool			= nullptr;
		void* m_descriptor_set_layout	= nullptr;
		uint32_t m_desctiptor_set_capacity = 0;
		std::map<uint32_t, void*> m_descriptor_set_cache;
		std::map<std::string, Shader_Resource> m_shader_resources;

		std::shared_ptr<RHI_Device> m_rhi_device;
	};
}
