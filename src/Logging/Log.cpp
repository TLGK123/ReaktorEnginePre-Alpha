
//= INCLUDES ========================
#include "Log.h"
#include <sstream>
#include <fstream>
#include "ILogger.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Quaternion.h"
#include "../Scene/GameObject.h"
#include "../FileSystem/FileSystem.h"
//===================================

//= NAMESPACES ================
using namespace std;
using namespace TmingEngine;
//=============================

#define LOG_FILE "log.txt"

namespace TmingEngine
{
	weak_ptr<ILogger> Log::m_logger;
	ofstream Log::m_fout;
	bool Log::m_firstLog = true;
	mutex Log::m_mutex;

	void Log::Initialize()
	{
	}

	void Log::Release()
	{
	}

	void Log::SetLogger(weak_ptr<ILogger> logger)
	{
		m_logger = logger;
	}

	//= LOGGING ==========================================================================
	void Log::Write(const string& text, LogType type) // all functions resolve to that one
	{
		// if a logger is available use it, if not, write to file
		if (!m_logger.expired())
		{
			LogString(text, type);
			return;
		}

		LogToFile(text, type);
	}

	void Log::Write(const char* text, LogType type)
	{
		Write(string(text), type);
	}

	/*void Log::Write(weak_ptr<GameObject> gameObject, LogType type)
	{
		gameObject.expired() ? Write("Null", type) : Write(gameObject.lock()->GetName(), type);
	}

	void Log::Write(const Vector2& vector, LogType type)
	{
		string x = "X: " + to_string(vector.x);
		string y = "Y: " + to_string(vector.y);

		Write(x + ", " + y, type);
	}

	void Log::Write(const Vector3& vector, LogType type)
	{
		string x = "X: " + to_string(vector.x);
		string y = "Y: " + to_string(vector.y);
		string z = "Z: " + to_string(vector.z);

		Write(x + ", " + y + ", " + z, type);
	}

	void Log::Write(const Vector4& vector, LogType type)
	{
		string x = "X: " + to_string(vector.x);
		string y = "Y: " + to_string(vector.y);
		string z = "Z: " + to_string(vector.z);
		string w = "W: " + to_string(vector.w);

		Write(x + ", " + y + ", " + z + ", " + w, type);
	}

	void Log::Write(const Quaternion& quaternion, LogType type)
	{
		string x = "X: " + to_string(quaternion.x);
		string y = "Y: " + to_string(quaternion.y);
		string z = "Z: " + to_string(quaternion.z);
		string w = "W: " + to_string(quaternion.w);

		Write(x + ", " + y + ", " + z + ", " + w, type);
	}*/

	void Log::Write(float value, LogType type)
	{
		Write(to_string(value), type);
	}

	void Log::Write(double value, LogType type)
	{
		Write(to_string(value), type);
	}

	void Log::Write(int value, LogType type)
	{
		Write(to_string(value), type);
	}

	void Log::Write(unsigned int value, LogType type)
	{
		Write(int(value), type);
	}

	void Log::Write(bool value, LogType type)
	{
		value ? Write("True", type) : Write("False", type);
	}

	void Log::Write(size_t value, LogType type)
	{
		Write(int(value), type);
	}

	void Log::LogString(const string& text, LogType type)
	{
		lock_guard<mutex> guard(m_mutex);
		m_logger.lock()->Log(text, type);
	}

	void Log::LogToFile(const string& text, LogType type)
	{
		lock_guard<mutex> guard(m_mutex);

		string prefix = (type == Info) ? "Info:" : (type == Warning) ? "Warning:" : "Error:";
		string finalText = prefix + " " + text;

		// Delete the previous log file (if it exists)
		if (m_firstLog)
		{
			FileSystem::DeleteFile_(LOG_FILE);
			m_firstLog = false;
		}

		// Open/Create a log file to write the error message to.
		m_fout.open(LOG_FILE, ofstream::out | ofstream::app);

		// Write out the error message.
		m_fout << finalText << endl;

		// Close the file.
		m_fout.close();
	}

	//=================================================================================
}