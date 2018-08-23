#pragma once
#include "EngineDefs.h"
#include "SmartPtr.h"
#include "Context.h"

namespace TmingEngine
{
    class ENGINE_CLASS Subsystem
	{
		friend class Context;
	public:
		Subsystem(Context* context)
		{
			m_context = context;
		}
		virtual ~Subsystem() {}

		virtual bool Initialize() { return true; }

	protected:
		Context * m_context;
	};
}
