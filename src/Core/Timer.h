#pragma once
#include "SubSystem.h"
#include <chrono>
//====================

namespace TmingEngine
{
	class ENGINE_CLASS Timer : public Subsystem
	{
	public:
		Timer(Context* context);
		~Timer();

		void Tick();
		float GetDeltaTimeMs() { return m_deltaTimeMs; }
		float GetDeltaTimeSec() { return m_deltaTimeSec; }

	private:
		float m_deltaTimeMs;
		float m_deltaTimeSec;

		std::chrono::high_resolution_clock::time_point m_previousTime;
	};
}