#pragma once
#include "SubSystem.h"
#include <vector>
//====================

namespace TmingEngine
{
	class ENGINE_CLASS Context
	{
	public:
		Context();
		~Context();

		// Register a subsystem
		void RegisterSubsystem(Subsystem* subsystem);

		// Get a subsystem
		template <class T> T* GetSubsystem();
	private:
		std::vector<Subsystem*> m_subsystems;
	};

	template <class T>
	T* Context::GetSubsystem()
	{
		for (const auto& subsystem : m_subsystems)
		{
			if (typeid(T) == typeid(*subsystem))
				return static_cast<T*>(subsystem);
		}

		return nullptr;
	}
}
