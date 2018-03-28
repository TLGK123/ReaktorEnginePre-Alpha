
//= INCLUDES ==========
#include <chrono>
#include "EngineDefs.h"
//=====================

namespace TmingEngine
{
	class ENGINE_CLASS Stopwatch
	{
	public:
		Stopwatch();
		~Stopwatch();

		void Start();

		float GetElapsedTimeSec();
		float GetElapsedTimeMs();

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
	};
}
