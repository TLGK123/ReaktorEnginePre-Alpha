
#pragma once

//= INCLUDES ==================
#include "../Core/EngineDefs.h"
#include <string>
#include <memory>
#include <iomanip>
#include <mutex>
//=============================

namespace TmingEngine
{
#define LOG_INFO(text)		TmingEngine::Log::Write(text, TmingEngine::Log::Info)
#define LOG_WARNING(text)	TmingEngine::Log::Write(text, TmingEngine::Log::Warning)
#define LOG_ERROR(text)		TmingEngine::Log::Write(text, TmingEngine::Log::Error)

	class GameObject;

	namespace Math
	{
		class Quaternion;
		class Vector2;
		class Vector3;
		class Vector4;
	}

	class ENGINE_CLASS Log
	{
		friend class ILogger;
	public:
		enum LogType
		{
			Info,
			Warning,
			Error
		};

		static void Initialize();
		static void Release();
		static void SetLogger(std::weak_ptr<ILogger> logger);

		// STRING
		static void Write(const std::string& text, LogType type);

		// CHAR_PTR
		static void Write(const char* text, LogType type);

		// GAMEOBJECT
		static void Write(std::weak_ptr<GameObject> gameObject, LogType type);

		// VECTORS
		static void Write(const Math::Vector2& vector, LogType type);
		static void Write(const Math::Vector3& vector, LogType type);
		static void Write(const Math::Vector4& vector, LogType type);

		// QUATERNION
		static void Write(const Math::Quaternion& quaternion, LogType type);

		// FLOAT
		static void Write(float value, LogType type);

		// DOUBLE
		static void Write(double value, LogType type);

		// INT
		static void Write(int value, LogType type);

		// UNSIGNED INT
		static void Write(unsigned int value, LogType type);

		// BOOL
		static void Write(bool value, LogType type);

		// SIZE_T
		static void Write(size_t value, LogType type);

		// WEAK_PTR
		template<typename T>
		static void Write(std::weak_ptr<T> ptr, LogType type) { Write(ptr.expired() ? "Expired" : typeid(ptr).name(), type); }

		// SHARED_PTR
		template<typename T>
		static void Write(std::shared_ptr<T> ptr, LogType type) { Write(ptr ? typeid(ptr).name() : "Null", type); }

		static void LogString(const std::string& text, LogType type);
		static void LogToFile(const std::string& text, LogType type);

	private:
		static std::weak_ptr<ILogger> m_logger;
		static std::ofstream m_fout;
		static std::string m_logFileName;
		static bool m_firstLog;
		static std::mutex m_mutex;
	};
}
