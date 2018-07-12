#include "Log.h"
using namespace std;
namespace TmingEngine
{
	void Debug::Log(const char * message, ...)
	{
		printf(message);
		Global<Context>().GetSubsystem<Console>()->AddLog(message);
	}
}