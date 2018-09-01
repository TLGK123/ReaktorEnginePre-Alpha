#pragma once

#ifndef  Subsystem_h
#define Subsystem_h
#include "EngineDefs.h"
#include "SmartPtr.h"

namespace TmingEngine
{
    class Context;
	class ENGINE_CLASS Subsystem
	{
		
	public:
		Subsystem(Context * context)
		{
			m_context = context;
		}
		virtual ~Subsystem() {}

		virtual bool Initialize() { return true; }

	protected:
		Context * m_context;
	};
}

#endif
