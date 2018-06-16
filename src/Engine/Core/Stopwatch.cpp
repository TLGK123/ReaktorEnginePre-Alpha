
//= INCLUDES =========
#include "Stopwatch.h"
//====================

//= NAMESPACES ========
using namespace std;
using namespace chrono;
//=====================

namespace TmingEngine
{
	Stopwatch::Stopwatch()
	{
		Start();
	}

	Stopwatch::~Stopwatch()
	{

	}

	void Stopwatch::Start()
	{
		m_start = high_resolution_clock::now();
	}

	float Stopwatch::GetElapsedTimeSec()
	{
		duration<double, milli> seconds = high_resolution_clock::now() - m_start;
		return (float)(seconds.count() / 1000);
	}

	float Stopwatch::GetElapsedTimeMs()
	{
		duration<double, milli> ms = high_resolution_clock::now() - m_start;
		return (float)ms.count();
	}
}
