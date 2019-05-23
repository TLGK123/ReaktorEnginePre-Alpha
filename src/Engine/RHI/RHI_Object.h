#pragma once

//= INCLUDES =====================
#include "../Core/EngineDefs.h"
#include "../Core/GUIDGenerator.h"
//================================

namespace TmingEngine
{
	class ENGINE_CLASS RHI_Object
	{
	public:
		RHI_Object()					{ m_id = GENERATE_GUID; }
		unsigned int RHI_GetID() const	{ return m_id; }

	protected:
		uint64_t m_size = 0;

	private:
		unsigned int m_id = 0;	
	};
}
