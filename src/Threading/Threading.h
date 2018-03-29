
#pragma once

//= INCLUDES =================
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include "../Core/SubSystem.h"
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

		//= Subsystem ============
		bool Initialize() override;
		//========================

		// This function is invoked by the threads
		void Invoke();

		// Add a task
		template <typename Function>
		void AddTask(Function&& function)
		{
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
		int m_threadCount = 7;
		std::vector<std::thread> m_threads;
		std::queue<std::shared_ptr<Task>> m_tasks;
		std::mutex m_tasksMutex;
		std::condition_variable m_conditionVar;
		bool m_stopping;
	};
}