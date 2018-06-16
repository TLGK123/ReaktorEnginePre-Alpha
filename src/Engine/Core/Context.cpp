#pragma once

//= INCLUDES =======
#include "Context.h"
//==================

namespace TmingEngine
{
	Context::Context()
	{

	}

	Context::~Context()
	{
		for (auto i = m_subsystems.size() - 1; i > 0; i--)
			delete m_subsystems[i];

		// Index 0 is the actual Engine instance, which is the instance
		// that called this deconstructor in the first place. A deletion
		// will result in a crash.
	}

	void Context::RegisterSubsystem(Subsystem* subsystem)
	{
		if (!subsystem)
			return;

		m_subsystems.push_back(subsystem);
	}
}