#include "Timer.h"

using namespace std;
using namespace chrono;

namespace TmingEngine
{
	Timer::Timer(Context* context) : Subsystem(context)
	{
		m_deltaTimeSec = 0.0f;
		m_deltaTimeMs = 0.0f;
	}

	Timer::~Timer()
	{
	}

	void Timer::Tick()
	{
//		auto currentTime = high_resolution_clock::now();
//		duration<double, milli> ms = currentTime - m_previousTime;
//		m_previousTime = currentTime;
//
//		m_deltaTimeMs = (float)ms.count();
//		m_deltaTimeSec = (float)(ms.count() / 1000);
	}
}
