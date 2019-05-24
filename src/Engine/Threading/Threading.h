
#pragma once

//= INCLUDES =================
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include "../Log/Log.h"
#include "../Core/Subsystem.h"
//============================

namespace TmingEngine
{
	//= TASK ===============================================================================
	class Task
	{
	public:
		typedef std::function<void()> functionType;

		Task(functionType&& function) { m_function = std::forward<functionType>(function); }
		void Execute() { m_function(); }

	private:
		functionType m_function;
	};
	//======================================================================================

	class Threading : public Subsystem
	{
	public:
		Threading(Context* context);
		~Threading();

		// This function is invoked by the threads
		void Invoke();

		// Add a task
		template <typename Function>
		void AddTask(Function&& function)
		{
			if (m_threads.empty())
			{
			//	LOG_WARNING("Threading::AddTask: No available threads, function will execute in the same thread");
				function();
				return;
			}

			// Lock tasks mutex
			std::unique_lock<std::mutex> lock(m_tasksMutex);

			// Save the task
			m_tasks.push(std::make_shared<Task>(std::bind(std::forward<Function>(function))));

			// Unlock the mutex
			lock.unlock();

			// Wake up a thread
			m_conditionVar.notify_one();
		}

	private:
		uint32_t m_threadCount;
		std::vector<std::thread> m_threads;
		std::queue<std::shared_ptr<Task>> m_tasks;
		std::mutex m_tasksMutex;
		std::condition_variable m_conditionVar;
		bool m_stopping;
	};
}
