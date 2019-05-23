
#pragma once

//= INCLUDES ================
#include "RHI_Object.h"
#include "RHI_Definition.h"
#include <memory>
#include "../Core/Settings.h"
//===========================

namespace TmingEngine
{
	class ENGINE_CLASS RHI_DepthStencilState : public RHI_Object
	{
	public:
		RHI_DepthStencilState(
			const std::shared_ptr<RHI_Device>& rhi_device,
			const bool depth_enabled,
			const RHI_Comparison_Function comparison = Settings::Get().GetReverseZ() ? Comparison_GreaterEqual : Comparison_LessEqual
		);
		~RHI_DepthStencilState();

		bool GetDepthEnabled() const	{ return m_depth_enabled; }
		void* GetBuffer() const			{ return m_buffer; }

	private:
		bool m_depth_enabled	= false;
		bool m_initialized		= false;
		void* m_buffer			= nullptr;
	};
}
