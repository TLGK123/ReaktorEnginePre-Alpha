
//= INCLUDES ==============
#include "Threading.h"
//=========================

//= NAMESPACES ======
using namespace  std;
//===================

namespace TmingEngine
{
	Threading::Threading(Context* context) : Subsystem(context)
	{
		m_stopping = false;
	}

	Threading::~Threading()
	{
		// Put unique lock on task mutex.
		unique_lock<mutex> lock(m_tasksMutex);

		// Set termination flag to true.
		m_stopping = true;

		// Unlock the mutex
		lock.unlock();

		// Wake up all threads.
		m_conditionVar.notify_all();

		// Join all threads.
		for (auto& thread : m_threads)
		{
			thread.join();
		}

		// Empty worker threads.
		m_threads.clear();
	}

	bool Threading::Initialize()
	{
		for (int i = 0; i < m_threadCount; i++)
		{
			m_threads.emplace_back(thread(&Threading::Invoke, this));
		}

		return true;
	}

	void Threading::Invoke()
	{
		shared_ptr<Task> task;
		while (true)
		{
			// Lock tasks mutex
			unique_lock<mutex> lock(m_tasksMutex);

			// Check condition on notification
			m_conditionVar.wait(lock, [this] { return !m_tasks.empty() || m_stopping; });

			// If m_stopping is true, it's time to shut everything down
			if (m_stopping && m_tasks.empty())
				return;

			// Get next task in the queue.
			task = m_tasks.front();

			// Remove it from the queue.
			m_tasks.pop();

			// Unlock the mutex
			lock.unlock();

			// Execute the task.
			task->Execute();
		}
	}
}