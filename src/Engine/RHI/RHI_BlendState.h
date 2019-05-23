#pragma once

//= INCLUDES ==============
#include "RHI_Object.h"
#include "RHI_Definition.h"
//=========================

namespace TmingEngine
{
	class ENGINE_CLASS RHI_BlendState : public RHI_Object
	{
	public:
		RHI_BlendState(const std::shared_ptr<RHI_Device>& device,
			bool blend_enabled					= false,
			RHI_Blend source_blend				= Blend_Src_Alpha,
			RHI_Blend dest_blend				= Blend_Inv_Src_Alpha,
			RHI_Blend_Operation blend_op		= Blend_Operation_Add,
			RHI_Blend source_blend_alpha		= Blend_One,
			RHI_Blend dest_blend_alpha			= Blend_One,
			RHI_Blend_Operation blend_op_alpha	= Blend_Operation_Add
		);
		~RHI_BlendState();

		bool GetBlendEnabled() const				{ return m_blend_enabled; }
		RHI_Blend GetSourceBlend() const			{ return m_source_blend; }
		RHI_Blend GetDestBlend() const				{ return m_dest_blend; }
		RHI_Blend_Operation GetBlendOp() const		{ return m_blend_op; }
		RHI_Blend GetSourceBlendAlpha() const		{ return m_source_blend_alpha; }
		RHI_Blend GetDestBlendAlpha() const			{ return m_dest_blend_alpha; }
		RHI_Blend_Operation GetBlendOpAlpha() const { return m_blend_op_alpha; }

		void* GetBuffer() const	{ return m_buffer; }

	private:
		bool m_blend_enabled					= false;
		RHI_Blend m_source_blend				= Blend_Src_Alpha;
		RHI_Blend m_dest_blend					= Blend_Inv_Src_Alpha;
		RHI_Blend_Operation m_blend_op			= Blend_Operation_Add;
		RHI_Blend m_source_blend_alpha			= Blend_One;
		RHI_Blend m_dest_blend_alpha			= Blend_One;
		RHI_Blend_Operation m_blend_op_alpha	= Blend_Operation_Add;
	
		void* m_buffer		= nullptr;
		bool m_initialized	= false;
	};
}
