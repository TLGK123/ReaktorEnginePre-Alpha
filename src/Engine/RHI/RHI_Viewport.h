

#pragma once

//= INCLUDES ==================
#include "../Core/EngineDefs.h"
#include "RHI_Object.h"
//=============================

namespace TmingEngine
{
	class SPARTAN_CLASS RHI_Viewport : public RHI_Object
	{
	public:
		RHI_Viewport(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f, float minDepth = 0.0f, float maxDepth = 1.0f)
		{
			m_x			= x;
			m_y			= y;
			m_width		= width;
			m_height	= height;
			m_minDepth	= minDepth;
			m_maxDepth	= maxDepth;
		}

		RHI_Viewport(const RHI_Viewport& viewport)
		{
			m_x			= viewport.GetX();
			m_y			= viewport.GetY();
			m_width		= viewport.GetWidth();
			m_height	= viewport.GetHeight();
			m_minDepth	= viewport.GetMinDepth();
			m_maxDepth	= viewport.GetMaxDepth();
		}

		~RHI_Viewport(){}

		bool operator==(const RHI_Viewport& rhs) const
		{
			return 
				m_x			== rhs.m_x			&& m_y			== rhs.m_y && 
				m_width		== rhs.m_width		&& m_height		== rhs.m_height && 
				m_minDepth	== rhs.m_minDepth	&& m_maxDepth	== rhs.m_maxDepth;
		}

		bool operator!=(const RHI_Viewport& rhs) const
		{
			return !(*this == rhs);
		}

		bool IsDefined() const			
		{
			return
				m_x			!= 0.0f && 
				m_y			!= 0.0f && 
				m_width		!= 0.0f && 
				m_height	!= 0.0f && 
				m_minDepth	!= 0.0f && 
				m_maxDepth	!= 0.0f;
		}

		const float& GetX()				const	{ return m_x; }
		const float& GetY()				const	{ return m_y; }
		const float& GetWidth()			const	{ return m_width; }
		const float& GetHeight()		const	{ return m_height; }
		const float& GetMinDepth()		const	{ return m_minDepth; }
		const float& GetMaxDepth()		const	{ return m_maxDepth; }
		float GetAspectRatio()			const	{ return m_width / m_height; }

		void SetPosX(float x)			{ m_x = x; }
		void SetPosY(float y)			{ m_y = y; }
		void SetWidth(float width)		{ m_width	= width; }
		void SetHeight(float height)	{ m_height	= height; }

	private:
		float m_x;
		float m_y;
		float m_width;
		float m_height;
		float m_minDepth;
		float m_maxDepth;
	};
}
